# Bridge555

**Bridge555** is an unconventional, lightweight Arduino library that turns an **Arduino Uno R3**, an analog **NE555 timer IC**, and a digital potentiometer (such as the X9C104) into a digitally programmable, closed-loop precision frequency and PWM generator.

---

## The Problem
The Arduino Uno R3 (ATmega328P) has severe hardware constraints (2 KB SRAM) and lacks flexible high-frequency PWM or hardware timers without hacking internal registers. Generating precise continuous pulses in software eats up 100% of CPU cycles, blocking other tasks. Meanwhile, analog NE555 circuits offer incredible hardware frequency generation, but they are entirely static—unless manually tuned.

---

## The Solution
`Bridge555` bridges microcontroller logic with analog hardware. It calculates math-to-wiper resistance mappings on the fly, commanding an external digital potentiometer to tune the NE555 circuit dynamically. By offloading heavy pulse generation to the analog domain, your Uno's CPU stays free for other tasks, while built-in feedback loops help monitor and self-correct frequency drift.

---

## Features
* **Math-to-Wiper Mapping:** Automatically translates target frequencies into precise digital potentiometer wiper steps based on standard astable 555 timing equations.
* **Zero CPU Overhead:** Once configured, the analog NE555 runs autonomously.
* **Closed-Loop Calibration Hook:** Leverages Uno’s input capture capabilities to read actual output frequencies and account for component tolerances.
* **AVR Optimized:** Tailored strictly for the ATmega328P (Arduino Uno R3) architecture with a tiny memory footprint.

---

## Hardware Requirements
1. **Arduino Uno R3**
2. **NE555 Timer IC**
3. **Digital Potentiometer** (e.g., X9C104 - 100kΩ)
4. **Timing Capacitor & Resistors** (wired in standard astable configuration)
