#ifndef _BUTTON_H_
#define _BUTTON_H_

/**
 * @author Maksym Palii
 * @brief Button control function prototypes
 * @version 1.0 
 */

#include <stdbool.h>
#include "button.h"

extern bool button_was_pressed;

void button_init(void);
bool button_pressed(void);
bool button_released(void);

#endif /* _BUTTON_H_ */