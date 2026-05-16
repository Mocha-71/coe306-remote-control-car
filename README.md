# COE306 Remote Control Car
## Overview
This project is a remote control car developed for the COE306 course at KFUPM.  
The car is controlled through a web interface hosted by an ESP32. Users can connect to the ESP32 access point and control the movement of the car using buttons on a webpage.

## Features
- ESP32-based web control
- Wireless control through a browser
- Forward, backward, left, right, and stop movement
- Servo motor control
- Responsive web interface that supports both vertical and horizontal phone orientations

## Components Used
- ESP32 S3 development board
- Continuous rotation servo motors
- 3.7 Batteries
- Regulator
- Breadboard and jumper wires
- Car chassis and wheels

## Technologies Used
- Arduino IDE
- ESP32 Wi-Fi library
- WebServer library
- ESP32Servo library
- HTML and CSS for the control webpage
  
## Project Preview
![Project Preview](https://github.com/Mocha-71/coe306-remote-control-car/blob/main/remote-control-car.png?raw=true)

## Circuit Connections
![Connection Diagram](https://github.com/Mocha-71/coe306-remote-control-car/blob/main/connections.png?raw=true)
## How It Works
The ESP32 creates a Wi-Fi access point.  
After connecting to the ESP32 network, the user opens the car control webpage in a browser.  
When a button is pressed, the browser sends a request to the ESP32, and the ESP32 controls the servo motors based on the selected direction.

## Notes
- The servo stop value may need calibration depending on the motor.

## Documentation
[Project Report](COE306_Project.pdf)
