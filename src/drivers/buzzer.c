/**
 * @author Maksym Palii
 * @brief Piezoelectric buzzer (based on Timer/Counter2)
 * @version 1.0
 * @date 21-July-2023
 */

#include "gpio.h"
#include "buzzer.h"

/****************************************************************************/
/* Set up Timer/Counter2 for 880Hz frequency generation                     */
/* (256 (prescaler) * 82(OCR2A + 1)) / 18_432_000 MHz = 0.001139s           */
/****************************************************************************/
void buzzer_init(void)
{
    // TCCR2A – Timer/Counter2 Control Register channel A
    TCCR2A = _BV(COM2A0) | _BV(WGM21);

    // OCR2A – Timer/Counter2 Output Compare Register channel A
    OCR2A = 81;    //set the compare reg to 82 ticks (zero based)
}

void buzzer_on(void)
{
    // TCCR2B – Timer/Counter2 Control Register channel B - clkT2S/256
    TCCR2B |= _BV(CS22) | _BV(CS21);
}

void buzzer_off(void)
{
    // TCCR2B – Timer/Counter2 Control Register channel B - Timer/Counter stopped
    TCCR2B &= ~(_BV(CS22) | _BV(CS21) | _BV(CS20));
}
