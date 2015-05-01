/*
 * network_rtos.cc
 *
 *  Created on: Mar 9, 2015
 *      Author: Gideon
 */

/* Scheduler includes. */
extern "C" {
	#include "small_printf.h"
	#include "FreeRTOS.h"
	#include "FreeRTOSConfig.h"
	#include "task.h"
	#include "semphr.h"
	#include "itu.h"
	#include "small_printf.h"
}

#include "init_function.h"

#define MAIN_LOOP_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )

SemaphoreHandle_t xSemaphore;

void main_loop(void *a);

int main (void)
{
	/* When re-starting a debug session (rather than cold booting) we want
	to ensure the installed interrupt handlers do not execute until after the
	scheduler has been started. */
	portDISABLE_INTERRUPTS();

	xTaskCreate( main_loop, "Main Event Loop", configMINIMAL_STACK_SIZE, NULL, MAIN_LOOP_TASK_PRIORITY, NULL );

	xSemaphore = xSemaphoreCreateMutex();

	/* Finally start the scheduler. */
	vTaskStartScheduler();

	/* Should not get here as the processor is now under control of the
	scheduler! */

   	return 0;
}
