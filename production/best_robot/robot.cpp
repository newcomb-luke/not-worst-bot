#include "robot.h"

/**
 * Class constructor, creates servo objects but doesn't attach them
 */
Robot::Robot(int left, int right)
{
  _leftPin = left;
  _rightPin = right;
}

/**
 * Attaches the servos and stops both, should only be called after config.
 */
void Robot::begin()
{
  // Begin the servo control
  _leftServo.attach(_leftPin);
  _rightServo.attach(_rightPin);

  // Immediately stop them
  _leftServo.write(_leftStop);
  _rightServo.write(_rightStop);
}

/**
 * Sets the config drive duty cycles for the servos
 */
void Robot::setDrives(int leftF, int rightF, int leftR, int rightR)
{
  _leftDrive = leftF;
  _rightDrive = rightF;

  _leftRev = leftR;
  _rightRev = rightR;
}

/**
 * Sets the config stop duty cycles for the servos
 */
void Robot::setStops(int left, int right)
{
  _leftStop = left;
  _rightStop = right;
}

/**
 * Sets the times it takes to turn left and right 90 degrees
 */
void Robot::setTurnTimes(int left, int right)
{
  _leftTurnTime = left;
  _rightTurnTime = right;
}

/**
 * Drives the robot forward for a certain number of milliseconds, and then stops
 */
void Robot::driveTimed(int ms)
{
  // Start the servos
  _leftServo.write(_leftDrive);
  _rightServo.write(_rightDrive);

  // TODO: Make this async?
  delay(ms); // Waits for milliseconds

  // Stop the servos
  _rightServo.write(_rightStop);
  _leftServo.write(_leftStop);
}

/**
 * Drives with a given speed percentage
 * Min = -100 or backwards
 * Max = 100 or forwards
 */
void Robot::setPower(int percent)
{
  int scaledLeft = map(percent, -100, 100, _leftRev, _leftDrive);
  int scaledRight = map(percent, -100, 100, _rightRev, _rightDrive);
  
  _leftServo.write(scaledLeft);
  _rightServo.write(scaledRight);
}

/**
 * Drives both wheels independently with given speed percentages
 * Min = -100 or backwards
 * Max = 100 or forwards
 */
void Robot::setWheelPowers(int percentLeft, int percentRight)
{
  int scaledLeft = map(percentLeft, -100, 100, _leftRev, _leftDrive);
  int scaledRight = map(percentRight, -100, 100, _rightRev, _rightDrive);
  
  _leftServo.write(scaledLeft);
  _rightServo.write(scaledRight);
}

/**
 * Drives the robot backwards for a certain number of milliseconds, and then stops
 */
void Robot::reverseTimed(int ms)
{
  // Start the servos
  _leftServo.write(_leftRev);
  _rightServo.write(_rightRev);

  // TODO: Make this async?
  delay(ms); // Waits for milliseconds

  // Stop the servos
  _rightServo.write(_rightStop);
  _leftServo.write(_leftStop);
}

/**
 * Turns the robot to the left by a certain number of degrees
 */
void Robot::turnLeft(int deg)
{
  _leftServo.write(_leftRev);
  _rightServo.write(_rightDrive);

  // TODO: Make this async?
  delay( (deg / 90.0f) * _leftTurnTime );

  _rightServo.write(_rightStop);
  _leftServo.write(_leftStop);
  
}

/**
 * Turns the robot to the right by a certain number of degrees
 */
void Robot::turnRight(int deg)
{
  _leftServo.write(_leftDrive);
  _rightServo.write(_rightRev);

  // TODO: Make this async?
  delay( (deg / 90.0f) * _rightTurnTime );

  _rightServo.write(_rightStop);
  _leftServo.write(_leftStop);
}

/**
 * Turns one wheel, given by an int, a specified number of ms
 * 0 = RIGHT
 * 1 = LEFT
 */
void Robot::driveWheelTimed(Wheel wheel, int ms)
{
  // Start the servos
  if (wheel == Wheel::LEFT)
    _leftServo.write(_leftDrive);
  else
    _rightServo.write(_rightDrive);

  // TODO: Make this async?
  delay(ms); // Waits for milliseconds

  // Stop the servos
  if (wheel == Wheel::LEFT)
    _leftServo.write(_leftStop);
  else
    _rightServo.write(_rightStop);
}

/**
 * Creates a new PID controller object using the FeedForward P, I, and D constants
 */
PIDController::PIDController(float ff, float p, float i, float d)
{
  _ff = ff;
  _p = p;
  _i = i;
  _d = d;
}

/**
 * Gets the output using the specified error
 */
float PIDController::getOutput(float error)
{
  
}