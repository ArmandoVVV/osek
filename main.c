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
#include "fsl_common.h"


#define TASK_A_ID	0
#define TASK_B_ID	1
#define TASK_C_ID	2
#define US_TO_DELAY	2000000

void task_A_function(void){
	green_led_on();
	SDK_DelayAtLeastUs(US_TO_DELAY,CLOCK_GetFreq(kCLOCK_CoreSysClk));
	activate_task(TASK_B_ID);
	green_led_on();
	SDK_DelayAtLeastUs(US_TO_DELAY,CLOCK_GetFreq(kCLOCK_CoreSysClk));
	rgb_off();
	terminate_task();
}

void task_B_function(void){
	red_led_on();
	SDK_DelayAtLeastUs(US_TO_DELAY,CLOCK_GetFreq(kCLOCK_CoreSysClk));
	chain_task(TASK_C_ID);
	terminate_task();
}

void task_C_function(void){
	blue_led_on();
	SDK_DelayAtLeastUs(US_TO_DELAY,CLOCK_GetFreq(kCLOCK_CoreSysClk));
	terminate_task();
}

int main(void) {
	task_t task_A = {
			.autostart = TRUE,
			.priority = 0,
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

	add_task(task_A);
	add_task(task_B);
	add_task(task_C);


	GPIO_init();
	os_init();

    while(TRUE) {

    }
    return 0 ;
}


