/*
 * config.h
 *
 * 		\brief
 *  	Created on:
 *  Author: Armando Cabrales
 *  		Efren Díaz
 */

#ifndef CONFIG_H_
#define CONFIG_H_

typedef enum{
	FALSE,
	TRUE
} boolean_t;

//GPIO
#define RED_LED_GPIO			(GPIOC)
#define BLUE_LED_GPIO			(GPIOA)
#define GREEN_LED_GPIO			(GPIOE)
#define SW2_GPIO				(GPIOD)
#define SW3_GPIO				(GPIOA)

//PORTS
#define RED_LED_PORT			(PORTC)
#define BLUE_LED_PORT			(PORTA)
#define GREEN_LED_PORT			(PORTE)
#define SW2_PORT				(PORTD)
#define SW3_PORT				(PORTA)

//PIN
#define RED_LED_PIN				(9u)
#define BLUE_LED_PIN			(11u)
#define GREEN_LED_PIN			(6u)
#define	SW2_PIN					(11)
#define	SW3_PIN					(10)

// MASKS
#define RED_LED_MASK			(1 << RED_LED_PIN)
#define BLUE_LED_MASK			(1 << BLUE_LED_PIN)
#define GREEN_LED_MASK			(1 << GREEN_LED_PIN)
#define GPIO_MUX_MASK			(1 << 8)
#define SW2_MASK				(1 << SW2_PIN)
#define SW3_MASK				(1 << SW3_PIN)


#endif /* CONFIG_H_ */
