# include <Servo.h>
#define sensorFront A0 
#define sensorAngle A1  
int servoPin=9;
int bigMotorForward =7;
int bigMotorBackward=8;
int smallMotorForward=2;
int smallMotorBackward =4;
int rodLengthBehind;
int baseLenght;
int stairHeight;
int numberOfStairs;
int SSM; // speed of small motor
int SBM; // speed of big motor z
Servo Servo1;
int steps =1;
const int numReadings=10;
int readIndex=0;
int readings[numReadings];
int total=0;
int average=0;
void setup(){
 Serial.begin(9600);
 Servo1.attach(servoPin);
 pinMode(bigMotorForward,OUTPUT);
 pinMode(bigMotorBackward,OUTPUT);
 pinMode(smallMotorForward,OUTPUT);
 pinMode(smallMotorBackward,OUTPUT);
 Servo1.write(0);
 for(int thisReading = 0; thisReading <= numReadings; thisReading++) {
    readings[thisReading] = distanceFront();
 total=total+readings[thisReading];
  }average=total/numReadings;
 }
float distanceFront(){float SensorValue = analogRead(sensorFront);
float vr = SensorValue*1000/1024;
float Distance = 4800/(vr - 20);
return Distance;
}
int distance(){
  for(int i=0;i<=50;i++){
  total = total - readings[readIndex];
  readings[readIndex] = distanceFront();
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
  delay(1);}
  return average;
  }
void moveForward()
{
   digitalWrite(smallMotorForward,HIGH);
   digitalWrite(smallMotorBackward,LOW); 
}

void moveBackward()
{
  digitalWrite(smallMotorForward,LOW);
  digitalWrite(smallMotorBackward,HIGH);
}
void stopSmallm()
{
  digitalWrite(smallMotorForward,HIGH);
  digitalWrite(smallMotorBackward,HIGH);
}
void rackForward()
{
   digitalWrite(bigMotorForward,HIGH);
   digitalWrite(bigMotorBackward,LOW); 
}

void rackBackward()
{
  digitalWrite(smallMotorForward,LOW);
  digitalWrite(smallMotorBackward,HIGH);
}
void stopBigM()
{
  digitalWrite(smallMotorForward,HIGH);
  digitalWrite(smallMotorBackward,HIGH);
}

int distanceAngle()
{
  float volts = analogRead(sensorAngle);
  int dist = 4800/(volts - 20); // worked out from datasheet graph
  return dist;
}
void loop(){
   do{moveForward();
   Serial.println(distance());
   }while(distance()>=30); 
    if(steps==1){Servo1.write(22);
    for(;distance()>=25;)moveForward();
    rackBackward();
    delay(3000);
 moveForward();
    delay(10000);
    stopBigM();
    delay(3000);
    stopSmallm();
    steps+=1;}
    //step 2 started 
    rackForward();
    delay(10000);
    stopBigM();
    Servo1.write(55);
    moveForward();
    delay(3000);
    stopSmallm();
    rackBackward();
    delay(3000);
    moveForward();
    rackBackward();
    delay(10000);
    stopBigM();
    delay(3000);
    stopSmallm();
 Serial.println(distance());
}
