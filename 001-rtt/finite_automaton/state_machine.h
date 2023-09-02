#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <stdbool.h>
#include <stdint-gcc.h>

typedef enum
{
    READY, 
    WAIT, 
    MEASURING, 
    RESULT
} e_state;

extern uint16_t user_reaction_time;
extern uint16_t high_score;
extern char *prompt;

void init_state_machine(void);
void handle_device_state(void);
void set_device_state(e_state state);
void set_ready_for_transition(void);
bool is_ready_for_transition(void);

#endif /* STATE_MACHINE_H_ */