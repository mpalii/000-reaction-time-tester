#include "launcher.h"
#include "../drivers/gpio.h"
#include "../drivers/button.h"
#include "../drivers/buzzer.h"
#include "../drivers/led.h"
#include "../drivers/lcd1602.h"
#include "../drivers/uart328p.h"
#include "../state_machine/state_machine.h"
#include "../task_manager/scheduler.h"

#include <avr/interrupt.h>

void init_drivers(void);

void launch_app(void)
{
    init_drivers();
    init_state_machine();
    init_scheduler();

    launch_tasks();
}

void init_drivers(void)
{
    gpio_init();
    lcd1602_init();
    led_init();
    buzzer_init();
    button_init();
    uart_init(F_CPU, 9600, false);

    sei();
}