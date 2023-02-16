/*
 * gpio.c
 *
 *  Created on: Nov 8, 2022
 *  Author: Armando Cabrales
 *  		Efren Díaz
 */

#include "config.h"
#include <gpio.h>
#include "fsl_gpio.h"
#include "fsl_port.h"

void GPIO_init(void)
{
	//Enable port clocks
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

	//Config mux port as GPIO
	RED_LED_PORT->PCR[RED_LED_PIN] |= GPIO_MUX_MASK;
	BLUE_LED_PORT->PCR[BLUE_LED_PIN] |= GPIO_MUX_MASK;
	GREEN_LED_PORT->PCR[GREEN_LED_PIN] |= GPIO_MUX_MASK;

	//Config GPIO direction as output
	RED_LED_GPIO->PDDR |= RED_LED_MASK;
	BLUE_LED_GPIO->PDDR |= BLUE_LED_MASK;
	GREEN_LED_GPIO->PDDR |= GREEN_LED_MASK;
}
