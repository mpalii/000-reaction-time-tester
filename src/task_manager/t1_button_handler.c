/**
 * @author Maksym Palii
 * @brief Task 1 - control button handling implementation
 * @version 1.0 
 */

#include "t1_button_handler.h"
#include "../drivers/button.h"
#include "../state_machine/state_machine.h"

#define T1 15
#define ALT_T1 1

bool fast_mode_enabled;

// external variables
volatile uint8_t time_1
bool button_was_pressed;
bool button_event;

// Button handling
void task_1(void)
{
	// re-initialize task 1 time
	time_1 = fast_mode_enabled ? ALT_T1 : T1;

	// check whether button was pressed
	if (button_pressed() && ready_for_state_transition)
	{
		button_was_pressed = true;
		// button push handling
		button_event = true;
		// MAYBE DON't NEED?? ready_for_state_transition = ready_for_state_transition ? false : true;
	}
	
	// check whether button was released
	if (button_released())
	{
		button_was_pressed = false;
        // button release handling
		// NOP
	}
}

void init_task_1(void)
{
    time_1 = T1;
    fast_mode_enabled = false;
}
