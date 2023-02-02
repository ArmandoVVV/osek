/**
 * @file    tarea1.c
 * @brief   Application entry point.
 */
#include "config.h"
#include "osek.h"


#define TASK_A_ID	1
#define TASK_B_ID	2
#define TASK_C_ID	3

void task_A_function(void){
	activate_task(TASK_B_ID);
}

void task_B_function(void){
	chain_task(TASK_C_ID);
}

void task_C_function(void){
	terminate_task();
}

int main(void) {
	task_t task_A;
	task_t task_B;
	task_t task_C;

	task_A.autostart = TRUE;
	task_A.priority = 0;
	task_A.function = task_A_function;

	task_B.autostart = FALSE;
	task_B.priority = 1;
	task_B.function = task_B_function;

	task_C.autostart = FALSE;
	task_C.priority = 2;
	task_C.function = task_C_function;

	add_task(task_A);
	add_task(task_B);
	add_task(task_C);


	os_init();

    while(TRUE) {

    }
    return 0 ;
}


