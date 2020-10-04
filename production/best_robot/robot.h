/*****************************************************************
 * Robot Control Library
 * Author: Luke Newcomb
 * Last Updated: 10/4/2020
 *****************************************************************/

#ifndef ROBOT_H
#define ROBOT_H

#include <Servo.h>
#include <Arduino.h>

class Robot
{
  private:
    int _leftPin = 0;
    int _leftDrive = 0;
    int _leftRev = 0; // Duty cycle for reverse
    int _leftStop = 0;
    int _leftTurnTime = 0; // The number of ms it takes to turn 90 degrees.
    
    int _rightPin = 0;
    int _rightDrive = 0;
    int _rightRev = 0; // Duty cycle for reverse
    int _rightStop = 0;
    int _rightTurnTime = 0; // The number of ms it takes to turn 90 degrees.
    
    Servo _leftServo;
    Servo _rightServo;
  public:
    Robot(int, int); // Creates a robot object using the left and right pins respectfully
    void begin(); // Attaches the servos and stops both
    void setDrives(int, int, int, int); // Sets the drive duty cycles for each servo, forward then reverse
    void setStops(int, int); // Sets the stop duty cycles for each servo
    void setTurnTimes(int, int); // Sets the turn times for both left and right
    void driveTimed(int); // Drives forward for a given number of milliseconds
    void reverseTimed(int); // Drives forward for a given number of milliseconds
    void turnLeft(int); // Turns to the left a given number of degrees
    void turnRight(int); // Turn to the right a given number of degrees
};

#endif
