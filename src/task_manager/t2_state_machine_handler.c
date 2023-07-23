/**
 * @author Maksym Palii
 * @brief Task 2 - state machine handling implementation
 * @version 1.0 
 */

#include "t2_state_machine_handler.h"
#include "../state_machine/state_machine.h"

#define T2 1

// external variables
volatile uint8_t time_2;

void task_2(void)
{
	// re-initialize task 2 timer
	time_2 = T2;
	// task 2 itself
	handle_device_state();
}