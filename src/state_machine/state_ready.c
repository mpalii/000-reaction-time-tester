#include "state_ready.h"
#include "state_machine.h"
#include "../drivers/lcd1602.h"
#include "../drivers/uart328p.h"

enum e_state device_state;

void handle_ready_state(void)
{
    if (!ready_for_state_transition) 
    {
        sprintf(text_buffer, "Best result: %d ms\r\nSystem is ready...\r\n", score);
        UART_transmit_array(text_buffer);
        ready_for_state_transition = true;
        user_reaction_time = 0;
        wait_time = 5233;
    }
	
    if (event_unhandled && ready_for_state_transition)
    {
        device_state = WAIT;
        ready_for_state_transition = false;
        event_unhandled = false;
	}
}
