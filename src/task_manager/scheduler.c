/**
 * @author Maksym Palii
 * @brief Simple round robbin scheduler
 * @version 1.0 
 */

#include <avr/interrupt.h>
#include "scheduler.h"
#include "t1_button_handler.h"
#include "t2_state_machine_handler.h"

volatile uint8_t time_1;
volatile uint8_t time_2;

void init_timer(void);
void init_tasks(void);

ISR (TIMER0_COMPA_vect)
{
    if (time_1 > 0) --time_1;
    if (time_2 > 0) --time_2;
}

void init_scheduler(void)
{
    init_timer();
    init_tasks();
}

/****************************************************************************/
/* Set up timer 0 for 1 ms timebase                                         */
/* (1024 (prescaler) * 18 (OCR0A + 1)) / 18_432_000 MHz = 0.001s = 1ms      */
/****************************************************************************/
void init_timer(void)
{
    // TCCR0A – Timer/Counter0 Control Register channel A
    TCCR0A = _BV(WGM01);            // Clear Timer on Compare Match (CTC) mode (only works with channel)
	
    // TCCR0B – Timer/Counter0 Control Register channel B
    TCCR0B = _BV(CS02) | _BV(CS00); // clk/1024 (From prescaler)
	
    // OCR0A – Timer/Counter0 Output Compare Register channel A
    OCR0A =	17;                    //set the compare reg to 18 time ticks (zero based)
	
    // TIMSK0 – Timer/Counter0 Interrupt Mask Register
    TIMSK0 = _BV(OCIE0A);           // Timer/Counter0 Output Compare Match channel A Interrupt Enable
}

void init_tasks(void)
{
	init_task_1();
	init_task_2();
}

void launch_tasks(void)
{
    while (true) 
    {
        if (time_1 == 0) { task_1(); }
        if (time_2 == 0) { task_2(); } 
    }
}
