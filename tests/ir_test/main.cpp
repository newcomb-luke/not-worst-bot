#include <Arduino.h>

#define IR_1 A0
#define IR_2 A1

int main(void)
{

    init(); // Allow Arduino to initialize AVR timers

    pinMode(IR_1, INPUT);
    pinMode(IR_2, INPUT);

    Serial.begin(9600);

    // Infinite loop
    for (;;)
    {
        Serial.print("IR1: ");
        Serial.print(analogRead(IR_1));
        Serial.print(",IR2: ");
        Serial.println(analogRead(IR_2));
    }

}
