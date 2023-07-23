/**
 * @author Maksym Palii
 * @brief LCD1602, 4bit mode
 * @version 1.0
 * @date 19-July-2023
 */

#include "gpio.h"
#include <util/delay.h>

#define MOVE_CURSOR_TO_POSITION_0_LINE_1 0x80
#define MOVE_CURSOR_TO_POSITION_0_LINE_2 0xC0
#define CLEAR_DISPLAY 0x01

// internal function prototypes
static inline void enable_4bit_mode(void);
static inline void configure_display(void);
void send_command_4bit_mode(uint8_t command);
void send_data_4bit_mode(uint8_t data);

void lcd1602_init(void)
{
    enable_4bit_mode();
    configure_display();
}

void lcd1602_move_cursor_row_1(void)
{
    send_command_4bit_mode(MOVE_CURSOR_TO_POSITION_0_LINE_1);
}

void lcd1602_move_cursor_row_2(void)
{
    send_command_4bit_mode(MOVE_CURSOR_TO_POSITION_0_LINE_2);
}

void lcd1602_render_message(char* message)
{
    uint8_t i = 0;
    while (message[i] != '\0')
    {
        send_data_4bit_mode(message[i++]);
    }
}

void lcd1602_clear_display(void)
{
    send_command_4bit_mode(CLEAR_DISPLAY);
}

static inline void enable_4bit_mode(void)
{
    // Special case of 'Function Set'
    _delay_ms(100);

    GPIO_HIGH(LCD_1602_PD4);
    GPIO_HIGH(LCD_1602_PD5);

    GPIO_HIGH(LCD_1602_E);
    _delay_us(37);
    GPIO_LOW(LCD_1602_E);
    _delay_us(37);

    // Special case of 'Function Set'
    _delay_ms(5);

    GPIO_HIGH(LCD_1602_PD4);
    GPIO_HIGH(LCD_1602_PD5);

    GPIO_HIGH(LCD_1602_E);
    _delay_us(37);
    GPIO_LOW(LCD_1602_E);
    _delay_us(37);

    // Special case of 'Function Set'
    _delay_us(100);

    GPIO_HIGH(LCD_1602_PD4);
    GPIO_HIGH(LCD_1602_PD5);

    GPIO_HIGH(LCD_1602_E);
    _delay_us(37);
    GPIO_LOW(LCD_1602_E);
    _delay_us(37);

    // Set interface to be 4 bits long
    _delay_us(100);

    GPIO_LOW(LCD_1602_PD4);
    GPIO_HIGH(LCD_1602_PD5);

    GPIO_HIGH(LCD_1602_E);
    _delay_us(37);
    GPIO_LOW(LCD_1602_E);
    _delay_us(37);

    _delay_us(100);
}

static inline void configure_display(void)
{
    send_command_4bit_mode(0b00101000);	// Real 'Function Set' - 4bit mode, 2 lines, 5x8 font
    _delay_us(53);
    send_command_4bit_mode(0b00001100);	// 'Display ON/OFF Control' display on, cursor off and not blink
    _delay_us(53);
    send_command_4bit_mode(0b00000001);	// 'Clear Display'
    _delay_ms(3);
    send_command_4bit_mode(0b00000110);	// 'Entry Mode Set' cursor shift to right
    _delay_ms(53);
}

void send_command_4bit_mode(uint8_t command)
{
    GPIO_LOW(LCD_1602_RS);

    if (command & 0b00010000)
        GPIO_HIGH(LCD_1602_PD4);
    else
        GPIO_LOW(LCD_1602_PD4);

    if (command & 0b00100000)
        GPIO_HIGH(LCD_1602_PD5);
    else
        GPIO_LOW(LCD_1602_PD5);

    if (command & 0b01000000)
        GPIO_HIGH(LCD_1602_PD6);
    else
        GPIO_LOW(LCD_1602_PD6);

    if (command & 0b10000000)
        GPIO_HIGH(LCD_1602_PD7);
    else
        GPIO_LOW(LCD_1602_PD7);

    GPIO_HIGH(LCD_1602_E);
    _delay_us(37);
    GPIO_LOW(LCD_1602_E);
    _delay_us(37);

    if (command & 0b00000001)
        GPIO_HIGH(LCD_1602_PD4);
    else
        GPIO_LOW(LCD_1602_PD4);

    if (command & 0b00000010)
        GPIO_HIGH(LCD_1602_PD5);
    else
        GPIO_LOW(LCD_1602_PD5);

    if (command & 0b00000100)
        GPIO_HIGH(LCD_1602_PD6);
    else
        GPIO_LOW(LCD_1602_PD6);

    if (command & 0b00001000)
        GPIO_HIGH(LCD_1602_PD7);
    else
        GPIO_LOW(LCD_1602_PD7);

    GPIO_HIGH(LCD_1602_E);
    _delay_us(37);
    GPIO_LOW(LCD_1602_E);
    _delay_us(37);
}

void send_data_4bit_mode(uint8_t data)
{
    GPIO_HIGH(LCD_1602_RS);

    if (data & 0b00010000)
        GPIO_HIGH(LCD_1602_PD4);
    else
        GPIO_LOW(LCD_1602_PD4);

    if (data & 0b00100000)
        GPIO_HIGH(LCD_1602_PD5);
    else
        GPIO_LOW(LCD_1602_PD5);

    if (data & 0b01000000)
        GPIO_HIGH(LCD_1602_PD6);
    else
        GPIO_LOW(LCD_1602_PD6);

    if (data & 0b10000000)
        GPIO_HIGH(LCD_1602_PD7);
    else
        GPIO_LOW(LCD_1602_PD7);

    GPIO_HIGH(LCD_1602_E);
    _delay_us(37);
    GPIO_LOW(LCD_1602_E);
    _delay_us(37);

    if (data & 0b00000001)
        GPIO_HIGH(LCD_1602_PD4);
    else
        GPIO_LOW(LCD_1602_PD4);

    if (data & 0b00000010)
        GPIO_HIGH(LCD_1602_PD5);
    else
        GPIO_LOW(LCD_1602_PD5);

    if (data & 0b00000100)
        GPIO_HIGH(LCD_1602_PD6);
    else
        GPIO_LOW(LCD_1602_PD6);

    if (data & 0b00001000)
        GPIO_HIGH(LCD_1602_PD7);
    else
        GPIO_LOW(LCD_1602_PD7);

    GPIO_HIGH(LCD_1602_E);
    _delay_us(37);
    GPIO_LOW(LCD_1602_E);
    _delay_us(37);
}
