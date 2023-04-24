/**
 * @file    tarea1.c
 * @brief   Application entry point.
 *  Author: Armando Cabrales
 *  		Efren Díaz
 */
#include "config.h"
#include <stdio.h>
#include "osek.h"
#include "gpio.h"
#include "leds.h"
#include "nvic.h"

#define DELAY	2000000
#define CLOCK_FREQ 21000000


uint8_t g_task_A_ID;
uint8_t g_task_B_ID;
uint8_t g_task_C_ID;

void delay(uint32_t delay){
	volatile uint32_t i = 0;

	while(i < DELAY){ //TODO: Make a variable with the core freq, to compare.
		i++;
	}
}

void task_A_function(void){
	Green_led_on();
	delay(DELAY); //TODO: Save core freq in a variable, make this more precision
	activate_task(g_task_B_ID,kFromNormalExec); //TODO: Is not needed to send the task ID.
	Green_led_on();
	delay(DELAY);
	RGB_off();
	terminate_task();
}

void task_B_function(void){
	Red_led_on();
	delay(DELAY);
	RGB_off();
	chain_task(g_task_C_ID,kFromNormalExec);
}

void task_C_function(void){
	Blue_led_on();
	delay(DELAY);
	RGB_off();
	terminate_task();
}

int main(void) {
	task_t task_A = {						//TODO: Move this variable out of main
			.autostart = kAutoStart,
			.priority = 0,
			.function = task_A_function,
	};

	task_t task_B = {
			.autostart = kStartSuspended,
			.priority = 1,
			.function = task_B_function,
	};

	task_t task_C = {
			.autostart = kStartSuspended,
			.priority = 2,
			.function = task_C_function,
	};
	g_task_A_ID = task_create(task_A);
	if (-1 == g_task_A_ID)
			printf("Task 1 creation failed\r\n");
	g_task_B_ID = task_create(task_B);
	if (-1 == g_task_B_ID)
				printf("Task 2 creation failed\r\n");
	g_task_C_ID = task_create(task_C);
	if (-1 == g_task_C_ID)
				printf("Task 3 creation failed\r\n");

//	NVIC_global_enable_interrupts;
//	NVIC_set_BASEPRI_threshold(PRIORITY_3);
//
//	NVIC_enable_interrupt(PORTD_IRQ);
//	NVIC_set_priority(PORTD_IRQ, PRIORITY_1);
//	NVIC_enable_interrupt(PORTA_IRQ);
//	NVIC_set_priority(PORTA_IRQ, PRIORITY_1);


	NVIC_SetPriority(PendSV_IRQn, 0xFF);
	GPIO_init();
	os_init();

    while(TRUE) {

    }
    return 0 ;
}
