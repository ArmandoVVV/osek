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
#include "osek.h"


void PORTD_IRQHandler(void){
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOD); // TODO: SDK

	// funcion solo para probar la interrupcion
	activate_task(2);


	GPIO_PortClearInterruptFlags(GPIOD, irq_status); // TODO: SDK
}

void PORTA_IRQHandler(void){
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOA); // TODO: SDK

	// funcion solo para probar la interrupcion
	terminate_task();


	GPIO_PortClearInterruptFlags(GPIOA, irq_status); // TODO: SDK
}


void GPIO_init(void){
	//Enable port clocks
	EnablePortClock(SIM_SCGC5_PORTC_MASK);
	EnablePortClock(SIM_SCGC5_PORTA_MASK);
	EnablePortClock(SIM_SCGC5_PORTE_MASK);
	EnablePortClock(SIM_SCGC5_PORTD_MASK);

	//Config mux port as GPIO
	SetPin_GPIO(RED_LED_PORT,RED_LED_PIN);
	SetPin_GPIO(BLUE_LED_PORT,BLUE_LED_PIN);
	SetPin_GPIO(GREEN_LED_PORT,GREEN_LED_PIN);
	SetPin_GPIO(SW2_PORT,SW2_PIN);
	SetPin_GPIO(SW3_PORT,SW3_PIN);


	//Config GPIO direction as output
	SET_PIN_AS_OUTPUT(RED_LED_GPIO, RED_LED_MASK);
	SET_PIN_AS_OUTPUT(BLUE_LED_GPIO, BLUE_LED_MASK);
	SET_PIN_AS_OUTPUT(GREEN_LED_GPIO, GREEN_LED_MASK);


	//Config GPIO direction as input
	SET_PIN_AS_INPUT(SW2_GPIO, SW2_MASK);
	SET_PIN_AS_INPUT(SW3_GPIO, SW3_MASK);

	// Config interruption
	SET_PIN_INTERRUPT(SW2_PORT, SW2_PIN, kPORT_InterruptFallingEdge);
	SET_PIN_INTERRUPT(SW3_PORT, SW3_PIN, kPORT_InterruptFallingEdge);

}
