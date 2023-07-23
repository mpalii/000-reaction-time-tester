#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

/**
 * @author Maksym Palii
 * @brief State machine
 * @version 1.0 
 */

enum e_state
{
    READY, 
    WAIT, 
    MEASURING, 
    RESULT
};

extern enum e_state device_state;
extern bool ready_for_state_transition;
extern bool button_event;

void init_state_machine(void);
void handle_device_state(void);

#endif /* _STATE_MACHINE_H_ */