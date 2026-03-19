# 🌡️ Temperature Monitoring & Fan Control System (PIC16F877A)

##  Project Overview

This project implements a temperature-based fan control system using the PIC16F877A microcontroller. The system reads temperature from an LM35 sensor, displays it on an LCD, and controls a fan using PWM based on temperature levels.

---

## ⚙️ Features

* 🌡️ Real-time temperature monitoring using LM35
* 🖥️ LCD display (16x2)
* 🌀 PWM-based fan speed control
* 🔁 Automatic fan ON/OFF based on temperature thresholds

---

##  Concepts Used

* ADC (Analog to Digital Conversion)
* PWM (Pulse Width Modulation)
* LCD Interfacing (8-bit mode)
* Embedded C (XC8 Compiler)

---

##  Hardware Components

* PIC16F877A Microcontroller
* LM35 Temperature Sensor
* 16x2 LCD (LM016L)
* DC Fan (Motor)
* BC547 Transistor
* 1N4007 Diode
* Crystal Oscillator (20MHz)
* Resistors & Capacitors

---

##  Circuit Diagram

![Circuit](images/circuit.png)

---

##  Output

<img width="1108" height="634" alt="image" src="https://github.com/user-attachments/assets/59bf9cc8-4e84-4a7e-8075-f13cfdb2e752" />

<img width="1075" height="588" alt="image" src="https://github.com/user-attachments/assets/10cb45af-85d4-41af-8797-cd6c9dcb97bd" />

<img width="1088" height="593" alt="image" src="https://github.com/user-attachments/assets/6e373a81-44e3-4aad-bd7e-6d49c22d649d" />

<img width="1104" height="584" alt="image" src="https://github.com/user-attachments/assets/419e3b3e-fb8f-4f1e-bf32-fc1f2ce1ac43" />





---

##  Working Principle

1. LM35 outputs analog voltage proportional to temperature.
2. PIC ADC converts analog signal to digital.
3. Temperature is calculated and displayed on LCD.
4. PWM signal controls fan speed based on temperature range:

   * <30°C → OFF
   * 30–35°C → LOW
   * 35–40°C → MEDIUM
   * > 40°C → HIGH

---

##  Software Used

* MPLAB X IDE
* XC8 Compiler
* Proteus Simulation

---

##  How to Run

1. Compile code in MPLAB
2. Generate HEX file
3. Load HEX into Proteus
4. Run simulation

---

##  Future Improvements

* IoT monitoring using ESP32
* Mobile app integration
* Graph-based temperature visualization

---

##  Author

Naveen Tatikonda
