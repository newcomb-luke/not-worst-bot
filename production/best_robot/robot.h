/*****************************************************************
 * Robot Control Library
 * Author: Luke Newcomb
 * Last Updated: 10/4/2020
 *****************************************************************/

#ifndef ROBOT_H
#define ROBOT_H

#include <Servo.h>
#include <Arduino.h>

enum class Wheel
{
  RIGHT,
  LEFT
};

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
    void setPower(int); // Drives with a given speed percentage
    void setWheelPowers(int, int); // Drives both wheels independently with given speed percentages
    void reverseTimed(int); // Drives forward for a given number of milliseconds
    void turnLeft(int); // Turns to the left a given number of degrees
    void turnRight(int); // Turn to the right a given number of degrees
    void driveWheelTimed(Wheel, int); // Turns one wheel, given by an int, a specified number of ms
};

class PIDController
{
  private:
    float _ff = 0.0f;
    float _p = 0.0f;
    float _i = 0.0f;
    float _d = 0.0f;
    unsigned long _lastUpdated = 0;
  public:
    PIDController(float, float, float, float); // Creates a new PID controller object using the FeedForward P, I, and D constants
    float getOutput(float); // Gets the output using the specified error
};

#endif
