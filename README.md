# ConfigurableIluminationSystem

#1	Functional requirements

##1.1	Application
The purpose of the project is to develop a configurable system that will control a lightning system built up from four LEDs. The user must be able to setup each LED individually (ON/OFF feature) and could control the illumination level.
User can observe via UART interface all the actions that are performed.

####The system will consist from the following peripherals:

-	4 LEDs controllable via PWM
-	1 joystick with 2 analog outputs and 1 push button
-	1 uart to USB converter
-	1 display (16 x 2 characters) controlled via GPIO

####The menu will have the following structure:

1.	LED 1 -> ON/OFF submenu
2.	LED 2 -> ON/OFF submenu
3.	LED 3 -> ON/OFF submenu
4.	LED 4 -> ON/OFF submenu
5.	Luminosity Level -> 1,2,3,4,5

####The joystick will allow the user to navigate in the menu: 

-	Up/Down movement will cycle the main menus / submenus
-	Right movement -> enter submenu
-	Left movement -> return to previous menu
-	Push button -> Select/ validate option inside menu

### The project was developed on FRDM-KEAZ128 development board that is equiped with Kinetis KL02 Cortex®-M0+ microcontroller.

