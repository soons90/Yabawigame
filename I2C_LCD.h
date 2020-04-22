#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#define I2C_LCD_SLA_W (0x27<<1)

void lcd_send_command(char command);
void lcd_send_data(char data);
void I2C_LCD_init(void);
void lcd_send_string(char *string);
void move_cursor(char row, char column);

#endif /* I2C_LCD_H_ */
