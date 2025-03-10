#include "adc_mcp3208.h"
#include <8051.h>

#define CLK P1_0
#define DIN P1_1
#define DOUT P1_2
#define CS P1_3

void adc_delay(){
    return;

}

unsigned int adc_spi(__bit channel) {
    unsigned int dout = 0x0000;
    CS = 1; 
    CLK = 0;    //CLK idles low
    DIN = 0;
    CS = 0;
    DIN = 1;
    CLK = 1;    //START = 1
    adc_delay();
    CLK = 0;
    adc_delay();
    CLK = 1;    //SGL = 1
    adc_delay();
    CLK = 0;
    adc_delay();
    DIN = 0;
    CLK = 1;    //D2 = 0
    adc_delay();
    CLK = 0;
    adc_delay();
    CLK = 1;    //D1 = 0
    adc_delay();
    CLK = 0;
    adc_delay();
    DIN = channel;
    CLK = 1;    //D0 = channel (0 for CH0 and 1 for CH1)
    adc_delay();
    CLK = 0;
    adc_delay();
    CLK = 1;    //11th rising edge
    adc_delay();
    CLK = 0;
    //get 12 bits
    DOUT = 1;
    char i;
    for(i=0; i<13; i++){
        CLK = 1;
        adc_delay();
        dout <<= 1;
        dout |= DOUT & 1;
        CLK = 0;
        adc_delay();
    }

    return dout;

}
