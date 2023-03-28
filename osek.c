/*
 * osek.c
 *
 *  Created on: Feb 1, 2023
 *  Author: Armando Cabrales
 *  		Efren Díaz
 */

#include "osek.h"
#include "fsl_port.h"

static task_t tasks_g[MAX_TASKS];
static task_t* running_task_g;

uint8_t add_task(task_t task){
	static uint8_t index = 0;

	tasks_g[index] = task;
	index++;

	return index - 1;
}

void activate_task(uint8_t task_id){
	// pone la tarea en ready

	tasks_g[task_id].state = READY;

	scheduler();
}


void chain_task(uint8_t task_id){
	// termina la tarea actual y ejecuta otra tarea
	running_task_g->state = SUSPENDED;
	tasks_g[task_id].state = READY;
	scheduler();

}


void terminate_task(void){
	running_task_g->state = SUSPENDED;
	scheduler();
}

void scheduler(void){
	uint8_t task_id;
	int8_t priority;

	for(priority = 10; priority >= 0; priority--){
		for(task_id = 0; task_id < TOTAL_TASKS; task_id++){
			if(tasks_g[task_id].state == READY && tasks_g[task_id].priority == priority){
				tasks_g[task_id].state = RUNNING;
				running_task_g = &tasks_g[task_id];
				tasks_g[task_id].function();
				break;
			}
		}
	}
}

void context_switch(void){
	static uint32_t r0 asm("r0");
	uint8_t i = 0;

	running_task_g->sp = &r0;
	do{
		running_task_g->stack[i] = *running_task_g->sp;
		running_task_g->sp += 32;
		i++;
	}while(i < 8);

}

void os_init(void){
	uint8_t task_id;

	for (task_id = 0; task_id < TOTAL_TASKS; task_id++){
		if(tasks_g[task_id].autostart){
			activate_task(task_id);
		}
	}

	scheduler();
}
