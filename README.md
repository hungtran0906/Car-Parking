# Car Parking STM32
This is the project implemented on STM32F103 microcontroller. This system allow admin user to manage allowed IDs for entrance, monitor available parking slots.
## Hardware Requirement
* STM32 microcontroller
* Keypad
* LCDs display
* RFID readers
* Servo motors
* PIR sensor
* RFID cards
## Key features
* ID manage : Add or remove IDs to control vehicles entering the parking
* Access/exit control: Servo motor opens the door when the card is correct, closes the door when the car has entered.
* Parking space monitoring: Update the number of available spaces automatically when the vehicle enters/exits.
