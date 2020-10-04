#include <Arduino.h>
#include "robot.h"

// Left servo constants
#define LEFT_PIN    2
#define LEFT_DRIVE  1100
#define LEFT_REV    2200
#define LEFT_STOP   1500
#define LEFT_TURN   650

// Right servo constants
#define RIGHT_PIN   3
#define RIGHT_DRIVE 1100
#define RIGHT_REV   2200
#define RIGHT_STOP  1500
#define RIGHT_TURN  650

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

  // Infinite loop
  for (;;)
  {
    
  }
  
}
