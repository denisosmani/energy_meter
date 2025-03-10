#include "lcd_lm044l.h"
#include <8051.h>

#define RS P2_0
#define EN P2_1
#define BUS P0

void lcd_delay(){
    char i = 40;
    while(i!=0){i--;}

}

void lcd_write_cmd(unsigned char command){
    RS = 0;
    lcd_delay();
    EN = 1;
    BUS = command;
    EN = 0;
    lcd_delay();
    
}

void lcd_write_data(unsigned char data){
    RS = 1;
    lcd_delay();
    EN = 1;
    BUS = data;
    EN = 0;
    lcd_delay();
    
}

void lcd_write_word(unsigned char word[], unsigned char size, unsigned char row){
    lcd_write_cmd(row);
    unsigned char i;
    for(i=0; i<size; i++){
        lcd_write_data(word[i]);
    }
}

void lcd_init(){
    lcd_write_cmd(0x38);
    lcd_write_cmd(0x0c);
    lcd_write_cmd(0x80);
    
    lcd_write_word("Voltage:", 8, ROW0); //0x88
    lcd_write_word("Current:", 8, ROW1);
    lcd_write_word("Power:", 6, ROW2);
    lcd_write_word("Energy:", 7, ROW3);

    lcd_write_word("V", 1, 0x92);
    lcd_write_word("A", 1, 0xd2);
    lcd_write_word("W", 1, 0xa6);
    lcd_write_word("Wh", 2, 0xe6);
}

void lcd_delay_clr(){
    int i = 3000;
    while(i!=0){i--;}

}

void lcd_clr(){
    lcd_write_cmd(0x01);
    lcd_delay_clr();

}
