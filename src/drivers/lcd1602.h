#ifndef _LCD1602_H_
#define _LCD1602_H_

/**
 * @author Maksym Palii
 * @brief LCD1602 function prototypes
 * @version 1.0
 * @date 19-July-2023
 */

void lcd1602_init(void);
void lcd1602_move_cursor_row_1(void);
void lcd1602_move_cursor_row_2(void);
void lcd1602_render_message(char* message);
void lcd1602_clear_display(void);

#endif /* _LCD1602_H_ */