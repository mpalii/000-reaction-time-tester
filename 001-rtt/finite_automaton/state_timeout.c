#include "state_timeout.h"
#include "state_machine.h"
#include "../drivers/button.h"
#include "../drivers/uart.h"
#include "../drivers/lcd1602.h"
#include "../task_manager/scheduler.h"
#include <stdio.h>

static char serial_text_buffer[36] = { '\0' };

void handle_timeout_state(void)
{
	if (!is_ready_for_transition())
	{
		sprintf(serial_text_buffer, "%010lums-TIMEOUT\r\n", mcu_operating_time);
		uart_transmit_data(serial_text_buffer);
		
		lcd1602_print("\r    Too slow    \n  try again...  ");
		
		allow_state_transition();
	}
	
	if (is_button_event_unhandled() && is_ready_for_transition())
	{
		set_device_state(WAIT);
	}
}