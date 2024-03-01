# Embedded Clock and Alarm System with Temperature Display

This project implements a digital clock with alarm functionality and temperature display on an Arduino board. It was developed as part of the Embedded Systems and Digital Design lab at the university.

## Features
- Real-time clock with hour, minute, and second display.
- Alarm setting and snooze functionality.
- Temperature display in Celsius and Fahrenheit.
- User interface with buttons for setting time, alarm, and toggling temperature units.

## Components Used
- Arduino board (e.g., Arduino Uno)
- LiquidCrystal library for interfacing with the LCD display
- Temperature sensor (analog or digital)
- Buzzer for alarm notification
- Pushbuttons for user input

## How to Use
1. Connect the components according to the defined pin configurations.
2. Upload the provided Arduino sketch to your Arduino board.
3. Use the buttons to set the time, alarm, and toggle temperature units.
4. The LCD will display the current time, alarm status, and temperature.
5. When the alarm time is reached, the buzzer will ring until the alarm is dismissed or snoozed.

## Project Structure
- `clock_alarm_temp.ino`: Arduino sketch containing the main code for the clock, alarm, and temperature display.
- `Readme.md`: Documentation file providing an overview of the project, its features, and usage instructions.

## Code Breakdown
- Buttons and Their Functions:
  - B1 (A0): Changes the time format between 24-hour and 12-hour.
  - B2 (A1): Enables or disables the alarm.
  - B3 (A2): Changes the temperature unit between Fahrenheit and Celsius.
  - B4 (A3): Stops the alarm when it snoozes.
- Time Setting:
  - Pressing B1 for 3 seconds sets the current time.
- Alarm Setting:
  - Pressing B2 for 3 seconds initiates the alarm setting mode.

## Circuit Configuration
- The circuit includes four buttons (B1, B2, B3, B4) for user input.
- Other components include a temperature sensor, buzzer, and LCD display interfaced with the Arduino board.

## Usage Instructions
1. Use B1 to toggle between time formats (24-hour and 12-hour).
2. Enable or disable the alarm using B2.
3. Change the temperature unit with B3.
4. Use B4 to stop the alarm when snoozing.
5. Long-press B1 or B2 for 3 seconds to set the time or alarm, respectively.

## Notes
- This code was developed as part of an Embedded Systems and Digital Design lab .
- Feel free to modify and extend the code for your own projects.
