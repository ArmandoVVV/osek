/*
 * osek.h
 *
 *  Created on: Feb 1, 2023
 *  Author: Armando Cabrales
 *  		Efren Díaz
 */

#ifndef OSEK_H_
#define OSEK_H_

#include "stdint.h"
#include "config.h"

#define TOTAL_TASKS		3
#define MAX_TASKS		10
#define STACK_SIZE		100


typedef enum{
	READY,
	RUNNING,
	SUSPENDED,
	WAITING
}task_state_t;

typedef struct{
	uint8_t priority;
	void (*function)(void);	  // apuntador a inicio de la tarea
	uint8_t task_id;
	boolean_t autostart;
	task_state_t state;
	uint32_t *sp;
	uint32_t stack[STACK_SIZE];
}task_t;


void activate_task(uint8_t task_id);
void chain_task(uint8_t task_id);
void terminate_task(void);
void os_init(void);
void scheduler(void);

uint8_t add_task(task_t task);

#endif /* OSEK_H_ */
