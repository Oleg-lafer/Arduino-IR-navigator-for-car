Certainly! Here's a polished and professional version of your project description, suitable for GitHub and academic presentation:

---

# Arduino Robot Control with IR Remote

## Overview

An Arduino-based robotic car system programmed in C++, combining joystick control, IR communication, and PWM-driven DC motors for responsive movement. The project leverages the **IRremote** library for remote signal decoding and includes **serial monitoring** for debugging and real-time data visualization.

## Extension: Coordinate-Based Autonomous Navigation
https://github.com/Oleg-lafer/Arduino-coordinate-navigator
<br />
This enhanced module allows the robot to **record a user-defined path** using joystick input and replay it autonomously. Coordinates are filtered and stored based on distance thresholds,  then translated into motor actions using geometric path calculations and the **Law of Sines** to compute rotation angles from three consecutive points.

<div style="display: flex;">
  <img src="car-and-IR-receiver_1.jpg" width="25%">
  <img src="car-and-IR-receiver_2.jpg" width="44%">
</div>




---

## Features
1. **Joystick Input:**  
   - Converts analog joystick readings into discrete values for movement control.
   - Maps joystick values to hexadecimal IR codes for transmission.

2. **Infrared Communication:**  
   - Utilizes the `IRremote.h` library for sending and receiving IR signals.
   - Sends joystick-based movement commands as Sony IR codes.

3. **Motor Control:**  
   - Two DC motors are controlled via PWM signals.
   - Supports forward, backward, left, and right movements based on IR commands.

4. **Serial Monitoring:**  
   - Displays joystick values and encoded transmission data for debugging and analysis.

---

## Components Used
- Arduino Uno (or compatible)
- Joystick Module
- IR LED for transmitting signals
- IR Receiver Module for receiving signals
- Two DC Motors with Motor Driver
- Robot chassis

---

## Code Highlights

### Joystick to IR Transmission
The joystick's analog values (`joyX` and `joyY`) are read, scaled, and encoded into a single hexadecimal value:
```cpp
int RVx = analogRead(joyX);
int RVy = analogRead(joyY);

int xTx = RVx / levels;
int yTx = RVy / levels;

int hexTx = xTx + yTx * 16;

irsend.sendSony(hexTx, 12);
```

### IR Signal Decoding and Motor Control
The received IR signals are decoded and mapped to specific motor actions:
```cpp
if (results.value == button2_forward) {
    moveForward();
} else if (results.value == button4_left) {
    moveLeft();
} else if (results.value == button6_right) {
    moveRight();
} else if (results.value == button8_backwards) {
    moveBackward();
}
```

---

## Functions
### Movement Functions
Each movement function (e.g., `moveForward`, `moveLeft`) controls the motor pins and PWM signals for the desired direction.
```cpp
void moveForward() {
    digitalWrite(LeftForward, HIGH);
    digitalWrite(LeftBackward, LOW);
    digitalWrite(RightForward, HIGH);
    digitalWrite(RightBackward, LOW);
    analogWrite(LeftPWM, 255);
    analogWrite(RightPWM, 255);
    delay(1000);
    stopMotors();
}
```

### Stop Motors
Stops all motor movement:
```cpp
void stopMotors() {
    analogWrite(RightPWM, 0);
    analogWrite(LeftPWM, 0);
}
```

---

## How to Use
1. Connect the joystick, IR LED, IR receiver, and motors as per the circuit diagram.
2. Upload the code to the Arduino board.
3. Use the joystick to send movement commands:
   - Move the joystick to control the car's direction (forward, backward, left, or right).
   - Commands are transmitted via IR and received by the robot.

---

## Potential Improvements
- Add obstacle detection with ultrasonic sensors.
- Implement speed control based on joystick intensity.
- Introduce autonomous modes like line following or object avoidance.
- Enhance command robustness with error detection for IR signals.

---

This project is an excellent introduction to remote-controlled robotics, combining hardware and software for a fun, interactive experience. Customize it further to explore advanced robotic functionalities!
