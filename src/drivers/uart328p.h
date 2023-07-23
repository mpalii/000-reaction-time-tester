#ifndef _UART328P_H_
#define _UART328P_H_

/**
 * @author Maksym Palii
 * @brief UART function prototypes
 * @version 1.0
 * @date 18-July-2023
 */

#include <avr/io.h>
#include <stdbool.h>
#include <stddef.h>

void uart_init(uint32_t f_cpu, uint32_t baud_rate, bool double_speed_enabled);
char* uart_receive_data(void);
void uart_transmit_data(char* data);

#endif /* _UART328P_H_ */