/**
 * @file    tarea1.c
 * @brief   Application entry point.
 */
#include "config.h"
#include "osek.h"
#include "gpio.h"
#include "leds.h"
#include "fsl_common.h"


#define TASK_A_ID	0
#define TASK_B_ID	1
#define TASK_C_ID	2

void task_A_function(void){
	green_led_on();
	SDK_DelayAtLeastUs(1000000,21000000);
	activate_task(TASK_B_ID);
	green_led_on();
	SDK_DelayAtLeastUs(1000000,21000000);
	terminate_task();
}

void task_B_function(void){
	red_led_on();
	SDK_DelayAtLeastUs(1000000,21000000);
	chain_task(TASK_C_ID);
	terminate_task();
}

void task_C_function(void){
	blue_led_on();
	SDK_DelayAtLeastUs(1000000,21000000);
	terminate_task();
}

int main(void) {
	task_t task_A;
	task_t task_B;
	task_t task_C;

	task_A.autostart = TRUE;
	task_A.priority = 0;
	task_A.state = READY;
	task_A.function = task_A_function;

	task_B.autostart = FALSE;
	task_B.priority = 1;
	task_B.state = READY;
	task_B.function = task_B_function;

	task_C.autostart = FALSE;
	task_C.priority = 2;
	task_C.state = READY;
	task_C.function = task_C_function;

	add_task(task_A);
	add_task(task_B);
	add_task(task_C);


	GPIO_init();
	os_init();

    while(TRUE) {

    }
    return 0 ;
}


