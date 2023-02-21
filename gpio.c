/*
 * gpio.c
 *
 *  Created on: Nov 8, 2022
 *  Author: Armando Cabrales
 *  		Efren Díaz
 */

#include "config.h"
#include <gpio.h>
#include "osek.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

void PORTD_IRQHandler(void){
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOD); // TODO: SDK

	activate_task(2);


	GPIO_PortClearInterruptFlags(GPIOD, irq_status); // TODO: SDK
}

void PORTA_IRQHandler(void){
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOA); // TODO: SDK

	terminate_task();


	GPIO_PortClearInterruptFlags(GPIOA, irq_status); // TODO: SDK
}


void GPIO_init(void)
{
	//Enable port clocks
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

	//Config mux port as GPIO
	RED_LED_PORT->PCR[RED_LED_PIN] |= GPIO_MUX_MASK;
	BLUE_LED_PORT->PCR[BLUE_LED_PIN] |= GPIO_MUX_MASK;
	GREEN_LED_PORT->PCR[GREEN_LED_PIN] |= GPIO_MUX_MASK;
	SW2_PORT->PCR[SW2_PIN] |= GPIO_MUX_MASK;
	SW3_PORT->PCR[SW3_PIN] |= GPIO_MUX_MASK;

	//Config GPIO direction as output
	RED_LED_GPIO->PDDR |= RED_LED_MASK;
	BLUE_LED_GPIO->PDDR |= BLUE_LED_MASK;
	GREEN_LED_GPIO->PDDR |= GREEN_LED_MASK;

	//Config GPIO direction as INPUT
	SW2_GPIO->PDDR &= GPIO_FIT_REG(~(SW2_MASK));
	SW3_GPIO->PDDR &= GPIO_FIT_REG(~(SW3_MASK));

	// Config interruption
	SW2_PORT->PCR[SW2_PIN] = (SW2_PORT->PCR[SW2_PIN] & ~PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(kPORT_InterruptFallingEdge);
	SW3_PORT->PCR[SW3_PIN] = (SW3_PORT->PCR[SW3_PIN] & ~PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(kPORT_InterruptFallingEdge);

}
