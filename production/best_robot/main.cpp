#include <Arduino.h>
#include "robot.h"

// Left servo constants
#define LEFT_PIN    3
#define LEFT_DRIVE  2200
#define LEFT_REV    834
#define LEFT_STOP   1515
#define LEFT_TURN   800

// Right servo constants
#define RIGHT_PIN   5
#define RIGHT_DRIVE 838
#define RIGHT_REV   2200
#define RIGHT_STOP  1519
#define RIGHT_TURN  800

Robot myRobot(LEFT_PIN, RIGHT_PIN);

int main(void)
{

  init(); // Allow Arduino to initialize AVR timers

  // Configure the robot
  myRobot.setDrives(LEFT_DRIVE, RIGHT_DRIVE, LEFT_REV, RIGHT_REV);
  myRobot.setStops(LEFT_STOP, RIGHT_STOP);
  myRobot.setTurnTimes(LEFT_TURN, RIGHT_TURN);

  // Start
  myRobot.begin();

  delay(5000);

  myRobot.turnLeft(90);

  delay(2000);

  myRobot.driveTimed(2400);

  delay(2000);

  myRobot.turnRight(90);

  delay(2000);

  myRobot.reverseTimed(2400);

  delay(2000);

  myRobot.turnLeft(90);

  delay(2000);

  myRobot.reverseTimed(2400);

  // Infinite loop
  for (;;)
  {
    
  }
  
}
