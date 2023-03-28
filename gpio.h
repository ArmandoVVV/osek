// gpio.h
/**
*	\file
*	\brief
*	\
 *  Author: Armando Cabrales
 *  		Efren Díaz
*
*/

#ifndef GPIO_H_
#define GPIO_H_

#include "stdint.h"

#define EnablePortClock(MASK) ({SIM->SCGC5 |= MASK;})
#define SetPin_GPIO(PORT,PIN) ({PORT->PCR[PIN] |= GPIO_MUX_MASK;})

// MACROS AUN NO PROBADAS  // SI LAS INTERRUPCIONES NO JALAN ES CULPA DE ESTO
#define SET_PIN_INTERRUPT(PORT, PIN, INTERRUPT_TYPE) ({(PORT->PCR[PIN] & ~PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(INTERRUPT_TYPE);})
#define SET_PIN_AS_INPUT(GPIO,MASK) ({GPIO->PDDR &= GPIO_FIT_REG(~(MASK));})
#define	SET_PIN_AS_OUTPUT(GPIO,MASK) ({GPIO->PDDR |= MASK;})



/*! These constants are used to select an specific port in the different API functions*/
typedef enum{GPIO_A, /*!< Definition to select GPIO A */
			 GPIO_B, /*!< Definition to select GPIO B */
			 GPIO_C, /*!< Definition to select GPIO C */
			 GPIO_D, /*!< Definition to select GPIO D */
			 GPIO_E, /*!< Definition to select GPIO E */
			 GPIO_F  /*!< Definition to select GPIO F */
} gpio_name_t;


void GPIO_init(void);

#endif /* GPIO_H_ */
