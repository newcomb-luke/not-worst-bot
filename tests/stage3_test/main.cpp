#include <Arduino.h>

// Constants
#define PULSE_PIN         8
#define ECHO_PIN          9
#define CONVERSION_FACTOR 0.034
#define NUMBER_READINGS   10
#define BUTTON_PIN        7

// Global variables
int lastButtonState = LOW;

int detectButtonPress(); // Does what it says on the tin
float readUltrasonicSensor(); // Also does what it says on the tin

int main(void)
{

    // We are going to do a state machine where the state changes when the button on top of the robot is pressed.
    int state = 0;

    // In order the know the extremes we have to store them
    float minimumDistance = 1000.0f;
    float maximumDistance = 0.0f;
    float avgSensorReading = 0.0f;

    // In order to reduce error for this test, the readings will be averaged
    float rollingSensorValues[NUMBER_READINGS];

    init(); // Allow Arduino to initialize AVR timers

    // Start the serial port
    Serial.begin(9600);

    // Set the button as an input. Active high
    pinMode(BUTTON_PIN, INPUT);

    // Set the ultrasonic sensor pin directions
    pinMode(PULSE_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Infinite loop
    for (;;)
    {

        // If we aren't "halted" then we are going to need to read a sensor
        if (state < 3)
        {

            // Variable to store the sum of all of the values in rollingSensorValues
            int sum = 0;

            // Iterate over rollingSensorValues, shifting each value to the left and summing them at the same time
            for (int i = 0; i < NUMBER_READINGS-1; i++)
            {
                rollingSensorValues[i] = rollingSensorValues[i + 1];
                sum += rollingSensorValues[i];
            }

            // Populate the last value in rollingSensorValues
            rollingSensorValues[NUMBER_READINGS-1] = readUltrasonicSensor();

            // Add the latest value to the sum
            sum += rollingSensorValues[NUMBER_READINGS-1];

            // Avg = sum / number of readings
            avgSensorReading = sum / NUMBER_READINGS;

            if (avgSensorReading > maximumDistance)
            {
                maximumDistance = avgSensorReading;
            }

            if (avgSensorReading < minimumDistance)
            {
                minimumDistance = avgSensorReading;
            }
        }

        switch (state)
        {
            // Raw sensor reading state
            case 0:
                Serial.print("Avg sensor reading: ");
                Serial.println(avgSensorReading);
                Serial.print("Maximum sensor reading: ");
                Serial.println(maximumDistance);
                break;
            // Switching to categorical reading state
            case 1:
                Serial.println("Switching to minimum reading state.");
                delay(2000);
                state++;
                break;
            // Categorical reading state
            case 2:
                Serial.print("Avg sensor reading: ");
                Serial.println(avgSensorReading);
                Serial.print("Minimum sensor reading: ");
                Serial.println(minimumDistance);
                break;
            case 3:
                Serial.println("Test complete.");
                Serial.flush();
                delay(1000);
                Serial.flush();
                state++;
                break;
            default:
                break;
        }

        // If the button was pressed, increment the state variable
        state += detectButtonPress();

        // Add a small delay for stability
        delay(50);

    }

}

int detectButtonPress()
{
    int currentButtonState = digitalRead(BUTTON_PIN);

    int wasPressed = currentButtonState == HIGH && lastButtonState == LOW;

    lastButtonState = currentButtonState;

    return wasPressed;
}

float readUltrasonicSensor()
{
    int microseconds = 0;

    // Reset the sensor
    digitalWrite(PULSE_PIN, LOW);
    delayMicroseconds(2);
    // Send out a pulse
    digitalWrite(PULSE_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(PULSE_PIN, LOW);
    // Read the response
    microseconds = pulseIn(ECHO_PIN, HIGH);

    return (microseconds - 10) * CONVERSION_FACTOR / 2;
}