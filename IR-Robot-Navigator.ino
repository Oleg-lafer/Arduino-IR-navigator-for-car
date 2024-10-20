#include <IRremote.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

// Define motor control pins
const int LeftPWM = 3;
const int LeftForward = 5;
const int LeftBackward = 4;

const int RightPWM = 6;
const int RightForward = 7;
const int RightBackward = 8;

void setup() {
    // Set motor control pins as outputs
    pinMode(LeftPWM, OUTPUT);
    pinMode(LeftForward, OUTPUT);
    pinMode(LeftBackward, OUTPUT);

    pinMode(RightPWM, OUTPUT);
    pinMode(RightForward, OUTPUT);
    pinMode(RightBackward, OUTPUT);

    // Initialize motors (stopped)
    digitalWrite(LeftForward, HIGH);
    digitalWrite(LeftBackward, LOW);
    digitalWrite(RightForward, HIGH);
    digitalWrite(RightBackward, LOW);

    analogWrite(RightPWM, 0);
    analogWrite(LeftPWM, 0);

    // Start the IR receiver
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
}

// Define variables for button values (Normal remote values)
// const unsigned long button2_forward = 0xFF18E7;    // Forward Button 2
// const unsigned long button4_left = 0xFF10EF;       // Left Button 4
// const unsigned long button6_right = 0xFF5AA5;      // Right Button 6
// const unsigned long button8_backwards = 0xFF4AB5;  // Backwards Button 8


//AC values
const unsigned long button2_forward = 0x9C90030A;    // Forward Button 2
const unsigned long button4_left = 0x9D90020A;       // Left Button 4
const unsigned long button6_right = 0x9C90060A;      // Right Button 6
const unsigned long button8_backwards = 0x9C900A0A;  // Backwards Button 8




// Infinite loop
void loop() {
    // Check if an IR signal has been received and decode it
    if (irrecv.decode(&results)) {
        // Print the decoded value in HEX format to the Serial Monitor
        Serial.println(results.value, HEX); 

        // Check which button was pressed and call the respective function
        if (results.value == button2_forward) {
            Serial.println("Button 2 Forward");
            moveForward();
        } else if (results.value == button4_left) {
            Serial.println("Left Button 4 pressed");
            moveLeft();
        } else if (results.value == button6_right) {
            Serial.println("Right Button 6 pressed");
            moveRight();
        } else if (results.value == button8_backwards) {
            Serial.println("Backwards Button 8 pressed");
            moveBackward();
        }

        // Resume the receiver to prepare for the next IR signal
        irrecv.resume(); 
    }
}

// Function to move forward
void moveForward() {
    Serial.println("Moving Forward");
    digitalWrite(LeftForward, HIGH);   // Left motor forward
    digitalWrite(LeftBackward, LOW);   // Left motor not backward
    digitalWrite(RightForward, HIGH);  // Right motor forward
    digitalWrite(RightBackward, LOW);  // Right motor not backward

    analogWrite(RightPWM, 255);  // Full speed forward for right motor
    analogWrite(LeftPWM, 255);   // Full speed forward for left motor

    delay(1000);  // Move forward for 1 second
    stopMotors();
}

// Function to move left
void moveLeft() {
    Serial.println("Turning Left");
    digitalWrite(LeftForward, LOW);    // Left motor off
    digitalWrite(LeftBackward, HIGH);  // Left motor backward
    digitalWrite(RightForward, HIGH);  // Right motor forward
    digitalWrite(RightBackward, LOW);  // Right motor not backward

    analogWrite(RightPWM, 255);  // Full speed for right motor
    analogWrite(LeftPWM, 255);   // Full speed for left motor (in reverse)

    delay(1000);  // Turn left for 1 second
    stopMotors();
}

// Function to move right
void moveRight() {
    Serial.println("Turning Right");
    digitalWrite(LeftForward, HIGH);   // Left motor forward
    digitalWrite(LeftBackward, LOW);   // Left motor not backward
    digitalWrite(RightForward, LOW);   // Right motor off
    digitalWrite(RightBackward, HIGH); // Right motor backward

    analogWrite(RightPWM, 255);  // Full speed for right motor (in reverse)
    analogWrite(LeftPWM, 255);   // Full speed for left motor

    delay(1000);  // Turn right for 1 second
    stopMotors();
}

// Function to move backward
void moveBackward() {
    Serial.println("Moving Backward");
    digitalWrite(LeftForward, LOW);    // Left motor off
    digitalWrite(LeftBackward, HIGH);  // Left motor backward
    digitalWrite(RightForward, LOW);   // Right motor off
    digitalWrite(RightBackward, HIGH); // Right motor backward

    analogWrite(RightPWM, 255);  // Full speed backward for right motor
    analogWrite(LeftPWM, 255);   // Full speed backward for left motor

    delay(1000);  // Move backward for 1 second
    stopMotors();
}

// Function to stop motors
void stopMotors() {
    analogWrite(RightPWM, 0);   // Stop right motor
    analogWrite(LeftPWM, 0);    // Stop left motor
}
