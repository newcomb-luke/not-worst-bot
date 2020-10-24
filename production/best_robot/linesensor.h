/*****************************************************************
 * IR Line Sensors Library
 * Author: Luke Newcomb
 * Last Updated: 10/23/2020
 *****************************************************************/

#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <Arduino.h>

// Stores different states of the sensor
enum class SensorState
{
    NEITHER,
    LEFT,
    RIGHT,
    BOTH
};

class LineSensor
{
    private:
        int _leftPin = 0;
        int _leftThreshold = 0; // Anything over this value will read as active
        int _rightPin = 0;
        int _rightThreshold = 0; // Anything over this value will read as active
    public:
        LineSensor(int, int, int, int); // Creates a line sensor object using the left and right pins, and the thresholds for both
        SensorState readState(); // Returns the current state of the sensor
};

#endif