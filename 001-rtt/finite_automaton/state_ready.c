#include "state_ready.h"
#include "state_machine.h"
#include "../drivers/lcd1602.h"
#include "../drivers/button.h"
#include "../drivers/uart.h"
#include "../task_manager/scheduler.h"
#include <avr/eeprom.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static char lcd_text_buffer[36] = { '\0' };
static char serial_text_buffer[36] = { '\0' };

void handle_ready_state(void)
{
	if (!is_ready_for_transition())
	{
		sprintf(serial_text_buffer, "%010lums-READY\r\n", mcu_operating_time);
		uart_transmit_data(serial_text_buffer);
		
		sprintf(lcd_text_buffer, "\rBest result:    \n%3ums           ", high_score);
		lcd1602_print(lcd_text_buffer);
		
		allow_state_transition();
		//user_reaction_time = 0;
	}
	
	if (is_button_event_unhandled() && is_ready_for_transition())
	{
		set_device_state(WAIT);
	}
}
