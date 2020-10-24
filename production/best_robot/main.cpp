#include <Arduino.h>
#include "robot.h"
#include "linesensor.h"

// Left servo constants
#define LEFT_PIN    3
#define LEFT_DRIVE  1800
#define LEFT_REV    1200
#define LEFT_STOP   1500
#define LEFT_TURN   800

// Right servo constants
#define RIGHT_PIN   5
#define RIGHT_DRIVE 1200
#define RIGHT_REV   1800
#define RIGHT_STOP  1500
#define RIGHT_TURN  800

// IR line sensor constants
#define RIGHT_IR     A0
#define RIGHT_THRESH 995
#define LEFT_IR      A1
#define LEFT_THRESH  950

int main(void)
{

    Robot myRobot(LEFT_PIN, RIGHT_PIN);
    LineSensor sensor(LEFT_IR, RIGHT_IR, LEFT_THRESH, RIGHT_THRESH);

    SensorState state = SensorState::NEITHER;
    SensorState lastState = SensorState::NEITHER;
    unsigned long msOffCourse = 0;
    int wheelSlowdown = 0;

    init(); // Allow Arduino to initialize AVR timers

    Serial.begin(9600);

    // Configure the robot
    myRobot.setDrives(LEFT_DRIVE, RIGHT_DRIVE, LEFT_REV, RIGHT_REV);
    myRobot.setStops(LEFT_STOP, RIGHT_STOP);
    myRobot.setTurnTimes(LEFT_TURN, RIGHT_TURN);

    // Start
    myRobot.begin();

    Serial.begin(9600);

    delay(5000);

    myRobot.setWheelPowers(0, 0);

    /*

    if left
        turn right proportional to the time that it is off course
    if right
        turn left proportional to the time that it is off course
    if neither
        drive forward
    if both
        stop

    */

    // Infinite loop
    for (;;)
    {
        state = sensor.readState();

        if (state != lastState)
        {
            msOffCourse = millis();
            lastState = state;
        }

        wheelSlowdown = 100 - static_cast<int>((static_cast<float>(millis() - msOffCourse) / 200.0f) * 40.0f);

        switch (state)
        {
            case SensorState::LEFT:
                myRobot.setWheelPowers(wheelSlowdown, 100);
                break;
            case SensorState::RIGHT:
                myRobot.setWheelPowers(100, wheelSlowdown);
                break;
            case SensorState::BOTH:
                // Stop the robot forever
                myRobot.setWheelPowers(0, 0);
                break;
                // for (;;) {}
            default:
                myRobot.setWheelPowers(100, 100);
        }
    }

}
