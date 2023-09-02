#include "state_measuring.h"
#include "state_machine.h"
#include "../drivers/button.h"
#include "../drivers/buzzer.h"
#include "../drivers/led.h"
#include "../drivers/uart.h"
#include "../task_manager/scheduler.h"
#include "../task_manager/button_handling_task.h"
#include <stdio.h>

static char serial_text_buffer[36] = { '\0' };

// External variables
volatile uint32_t mcu_operating_time;
bool fast_mode_enabled;

void handle_measuring_state(void)
{
	if (!is_ready_for_transition())
	{
		sprintf(serial_text_buffer, "%010lums-MEASURING\r\n", mcu_operating_time);
		uart_transmit_data(serial_text_buffer);
		led_on();
		buzzer_on();
		set_ready_for_transition();
	}
	else
	{
		user_reaction_time++;
	}
	
	if (is_button_event_unhandled()) {
		fast_mode_enabled = false;
		
		set_device_state(RESULT);
		
		led_off();
		buzzer_off();
	}
	
	if (user_reaction_time == 1000)
	{
		led_off();
		buzzer_off();
		fast_mode_enabled = false;

		prompt = "\r    Too slow    \n  try again...  ";
		set_device_state(READY);
	}
}