/* nvic.c
 *	\file
 *	\brief
 *	 *  Author: Armando Cabrales
 *  		Efren Díaz
 *	\date	Sep 20, 2022
 */

#include "NVIC.h"
#include "MK66F18.h"

void NVIC_enable_interrupt_and_priority(interrupt_t interrupt_number, priority_level_t priority)
{
	/**This functions are part of CMSIS Core functions*/
	/**It enables the IRQ*/
	NVIC_EnableIRQ(interrupt_number);
	/**It Sets the priority of the IRQ*/
	NVIC_SetPriority(interrupt_number, priority);
}


void NVIC_set_basepri_threshold(priority_level_t priority)
{
	/**Sets the threshold level to attend interrupts*/
	/**A shift is needed to align in a correct manner the data in priority inside BASEPRI register*/
	__set_BASEPRI(priority << (8 - __NVIC_PRIO_BITS));
}

