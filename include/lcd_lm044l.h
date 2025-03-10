#define ROW0 0x80
#define ROW1 0xc0
#define ROW2 0x94
#define ROW3 0xd4

/*
 *  This delay is needed for MCU and
 *  LCD to be frequency-wise compatible
 */
void lcd_delay(void);

/*
 *  Used to write commands on LCD
 *  @param[in] command to send on LCD
 */
void lcd_write_cmd(unsigned char command);

/*
 *  Used to write data on LCD
 *  @param[in] data to be written on LCD
 */
void lcd_write_data(unsigned char data);

/*
 *  Used to write data on LCD
 *  @param[in] word Data to be written on LCD
 *  @param[in] size Number of bytes to write
 *  @param[in] row Row of LCD to print on
 */
void lcd_write_word(unsigned char word[], unsigned char size, unsigned char row);

/*
 * Used to initialize the LCD
 */
void lcd_init(void);

/*
 *  Used to have a delay after
 *  LCD is cleared and because of its 
 *  inactivity for that time
 */
void lcd_delay_clr(void);

/*
 * Used to clear the content of LCD
 */
void lcd_clr(void);