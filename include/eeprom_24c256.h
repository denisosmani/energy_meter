#include <8051.h>

#define bool __bit

/*
 *  This delay is needed for MCU and
 *  EEPROM to be frequency-wise compatible
 */
void eeprom_delay();

/*
 *  I2C communication init between EEPROM and MCU
 *  and prepares conditions for the comm
 */
void i2c_init();

/*
 *  I2C communication starts between EEPROM and MCU
 */
void i2c_start();

/*
 *  Gets acknowledge bit from slave to check for errors
 */
bool getAck();

/*
 *  Writes one page on the EEPROM
 *  @param[in] slave_address That is address of the slave
 *  @param[in] location_address The first address to start writing
 */
void eeprom_write_page(unsigned char slave_address, unsigned int location_address);

/*
 *  Writes one byte on the EEPROM
 *  @param[in] data Byte to write
 */
void eeprom_write_byte(unsigned char data);

/*
 *  Clears the EEPROM content
 */
void clear_eeprom();

/*
 *  I2C communication stops between EEPROM and MCU
 */
void i2c_stop();
