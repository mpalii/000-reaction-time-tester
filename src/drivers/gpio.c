/**
 * @author Maksym Palii
 * @brief GPIO initialization
 * @version 1.0
 * @date 13-July-2023
 */

#include "gpio.h"

void gpio_init(void)
{
    GPIO_SET_INPUT(BUTTON);
    GPIO_SET_OUTPUT(LED);
    GPIO_SET_OUTPUT(BUZZER);
    GPIO_SET_OUTPUT(LCD_1602_PD4);
    GPIO_SET_OUTPUT(LCD_1602_PD5);
    GPIO_SET_OUTPUT(LCD_1602_PD6);
    GPIO_SET_OUTPUT(LCD_1602_PD7);
    GPIO_SET_OUTPUT(LCD_1602_RS);
    GPIO_SET_OUTPUT(LCD_1602_E);
}
