#include <cstdint>
#include <string.h>
#include <Arduino.h>
#include <Servo.h>

// Global Constants
#define FW_VERSION 0.1 // Note: No ending commas on defines
#define DEBUG false

#define LED 2 // Data Pin 2
#define Servo1Pin D5 // Data Pin 5

// Global Objects
Servo servo1;  // Create a servo object to control the first servo
// Twelve servo objects can be created on most boards

// Global Variables
float step = 0.5;
float servo1Pos = 0;
float minPos = 0;
float maxPos = 180;
bool direction = false;

void yieldBackTime() {
  #if defined (ESP8266)
    yield();
  #endif
}

void ledOn() {
    digitalWrite(LED, true);
    if (DEBUG) Serial.println("LED On");
}

void ledOff() {
    digitalWrite(LED, false);
    if (DEBUG) Serial.println("LED Off");
}

void ledToggle() {
    digitalWrite(LED, !(digitalRead(LED)));
}

void setServo1Pos(float pos) {
    servo1.write(pos);
    if (DEBUG) {
        Serial.print("Servo Pos: ");
        Serial.println(pos);
    }
}

// Setup occurs on cold boot
void setup(void) {
  pinMode(LED, OUTPUT); // Set the LED to output mode to control it

  delay(1000); // Wait for the USB connection to settle for communication.
  Serial.begin(115200); // Set speed of the terminal for debugging
  Serial.println(); // Output a linefeed to start at a new line after bootup

  ledOff(); // Set LED OFF to save power (On by default after boot)

  // Attach servo 1 on GPIO to the servo1 object
  servo1.attach(Servo1Pin);

  delay(500);
}

// Main hardware loop
void loop(void) {

    if (direction) {
        servo1Pos += step;
    } else {
        servo1Pos -= step;
    }

    if (servo1Pos < minPos || servo1Pos > maxPos) {
        // toggle direction
        direction = !direction;
    }

    setServo1Pos(servo1Pos);   // tell servo 1 to go to position stored in servo1Pos

    // This should always be at the end of the loop
    yieldBackTime(); // Yeild back time to the interrupts after any work is performed
}

