/*
 * leds.h
 *
 *  Created on: Feb 10, 2023
 *  Author: Armando Cabrales
 *  		Efren Díaz
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "config.h"
#include "fsl_gpio.h"

#define RGB_off() ({RED_LED_GPIO->PSOR |= RED_LED_MASK; BLUE_LED_GPIO->PSOR |= BLUE_LED_MASK; GREEN_LED_GPIO->PSOR |= GREEN_LED_MASK;})
#define Green_led_on() ({RGB_off(); GREEN_LED_GPIO->PCOR |= GREEN_LED_MASK;})
#define Blue_led_on() ({RGB_off(); BLUE_LED_GPIO->PCOR |= BLUE_LED_MASK;})
#define Red_led_on() ({RGB_off(); RED_LED_GPIO->PCOR |= RED_LED_MASK;})


#endif /* LEDS_H_ */
