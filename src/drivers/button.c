/**
 * @author Maksym Palii
 * @brief Button driver
 * @version 1.0 
 */

#include "gpio.h"
#include "button.h"

void button_init(void)
{
    button_was_pressed = false;
}

bool button_pressed(void)
{
    return ((GPIO_GET_INPUT(BUTTON) == 0) && !button_was_pressed);
}

bool button_released(void)
{
    return ((GPIO_GET_INPUT(BUTTON) != 0) && button_was_pressed);
}