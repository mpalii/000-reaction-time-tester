#include "state_result.h"
#include "state_machine.h"
#include "../drivers/lcd1602.h"
#include "../drivers/button.h"
#include "../drivers/uart.h"
#include "../task_manager/eeprom_score_saving_task.h"
#include <stdio.h>

static char lcd_text_buffer[37];
static char serial_text_buffer[37];

// External variables
volatile uint32_t mcu_operating_time;

void handle_result_state(void)
{
	if (!is_ready_for_transition())
	{		
		sprintf(serial_text_buffer, "%010lums-RESULT\r\n", mcu_operating_time);
		uart_transmit_data(serial_text_buffer);
		
		if (user_reaction_time < high_score)
		{
			high_score = user_reaction_time;
			eeprom_save_score(high_score);
		}
		
		sprintf(lcd_text_buffer, "\rYour result is: \n%3ums           ", user_reaction_time);
		lcd1602_print(lcd_text_buffer);
		
		allow_state_transition();
	}
	

	if (is_button_event_unhandled() && is_ready_for_transition())
	{
		set_device_state(READY);
	}
}