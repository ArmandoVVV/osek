/*
 * leds.c
 *
 *  Created on: Feb 10, 2023
 *  Author: Armando Cabrales
 *  		Efren Díaz
 */

#include "leds.h"
#include "gpio.h"
#include "config.h"
#include "fsl_gpio.h"

void red_led_on(void){
	rgb_off();
	GPIO_PortClear(RED_LED_GPIO, RED_LED_MASK);
}

void blue_led_on(void){
	rgb_off();
	GPIO_PortClear(BLUE_LED_GPIO, BLUE_LED_MASK);

}

void green_led_on(void){
	rgb_off();
	GPIO_PortClear(GREEN_LED_GPIO, GREEN_LED_MASK);

}

void rgb_off(void){
	GPIO_PortSet(RED_LED_GPIO, RED_LED_MASK);
	GPIO_PortSet(BLUE_LED_GPIO, BLUE_LED_MASK);
	GPIO_PortSet(GREEN_LED_GPIO, GREEN_LED_MASK);
}
