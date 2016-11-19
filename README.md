# Password-Protection-System-8051
Course project for EEE G512 (Embedded System Design) at BITS Pilani Hyderabad
As a part of this project, we built a Password Protection System. System will ask user for password, if the input password is correct then access will be granted(LED glows on Port 0) . Else, you will hear a buzzer sound(buzzer connected to Port 3). We interface 8051 with 16x2 LCD in 4 bit mode. LCD is used to display entered passwords. 
Main code is in main_sys.c file, while we used lcd.h file to send commands to 16x2 LCD. ir_lcd.h file to get inputs from IR remote.
We made this project on Keil Software by ARM
