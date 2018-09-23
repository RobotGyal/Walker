#include <Servo.h>

Servo frontServo;
Servo rearServo;

int centerPos = 90;
int frontRightUp = 72;
int frontLeftUp = 108;
int backRightForward = 75;
int backLeftForward = 105;
int walkSpeed = 150;
int centerTurnPos = 81;
int frontTurnRightUp = 63;
int frontTurnLeftUp = 117;
int backTurnRightForward = 66;
int backTurnLeftForward = 96;

int pingPin = 4;
long int duration, distanceInches;
long distanceFront = 0;
int startAvoidanceDistance = 20;

long microsecondsToInches(long microseconds)
{
  return microseconds;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds;
}

long distanceCm()
{
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  
  distanceInches = microsecondsToInches(duration);
  return microsecondsToCentimeters(duration);
}

void center()
{
  frontServo.write(centerPos);
  rearServo.write(centerPos);
}

void moveForward()
{
  frontServo.write(frontRightUp);
  rearServo.write(backLeftForward);
  delay(125);
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(65);
  frontServo.write(frontLeftUp);
  rearServo.write(backRightForward);
  delay(125);
}

void moveBackRight()
{
  frontServo.write(frontRightUp);
  rearServo.write(backRightForward);
  delay(125);
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(65);
  frontServo.write(frontRightUp);
  rearServo.write(backRightForward);
  delay(125);
  frontServo.write(centerPos);
  rearServo.write(centerPos);
  delay(65);
}

void moveTurnLeft()
{
  frontServo.write(frontTurnRightUp);
  rearServo.write(backTurnLeftForward);
  delay(125);
  frontServo.write(centerTurnPos);
  rearServo.write(centerTurnPos);
  delay(125);
  frontServo.write(frontTurnLeftUp);
  rearServo.write(backTurnRightForward);
  delay(125);
  frontServo.write(centerTurnPos);
  rearServo.write(centerTurnPos);
  delay(125);
}

void setup()
{
  frontServo.attach(2);
  rearServo.attach(3);
  pinMode(pingPin, OUTPUT);
}

void loop()
{
  distanceFront = distanceCm();
  if (distanceFront > 1)
  {
    if (distanceFront < startAvoidanceDistance)
    {
      for(int i=0;i<=8; i++)
      {
        moveBackRight();
        delay(walkSpeed);
      }
      for(int i=0; i<=10; i++)
      {
        moveTurnLeft();
        delay(walkSpeed);
      }
    }
    else
    {
      moveForward();
      delay(walkSpeed);
    }
  }
}
  
