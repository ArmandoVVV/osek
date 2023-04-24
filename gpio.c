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
	GPIO_PortClearInterruptFlags(GPIOD, irq_status); // TODO: SDK
	//activate_task(2);

}

void PORTA_IRQHandler(void){
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOA); // TODO: SDK
	GPIO_PortClearInterruptFlags(GPIOA, irq_status); // TODO: SDK
	terminate_task();

}


void GPIO_init(void)
{
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
	RED_LED_GPIO->PDDR |= RED_LED_MASK; //TODO: Convert to a macro; Set_GPIO_Output(GPIO,MASK_PIN) ({GPIO->PDDR |= MASK_PIN})
	BLUE_LED_GPIO->PDDR |= BLUE_LED_MASK;
	GREEN_LED_GPIO->PDDR |= GREEN_LED_MASK;

	//Config GPIO direction as input
	SW2_GPIO->PDDR &= GPIO_FIT_REG(~(SW2_MASK));
	SW3_GPIO->PDDR &= GPIO_FIT_REG(~(SW3_MASK));

	// Config interruption
	SW2_PORT->PCR[SW2_PIN] = (SW2_PORT->PCR[SW2_PIN] & ~PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(kPORT_InterruptFallingEdge);
	SW3_PORT->PCR[SW3_PIN] = (SW3_PORT->PCR[SW3_PIN] & ~PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(kPORT_InterruptFallingEdge);

}
