/*
 * osek.c
 *
 *  Created on: Feb 1, 2023
 *      Author: armando
 */

#include "osek.h"

static task_t tasks_g[3];
static task_t* running_task_g;

void add_task(task_t task){
	static uint8_t index = 0;

	tasks_g[index] = task;
	index++;
}

void activate_task(uint8_t task_id){
	// pone la tarea en ready

	tasks_g[task_id].state = READY;

	scheduler();
}


void chain_task(uint8_t task_id){
	// ejecuta una tarea despues de que termina la tarea actual
	 tasks_g[task_id].state = WAITING;

}


void terminate_task(void){
	running_task_g->state = SUSPENDED;
	scheduler();
}

void scheduler(void){
	uint8_t task_id;

	for(task_id = 0; task_id < TOTAL_TASKS; task_id++){
		if(WAITING == tasks_g[task_id].state){
			 tasks_g[task_id].state = RUNNING;
			 running_task_g = &tasks_g[task_id];
			 tasks_g[task_id].function();
		}
		else if(READY ==  tasks_g[task_id].state){
			switch(tasks_g[task_id].priority){
				case 0:
					tasks_g[task_id].state = RUNNING;
					running_task_g = &tasks_g[task_id];
					tasks_g[task_id].function();
					break;

				case 1:
					tasks_g[task_id].state = RUNNING;
					running_task_g = &tasks_g[task_id];
					tasks_g[task_id].function();
					break;

				case 2:
					tasks_g[task_id].state = RUNNING;
					running_task_g = &tasks_g[task_id];
					tasks_g[task_id].function();
					break;

				default:
					// ignore
					break;

			}
		}
	}

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
