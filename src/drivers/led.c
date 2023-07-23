/**
 * @author Maksym Palii
 * @brief LED driver
 * @version 1.0 
 */

#include "gpio.h"
#include "led.h"

void led_init(void)
{
    // nop
}

void led_on(void) 
{
    GPIO_HIGH(LED);
}

void led_off(void)
{
    GPIO_LOW(LED);
}
