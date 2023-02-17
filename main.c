/**
 * @file    tarea1.c
 * @brief   Application entry point.
 *  Author: Armando Cabrales
 *  		Efren Díaz
 */
#include "config.h"
#include "osek.h"
#include "gpio.h"
#include "leds.h"


#define TASK_A_ID	0
#define TASK_B_ID	1
#define TASK_C_ID	2
#define US_TO_DELAY	20000000
#define CLOCK_FREQ 21000000

void delay(uint32_t delay){
	uint8_t i;

	while(i < 100){
		i++;
	}
}

void task_A_function(void){
	Green_led_on();
	delay(US_TO_DELAY); //TODO: Save core freq in a variable, make this more precision
	activate_task(TASK_B_ID); //TODO: Is not needed to send the task ID.
	Green_led_on();
	delay(US_TO_DELAY);
	RGB_off();
	terminate_task();
}

void task_B_function(void){
	Red_led_on();
	delay(US_TO_DELAY);
	chain_task(TASK_C_ID); //TODO: Remade this function, this will terminate this task and continue th next task.
	terminate_task();		//TODO: So far this is not needed.
}

void task_C_function(void){
	Blue_led_on();
	delay(US_TO_DELAY);
	terminate_task();
}

int main(void) {
	task_t task_A = {						//TODO: Move this variable out of main
			.autostart = TRUE,
			.priority = 0,					//TODO: Priorites are inversed.
			.state = SUSPENDED,
			.function = task_A_function,
	};

	task_t task_B = {
			.autostart = FALSE,
			.priority = 1,
			.state = SUSPENDED,
			.function = task_B_function,
	};

	task_t task_C = {
			.autostart = FALSE,
			.priority = 2,
			.state = SUSPENDED,
			.function = task_C_function,
	};

	add_task(task_A); //TODO: This is the global solution for the variables in main
	add_task(task_B); //TODO: With return: task_A_ID = add_task(task_A)
	add_task(task_C);


	GPIO_init();
	os_init();

    while(TRUE) {

    }
    return 0 ;
}
