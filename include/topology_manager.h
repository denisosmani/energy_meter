#include <8051.h>
#include "adc_mcp3208.h"
#include "lcd_lm044l.h"
#include "eeprom_24c256.h"

/*
 *  Formats voltage and prints it on LCD
 * 
 */
void format_print_voltage();

/*
 *  Measures voltage using ADC (CH0)
 * 
 */
void measure_voltage();

/*
 *  Formats current and prints it on LCD
 * 
 */
void format_print_current();

/*
 *  Measures voltage using ADC (CH1)
 * 
 */
void measure_current();

/*
 *  Formats power and prints it on LCD
 * 
 */
void format_print_power();

/*
 *  Calculates the power multiplying actual voltage
 *  and current
 * 
 */
void calculate_power();

/*
 *  Formats energy and prints it on LCD
 * 
 */
void format_print_energy();

/*
 *  Acumulates energy every sample, adding the power
 * 
 */
void calculate_energy();

/*
 *  Increments a seconds counter
 * 
 */
void inc_seconds();

/*
 * Prints the seconds on LCD
 * 
 * @param[in] seconds Seconds that have passed
 */
void lcd_print_seconds(unsigned long int seconds);

/*
 *  Stores data on EEPROM
 * 
 */
void store_data_eeprom();