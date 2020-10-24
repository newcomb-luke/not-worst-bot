#include <Arduino.h>

// IR line sensor constants
#define RIGHT_IR     A0
#define RIGHT_THRESH 950
#define LEFT_IR      A1
#define LEFT_THRESH  900

#define BUTTON_PIN   7

// Global variables
int lastButtonState = LOW;

int detectButtonPress(); // Does what it says on the tin

int main(void)
{

    // We are going to do a state machine where the state changes when the button on top of the robot is pressed.
    int state = 0;

    // For averaging, we need a way to store the past readings
    int rollingSensorValues[20];

    // Initialize the array to all 0's
    for (int i = 0; i < 20; i++)
    {
        rollingSensorValues[i] = 0;
    }

    init(); // Allow Arduino to initialize AVR timers

    // Start the serial port
    Serial.begin(9600);

    // Set the button as an input. Active high
    pinMode(BUTTON_PIN, INPUT);

    // Set the right IR sensor pin as an input
    pinMode(RIGHT_IR, INPUT);

    // Infinite loop
    for (;;)
    {
        switch (state)
        {
            // Raw sensor reading state
            case 0:
                Serial.print("Sensor reading: ");
                Serial.println(analogRead(RIGHT_IR));
                break;
            // Switching to categorical reading state
            case 1:
                Serial.println("Switching to categorical testing.");
                delay(2000);
                state++;
                break;
            // Categorical reading state
            case 2:
                Serial.println( analogRead(RIGHT_IR) > RIGHT_THRESH ? "Black" : "White" );
                break;
            // Switching to averaging reading state
            case 3:
                Serial.println("Switching to averaging test.");
                delay(2000);
                state++;
                break;
            // Averaging reading state
            case 4:
                // Variable to store the sum of all of the values in rollingSensorValues
                int sum = 0;

                // Iterate over rollingSensorValues, shifting each value to the left and summing them at the same time
                for (int i = 0; i < 19; i++)
                {
                    rollingSensorValues[i] = rollingSensorValues[i + 1];
                    sum += rollingSensorValues[i];
                }

                // Populate the last value in rollingSensorValues
                rollingSensorValues[19] = analogRead(RIGHT_IR);

                // Add the latest value to the sum
                sum += rollingSensorValues[19];

                Serial.print("Avg. sensor reading: ");
                // Avg = sum / number of readings
                Serial.println( sum / 20 );
                break;
            // Last state before stopping
            case 5:
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
        delay(100);

    }

}

int detectButtonPress()
{
    int currentButtonState = digitalRead(BUTTON_PIN);

    int wasPressed = currentButtonState == HIGH && lastButtonState == LOW;

    lastButtonState = currentButtonState;

    return wasPressed;
}