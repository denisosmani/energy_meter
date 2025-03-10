/*
 *  This delay is needed for MCU and
 *  ADC to be frequency-wise compatible
 */
void adc_delay(void);

/*
 *  SPI communication between ADC and MCU
 *  @param[out] dout
 * 
 *  returns digital output generated from ADC
 */
unsigned int adc_spi(__bit channel);
