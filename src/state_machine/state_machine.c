/**
 * @author Maksym Palii
 * @brief State machine implementation
 * @version 1.0 
 */

#include "state_machine.h"
//#include "state_ready.h"

enum e_state device_state;
bool ready_for_state_transition;
bool button_event;

void handle_device_state(void)
{
    switch (device_state)
    {
        case READY: 
            //handle_ready_state(); 
            break;
        case WAIT: 
            //handle_wait_state(); 
            break;
        case MEASURING: 
            //handle_measuring_state(); 
            break;
        case RESULT: 
            //handle_result_state(); 
            break;	
	}
}

void init_state_machine(void)
{
    device_state = WAIT;
    ready_for_state_transition = false;
    button_event = false;
}
