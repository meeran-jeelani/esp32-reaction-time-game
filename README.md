# ESP32 Reaction Time Game

## Overview
This project is a simple reaction time game built using an ESP32 and an OLED display. 
The system measures how quickly a user reacts after a visual prompt.

## How It Works
1. The game waits for a random delay.
2. An LED or OLED message indicates when to press the button.
3. The system calculates reaction time using system timers.
4. Reaction time is displayed on the OLED screen.

## Components Used
- ESP32
- OLED Display (I2C)
- Push Button
- Resistor
- Breadboard and jumper wires

## Concepts Learned
- Digital input and output handling
- Timing using `millis()`
- Event-based programming
- Display interfacing using I2C


## Future Improvements
- Add best score tracking
- Add sound feedback using buzzer
