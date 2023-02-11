/*
 * gpio.c
 *
 *  Created on: Nov 8, 2022
 *      Author: armando
 */

#include "config.h"
#include <gpio.h>
#include "fsl_gpio.h"
#include "fsl_port.h"

volatile static gpio_interrupt_flags_t g_intr_status_flag = {0};

static void (*gpio_A_callback)(uint32_t flags) = 0;
static void (*gpio_B_callback)(uint32_t flags) = 0;
static void (*gpio_C_callback)(uint32_t flags) = 0;
static void (*gpio_D_callback)(uint32_t flags) = 0;
static void (*gpio_E_callback)(uint32_t flags) = 0;


void GPIO_callback_init(gpio_name_t gpio, void (*handler)(uint32_t flags))
{
	switch(gpio){
		case GPIO_A:
			gpio_A_callback = handler;
			break;

		case GPIO_B:
			gpio_B_callback = handler;
			break;

		case GPIO_C:
			gpio_C_callback = handler;
			break;

		case GPIO_D:
			gpio_D_callback = handler;
			break;

		default: // gpio == GPIO_E
			gpio_E_callback = handler;
	}
}

void PORTC_IRQHandler(void){
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOC);

	if(gpio_C_callback)
	{
		gpio_C_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOC, irq_status);


}

void PORTB_IRQHandler(void){
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOB);

	if(gpio_B_callback)
	{
		gpio_B_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOB, irq_status);
}

void GPIO_init(void)
{

	gpio_pin_config_t gpio_output_config = {
			        kGPIO_DigitalOutput,
			        1,
			    };


	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortE);


	PORT_SetPinMux(RED_LED_PORT, RED_LED_PIN, kPORT_MuxAsGpio);
	GPIO_PinInit(RED_LED_GPIO, RED_LED_PIN, &gpio_output_config);

	PORT_SetPinMux(BLUE_LED_PORT, BLUE_LED_PIN, kPORT_MuxAsGpio);
	GPIO_PinInit(BLUE_LED_GPIO, BLUE_LED_PIN, &gpio_output_config);

	PORT_SetPinMux(GREEN_LED_PORT, GREEN_LED_PIN, kPORT_MuxAsGpio);
	GPIO_PinInit(GREEN_LED_GPIO, GREEN_LED_PIN, &gpio_output_config);



}
