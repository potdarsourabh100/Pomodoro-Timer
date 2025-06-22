# Pomodoro Timer (STM32 + TM1637 + 18650 Li-ion)

A compact and handheld Pomodoro Timer built using an STM32 microcontroller, TM1637 display, 2 tactile switches, and a buzzer. It is powered by dual 18650 Li-ion cells with a 2S BMS and includes USB charging support.

---
## Working Idea

# Pomodoro Timer Flowchart

```text
+----------------------+
|   Start Application |
+----------------------+
           |
           v
+----------------------+
|  Set Work Duration   |<------+
|   (e.g., 25 mins)    |       |
+----------------------+       |
           |                   |
           v                   |
+----------------------+       |
|    Start Work Timer  |       |
+----------------------+       |
           |                   |
           v                   |
+----------------------+       |
|   Countdown Work     |       |
|   Time Every Second  |       |
+----------------------+       |
           |                   |
           v                   |
+----------------------+       |
|  Work Time Finished? |--No--+
+----------------------+
           |
          Yes
           |
           v
+----------------------+
| Play Alarm / Notify |
+----------------------+
           |
           v
+----------------------+
|  Increment Pomodoro  |
|     Count (+1)       |
+----------------------+
           |
           v
+----------------------+
| Pomodoro Count % 4 = 0? |
+----------------------+
       | Yes          | No
       v              v
+----------------+  +----------------------+
| Long Break     |  | Short Break         |
| (15-30 mins)   |  | (5 mins)            |
+----------------+  +----------------------+
       |                   |
       v                   v
+----------------------+  +----------------------+
|  Start Break Timer   |  |  Start Break Timer   |
+----------------------+  +----------------------+
           |                   |
           v                   v
+----------------------+  +----------------------+
| Countdown Break Time |  | Countdown Break Time |
+----------------------+  +----------------------+
           |                   |
           v                   v
+----------------------+  +----------------------+
| Break Time Finished? |  | Break Time Finished? |
+----------------------+  +----------------------+
           |                   |
          Yes                 Yes
           |                   |
           v                   v
+----------------------+
|     Back to Work     |
+----------------------+
           |
           v
     (Repeat Cycle)

---

## 🧠 Features

-⏱️ Pomodoro Mode(P): 25 minutes of focus time
- ☕ Short Break(S): 5 minutes
- 😌 Long Break(L): 15 minutes (after 4 Pomodoros)
- 2 Push Buttons:
  - Button 1: Start/Stop/Reset
  - Button 2: Cycle Modes (P/S/L)
- Buzzer for notifications (end of session, low battery)
- Powered by 2x 18650 Li-ion with BMS protection
- USB Charging (Micro-USB/USB-C)
- TM1637 4-digit 7-segment display

---

## 📦 Hardware Used

| Component       | Description                          |
|----------------|--------------------------------------|
| STM32 MCU      | STM32F0xx / STM32G0xx series         |
| Display        | TM1637 4-digit 7-segment module      |
| Buzzer         | Active piezo buzzer                  |
| Switches       | 2x Tactile push buttons              |
| Battery        | 2x 18650 Li-ion cells                |
| BMS            | 2S Battery Management System         |
| USB Charging   | TP4056-based charger (5V input)      |

---

## 🔧 Build Instructions

1. Assemble all hardware components as per the schematic.
2. Flash the firmware to STM32 using ST-Link.
3. Power the system using battery or USB.
4. Use Button 1 to start/stop/reset the timer.
5. Use Button 2 to switch between Pomodoro, Short, and Long Break modes.

---

## 📌 To-Do / Enhancements

- [ ] Add various tones for notifications
- [ ] Add BLE support for app notifications
- [ ] Configurable timer durations via USB
- [ ] Battery monitoring via ADC
- [ ] Low-power sleep mode
- [ ] Pocket-sized, portable enclosure

---

## 📜 License

This project is open-source under the MIT License.
