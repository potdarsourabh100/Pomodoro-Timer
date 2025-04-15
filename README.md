## 1. Project Overview
A handheld Pomodoro Timer device to help users manage time effectively using the Pomodoro technique. The device will display a countdown timer on a TM1637 4-digit display, accept input through two push buttons, provide audible alerts via a buzzer, and be powered by a rechargeable 2-cell 18650 Li-ion battery with BMS. USB connectivity will be used for charging and data communication.

## 2. Objective
To develop a compact, portable, and user-friendly Pomodoro Timer that offers a simple user interface and effective time tracking with minimal hardware complexity.

## 3. Hardware Requirements
### 3.1 Core Components
Component	   Description
MCU	         STM32 (STM32F0xx/G0xx preferred for low power)
Display	     TM1637 4-digit 7-segment display module
Switches	   2 tactile push buttons
Buzzer	     Active piezo buzzer
Battery	     2 x 18650 Li-ion cells
Battery Protection	2S BMS module
Charging	Micro-USB or USB-C port with TP4056-based charging IC
Enclosure	Handheld ergonomic plastic casing (3D printed or off-the-shelf)
## 4. Functional Requirements
### 4.1 Timer Operation
Pomodoro Duration: 25 minutes of focused work
Break Duration:
Short Break: 5 minutes
Long Break: 15 minutes (after every 4 Pomodoros)
User Input:
Button 1 (Start/Stop/Reset):
Short Press: Start/Stop timer
Long Press (>2s): Reset current session
Button 2 (Mode Switch):
Cycle between Pomodoro, Short Break, Long Break
Confirmation after 2s timeout or button press
### 4.2 Display Behavior (TM1637)
Show countdown in MM:SS format.
Display P, S, or L in the first digit (blinking) to indicate Pomodoro, Short break, or Long break respectively (if applicable).
When timer is paused, display should blink.
Show done or ---- when timer ends.
### 4.3 Sound Notifications
Short beep every minute for feedback (optional).
Long beep (2s) at the end of each timer.
Continuous short beeps for 5s as final notification (optional).
### 4.4 Power Management
Powered by 2x 18650 cells in series.
2S BMS to provide protection from over-voltage, over-discharge, and short-circuit.
Battery voltage monitoring via ADC to indicate low battery.
Low battery warning on display and buzzer beep pattern.
Auto shutdown when battery is critically low.
### 4.5 Charging and USB Interface
USB port for:
Charging the batteries (5V input)
Future provision: serial communication for log extraction or timer configuration
LED indicator for charging (charging/red, full/green)
### 4.6 Ergonomics
Device should:
Be compact and handheld (approx. 100mm x 60mm x 30mm)
Use minimal buttons for ease of use
Have accessible USB port and clear visibility of the display
## 5. Non-Functional Requirements
### 5.1 Performance
Timer precision: ±1 second over 25 minutes
Debouncing: Software-based for all buttons
Startup Time: <2 seconds
Buzzer should not exceed 80 dB SPL at 10cm

### 5.2 Power Efficiency
Sleep mode when idle
Wake up on button press
Total standby current <500 µA

### 5.3 Environmental
Operating temperature: 0°C to 50°C
Humidity: 20–85% RH, non-condensing

## 6. Future Enhancements (Optional)
Vibration motor for silent notification
Bluetooth interface for app connectivity
OLED display for more detailed status
Custom timer settings via serial interface or USB config tool

## 7. Deliverables
Schematics and PCB design files
Firmware source code (with comments and documentation)
3D design files for enclosure
Test report for all functional cases
User manual (1-page quick start)

