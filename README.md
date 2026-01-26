# 🎮 ESP32 Reaction Time Game

> Test your reflexes with an interactive reaction time game built on ESP32!

---

## 🧠 Overview
The **ESP32 Reaction Time Game** measures how quickly a user responds after a randomized delay.  
It features an animated OLED interface, accurate timing logic, and robust state-based input handling.

---
## 🎮 How It Works

1. Press the button to start the game  
2. The system waits for a random delay  
3. When **PRESS!** appears on the display, press the button as quickly as possible  
4. Your reaction time is calculated and displayed
5. Current and best reaction times are shown 
6. Early button presses are detected and rejected  

---

## ✨ Features
- 🎲 Randomized delay before reaction prompt  
- ⏱️ Accurate reaction time measurement using `millis()`  
- 🏆 Best reaction time tracking
- ✅ Early button press detection with visual feedback
- 🔘 Reliable button debouncing and state-based input handling  
- 🖥️ Animated and interactive OLED user interface  
- 🧩 Clean finite state machine–based game logic  

---

## 🧰 Components Used
- ESP32  
- OLED Display (I2C)  
- Push Button  
- Resistor  
- Breadboard and jumper wires  

---

## 📚 Concepts Learned
- Digital input handling and debouncing  
- Non-blocking timing using `millis()`  
- Finite state machines in embedded systems  
- Event-driven programming  
- OLED display interfacing via I2C  
- UI design for resource-constrained devices  

---

## 📌 Project Status

This project is **complete and stable**.  
No additional features are currently planned.

✔ Core gameplay implemented  
✔ UI improvements completed  
✔ Best score tracking added<br>
✔ Early press detection added  
</br>
---
## 🖼️ Project Images

### 🎮 Gameplay
<p align="center">
  <img src="images/gameplay_1.jpg" width="450">
  <img src="images/gameplay_2.jpg" width="450">
</p>


### 🔌 Hardware Setup
<p align="center">
  <img src="images/circuit.jpg" width="400">
</p>



---

## 💡 Why this project?
This project focuses on **input reliability**, **state-driven logic**, and **user feedback**, making it a strong foundation for embedded systems and security-oriented hardware projects.

---
