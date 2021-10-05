   ////////////////////////////////////////////////////////
  //          Arduino Obstacle Avoiding Robot v2.0      //             
 //            By Aarav Garg - 2021                    //
////////////////////////////////////////////////////////

//including the libraries
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h> 

//defining pins and variables
#define TRIG_PIN A4 
#define ECHO_PIN A5 
#define MAX_DISTANCE 200
#define MAX_SPEED 200 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

#define turn_amount 500

//defining motors,servo,sensor
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
AF_DCMotor motor1(2, MOTOR12_8KHZ); 
AF_DCMotor motor2(1, MOTOR12_8KHZ);
Servo myservo; 
  
//defining global variables
boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(10);  
  myservo.write(90); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 Serial.println(distance);
 
 if(distance<=15)
 {
  Serial.println("Object Detected");
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  Serial.print("Distance Right = ");
  Serial.println(distanceR);
  delay(200);
  distanceL = lookLeft();
  Serial.print("Distance Left = ");
  Serial.println(distanceL);
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }
  else
  {
    turnLeft();
    moveStop();
  }
 }
 else
 {
  moveForward();
 }

 //reseting the variable after the operations
 distance = readPing();
}

int lookRight()
{
    myservo.write(0); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(90); 
    return distance;
}

int lookLeft()
{
    myservo.write(180); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(90); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);      
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
  }
}  

void turnRight() {
  Serial.println("Turning Right");
  motor1.run(FORWARD);
  motor2.run(BACKWARD);     
  delay(turn_amount);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);      
} 
 
void turnLeft() {
  Serial.println("Turning Left");
  motor1.run(BACKWARD);     
  motor2.run(FORWARD);     
  delay(turn_amount);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
}  
