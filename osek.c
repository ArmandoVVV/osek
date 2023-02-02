/*
 * osek.c
 *
 *  Created on: Feb 1, 2023
 *      Author: armando
 */

#include "osek.h"

//static task_t tasks[3] = {task_t task_A, task_t task_B, task_t task_C};

// TODO: hacer una funcion que cheque cual es la tarea actual en ejecución

static task_t tasks_g[3];
static task_t* running_task_g;

void add_task(task_t task){
	static uint8_t index = 0;

	tasks_g[index] = task;
	index++;
}

void activate_task(uint8_t task_id){
	// pone la tarea en running

	tasks_g[task_id].state = RUNNING;
	running_task_g = &tasks_g[task_id];

	tasks_g[task_id].function();

	//scheduler();
}


void chain_task(uint8_t task_id){
	// ejecuta una tarea despues de que termina la tarea actual
}


void terminate_task(void){
	uint8_t task_id;

//	for (task_id = 0; task_id < TOTAL_TASKS; task_id++){
//		if(RUNNING == tasks_g[task_id].state){
//			tasks_g[task_id].state = READY;
//		}
//	}

	running_task_g->state = READY;

}

void scheduler(void){
	// buscar cual es la siguiente tarea dependiendo de su estado y prioridad

//	uint8_t task_id;
//
//	terminate_task();
//
//	for (task_id = 0; task_id < TOTAL_TASKS; task_id++){
//		if(RUNNING == tasks_g[task_id].state){
//			tasks_g[task_id].state = READY;
//		}
//	}

}

// solo funciona para este caso en especifico, solo una tarea con autostart
// corre la tarea con autostart con mas prioridad
void os_init(void){
	uint8_t task_id;

	for (task_id = 0; task_id < TOTAL_TASKS; task_id++){
		if(tasks_g[task_id].autostart){
			activate_task(task_id);
		}
	}
}
