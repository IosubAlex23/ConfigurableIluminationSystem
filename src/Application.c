/*
 * Application.c
 *
 *  Created on: 27 mai 2018
 *      Author: Alex
 */

#include "Application.h"

#define NumberOfLeds 4
#define JOYSTICK_BTN 0
#define FIRST_SELECTOR_POS_MENU1 8 // 8*1(1=The number of the menu) Position of the first selector
#define MENU1_SELECTOR_SPACES 5 // Spaces between selectors
#define FIRST_SELECTOR_POS_MENU2 3 //FIRST_SELECTOR_POS_MENU2*2(The number of the menu) Position of the first selector
#define MENU2_SELECTOR_SPACES 2 // Spaces between selectors
#define LEDS_LEVEL_STEP 10000

uint8 MenuRowElement = 0;
MenuLocation LocationOfTheMenu = MenuLocation_MainMenu;
uint8 SelectorLocation = 0;
uint8 SelectedOption;
Joystick_State previous_state = -1;
const char * Menu[] = { "LED 1", "LED 2", "LED 3", "LED 4", "Level", "       " };
const char * SubMenu[] = { "          ", ":  OFF  ON", " 1 2 3 4 5" };
struct Led leds[NumberOfLeds];

void App_vInit(void) {
	uint8 IndexOfLed;
	/* Led initialization + Writing first screen to the display using App_vRefreshDisplay()
	 * */
	for (IndexOfLed = 0; IndexOfLed < NumberOfLeds; IndexOfLed++) {
		//leds[IndexOfLed].led_level = LED_Level1;
		leds[IndexOfLed].led_level = LED_ui32getLevel();
		leds[IndexOfLed].led_status = LED_OFF;
		leds[IndexOfLed].channel = &FTM2_C0V + (2 * IndexOfLed);
	}
	App_vRefreshDisplay();
}

void App_vRefreshDisplay(void) {
	/* Writes characters to the display based on LocationOfTheMenu*/
	LCD_String_xy(0, 1, Menu[MenuRowElement]);
	LCD_String(SubMenu[LocationOfTheMenu]);
	LCD_String_xy(1, 1, Menu[MenuRowElement + 1]);
	App_vSetSelector(0);
}

void App_vCheckUserInput(void) {
	Joystick_State state = getJoystickState();
	Button_State js_btn = isGPIOA_ButtonPressed(JOYSTICK_BTN);
	/* state != previous_state - used for avoiding succesive readings
	 * state != JoyStick_Center - joystick has to be in any other state, different from the center
	 * Every state is checked depending on the menu location
	 *   */
	if (state != previous_state && state != JoyStick_Center) {
		if (LocationOfTheMenu == MenuLocation_MainMenu) {
			if (state == JoyStick_North) {
				MenuRowElement =
						MenuRowElement > 0 ?
								MenuRowElement - 1 : MenuRowElement;
				UART_send_String("User goes up.\n\r");
			} else if (state == JoyStick_South) {
				MenuRowElement =
						MenuRowElement < NumberOfLeds ?
								MenuRowElement + 1 : MenuRowElement;
				UART_send_String("User goes down.\n\r");
			} else if (state == JoyStick_East) {
				switch (MenuRowElement) {
				case 0:
				case 1:
				case 2:
				case 3:
					LocationOfTheMenu = MenuLocation_LedMenu;
					break;
				case 4:
					LocationOfTheMenu = MenuLocation_LevelMenu;
					break;
				default:
					LocationOfTheMenu = MenuLocation_MainMenu;
				}
				if (MenuRowElement < NumberOfLeds)
					SelectedOption = leds[MenuRowElement].led_status;
				else
					SelectedOption = (LED_ui32getLevel() / LEDS_LEVEL_STEP) - 1;
				UART_send_String("User goes right.\n\r");
			}
			App_vRefreshDisplay();
			/* S-a schimbat locatia meniului, se seteaza noua locatie in functie de meniul
			 *
			 *  in care s-a intrat */
			if (LocationOfTheMenu == MenuLocation_LedMenu)
				App_vSetSelector(
						LocationOfTheMenu * FIRST_SELECTOR_POS_MENU1
								+ (SelectedOption * MENU1_SELECTOR_SPACES)); // in loc de 0 vine starea actuala a ledului
			else if (LocationOfTheMenu == MenuLocation_LevelMenu)
				App_vSetSelector(
						LocationOfTheMenu * FIRST_SELECTOR_POS_MENU2
								+ (SelectedOption * MENU2_SELECTOR_SPACES)); // in loc de 0 vine starea actuala a ledului

		} else if (LocationOfTheMenu == MenuLocation_LedMenu) {
			if (state == JoyStick_North) {
				SelectedOption = 1;
				App_vSetSelector(
						LocationOfTheMenu * FIRST_SELECTOR_POS_MENU1
								+ (SelectedOption * MENU1_SELECTOR_SPACES));
				UART_send_String("User hovers ON.\n\r");
			} else if (state == JoyStick_South) {
				SelectedOption = 0;
				App_vSetSelector(
						LocationOfTheMenu * FIRST_SELECTOR_POS_MENU1
								+ (SelectedOption * MENU1_SELECTOR_SPACES));
				UART_send_String("User hovers OFF.\n\r");
			} else if (state == JoyStick_West) {
				LocationOfTheMenu = 0;
				App_vRefreshDisplay();
				SelectedOption = 0;
				UART_send_String("User returned to the main menu.\n\r");
			}
		} else if (LocationOfTheMenu == MenuLocation_LevelMenu) {
			if (state == JoyStick_North) {
				if (SelectedOption < NumberOfLeds) {
					SelectedOption = SelectedOption + 1;
					App_vSetSelector(
							LocationOfTheMenu * FIRST_SELECTOR_POS_MENU2
									+ (SelectedOption * MENU2_SELECTOR_SPACES));
					UART_send_String(
							"User cycles up throughout illumination levels.\n\r");
				} else
					SelectedOption = NumberOfLeds;
			} else if (state == JoyStick_South) {
				if (SelectedOption > 0) {
					SelectedOption = SelectedOption - 1;
					App_vSetSelector(
							LocationOfTheMenu * FIRST_SELECTOR_POS_MENU2
									+ (SelectedOption * MENU2_SELECTOR_SPACES));
					UART_send_String(
							"User cycles down throughout illumination levels.\n\r");
				} else
					SelectedOption = 0;
			} else if (state == JoyStick_West) {
				LocationOfTheMenu = 0;
				App_vRefreshDisplay();
				SelectedOption = 0;
				UART_send_String("User returned to the main menu.\n\r");
			}
		}
	}
	/* Checks if the joystick btn is pressed and takes actions depending on the current menu */
	if (js_btn == Button_Pressed) {
		if (LocationOfTheMenu == MenuLocation_LedMenu) {
			if (SelectedOption) {
				leds[MenuRowElement].led_status = LED_ON;
				LED_vTurnON(&leds[MenuRowElement]);
				SelectedOption = 0;
			} else {
				leds[MenuRowElement].led_status = LED_OFF;
				LED_vTurnOFF(&leds[MenuRowElement]);
			}
		} else if (LocationOfTheMenu == MenuLocation_LevelMenu) {
			if (SelectedOption == 0) {
				LED_vSetLevel(LED_Level1);
			} else if (SelectedOption == 1) {
				//leds[MenuRowElement].led_level = LED_Level2;
				LED_vSetLevel(LED_Level2);
			} else if (SelectedOption == 2) {
				//leds[MenuRowElement].led_level = LED_Level2;
				LED_vSetLevel(LED_Level3);
			} else if (SelectedOption == 3) {
				//leds[MenuRowElement].led_level = LED_Level2;
				LED_vSetLevel(LED_Level4);
			} else if (SelectedOption == 4) {
				//leds[MenuRowElement].led_level = LED_Level2;
				LED_vSetLevel(LED_Level5);
			}
			LED_vUpdateLEDS(leds, NumberOfLeds);
		}
		UART_send_String("User has pressed the validation button.\n\r");
	}
	previous_state = state;
}

void App_vSetSelector(uint8 location) {
	App_vClearSelector();
	LCD_Char_xy(0, location, '*');
	SelectorLocation = location;
}

void App_vClearSelector() {
	LCD_Char_xy(0, SelectorLocation, ' ');
}
