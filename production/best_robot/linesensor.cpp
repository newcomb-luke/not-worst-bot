#include "linesensor.h"

/**
 * Class constructor, creates a new instance of LineSensor
 */
LineSensor::LineSensor(int left, int right, int leftThreshold, int rightThreshold)
{
    _leftPin = left;
    _rightPin = right;
    _leftThreshold = leftThreshold;
    _rightThreshold = rightThreshold;

    pinMode(_leftPin, INPUT);
    pinMode(_rightPin, INPUT);
}

/**
 * Returns the current state of the sensor as a SensorState enum value.
 */
SensorState LineSensor::readState()
{
    Serial.print(analogRead(_leftPin));
    Serial.print(", ");
    Serial.println(analogRead(_rightPin));
    // Branchless logic for extra speed
    return SensorState( (analogRead(_leftPin) > _leftThreshold) + (analogRead(_rightPin) > _rightThreshold) * 2 );
}