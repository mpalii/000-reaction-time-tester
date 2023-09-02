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

static inline void print_message(void);

void handle_ready_state(void)
{
	if (!is_ready_for_transition())
	{
		sprintf(serial_text_buffer, "%010lums-READY\r\n", mcu_operating_time);
		uart_transmit_data(serial_text_buffer);
		print_message();		
		set_ready_for_transition();
		user_reaction_time = 0;
	}
	
	if (is_button_event_unhandled() && is_ready_for_transition())
	{
		set_device_state(WAIT);

	}
}

static inline void print_message(void)
{
	if (prompt != NULL) 
	{
		lcd1602_print(prompt);
	}
	else 
	{	
		//uint16_t score = eeprom_read_word(SCORE_ADDRESS);
		//sprintf(text_buffer, "#\r  Best result:\n%ums", score);
		sprintf(lcd_text_buffer, "\rBest result:    \n%3ums           ", high_score);
		lcd1602_print(lcd_text_buffer);
	}
}
