#include "eeprom_24c256.h"

#define SCL P2_2
#define SDA P2_3
#define RED_LED P2_6

unsigned int clr_addr = 0x0000;

void eeprom_delay(){
    char i = 4;
    while(i!=0){i--;}

}
void i2c_init(){
    RED_LED = 0;

    SDA = 1;
    eeprom_delay();
    SCL = 1;
}
void i2c_start(){
    SDA = 0;
    eeprom_delay();
    SCL = 0;
    eeprom_delay();

}

bool getAck(){
        bool ack_bit;
        SDA = 1;
        SCL = 1;
        eeprom_delay();
        ack_bit = SDA;
        SCL = 0;
        eeprom_delay();
        return ack_bit;

}

void eeprom_write_page(unsigned char slave_address, unsigned int location_address){
    char i = 0;
    for(i = 0; i < 8; i++){
        SDA = (slave_address >> (7-i)) & 1;
        eeprom_delay();
        SCL = 1;
        eeprom_delay();
        SCL = 0;
        eeprom_delay();
    }
    
    if(getAck() == 1){
        RED_LED = 1;
        i2c_stop();
        return;
    }
    
    i = 0;
    for(i = 0; i < 8; i++){
        SDA = (location_address >> (15-i)) & 1;
        eeprom_delay();
        SCL = 1;
        eeprom_delay();
        SCL = 0;
        eeprom_delay();
    }

    if(getAck() == 1){
        RED_LED = 1;
        i2c_stop();
        return;
    }

    i = 0;
    for(i = 0; i < 8; i++){
        SDA = (location_address >> (7-i)) & 1;
        eeprom_delay();
        SCL = 1;
        eeprom_delay();
        SCL = 0;
        eeprom_delay();
    }

    if(getAck() == 1){
        RED_LED = 1;
        i2c_stop();
        return;
    }
}

void eeprom_write_byte(unsigned char data){
    char i;
    for(i = 0; i < 8; i++){
        SDA = (data >> (7-i)) & 1;
        eeprom_delay();
        SCL = 1;
        eeprom_delay();
        SCL = 0;
        eeprom_delay();
    }
    
    if(getAck() == 1){
        RED_LED = 1;
        i2c_stop();
        return;
    }
}

void eeprom_delay_clr(){
    int i = 2000;
    while(i!=0){i--;}

}
void clear_eeprom(){
    int j;
    for(j=0; j<10; j++){ //512 for all
        i2c_start();
        eeprom_write_page(0xa0, clr_addr);

        char i;
        for(i=0; i<64; i++){
            eeprom_write_byte(0x00);
        }
        clr_addr += 64;
        i2c_stop();
        eeprom_delay_clr();
    }
}

void i2c_stop(){
    SCL = 0;
    eeprom_delay();
	SDA = 0;
    eeprom_delay();
	SCL = 1;
    eeprom_delay();
	SDA = 1;
    eeprom_delay();

}
