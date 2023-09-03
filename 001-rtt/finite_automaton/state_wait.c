#include "state_wait.h"
#include "state_machine.h"
#include "../drivers/lcd1602.h"
#include "../drivers/button.h"
#include "../drivers/uart.h"
#include "../task_manager/scheduler.h"
#include "../task_manager/button_handling_task.h"
#include <stdio.h>
#include <stdlib.h>


static uint16_t wait_time;

static char log_buffer[36] = { '\0' };

// External variables
volatile uint32_t mcu_operating_time;

void handle_wait_state(void)
{
	if (!is_ready_for_transition())
	{		
		
		user_reaction_time = 0;
		
		//lcd_print("#\r      Wait\n   for signal");
		lcd1602_print("\r      Wait      \n   for signal   ");
		
		srand((unsigned int) mcu_operating_time);
		wait_time = 999 + (rand() % 9000);
		
		//sprintf(log_buffer, "WAIT: %ums\r\n", wait_time);
		sprintf(log_buffer, "%010lums-WAIT: %ums\r\n", mcu_operating_time, wait_time);
		uart_transmit_data(log_buffer);
		
		fast_mode_enabled = true;
		allow_state_transition();
	}
	else
	{
		if (wait_time > 0) wait_time--;
	}
	
	if (is_button_event_unhandled())
	{
		fast_mode_enabled = false;
		//prompt = "\r    Too fast    \n  try again...  ";
		set_device_state(FALSE_START);
	}
	
	if (wait_time == 0)
	{
		set_device_state(MEASURING);
	}
}