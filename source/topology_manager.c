#include "topology_manager.h"

#define CHANNEL_0 0
#define CHANNEL_1 1

__code unsigned char lcd_numbers[] = {'0','1','2','3','4','5','6','7','8','9'};

float voltage_volt_f;
float current_amp_f;
float power_wat_f;
float energy_wath_f=0.0;
float printed_energy_f;
__bit is_neg_voltage;
__bit is_neg_current;

unsigned int range_normalize;
unsigned char buffer[7];
unsigned int location_address = 0x0000;

unsigned long int seconds = 0; 

void format_print_voltage(){
    buffer[0]='0';
    buffer[1]='0';
    buffer[2]='0';
    buffer[3]='0';
    buffer[4]='0';
    buffer[5]='0';
    buffer[6]='0';
    buffer[7]='0';

    if(is_neg_voltage){
        buffer[0] = '-';
    }else{
        buffer[0] = '+';
    }
    
    int whole_part = (int)voltage_volt_f;
    int fractional_part = (voltage_volt_f - whole_part)*1000;
    
    if((fractional_part/10) != 99 && (fractional_part)%10 >= 5){
        fractional_part += 10;
    }

    buffer[1] = lcd_numbers[(whole_part/100)%10];
    buffer[2] = lcd_numbers[(whole_part/10)%10];
    buffer[3] = lcd_numbers[(whole_part)%10];
    buffer[4] = '.';
    buffer[5] = lcd_numbers[(fractional_part/100)%10];
    buffer[6] = lcd_numbers[(fractional_part/10)%10];

    lcd_write_word(buffer, 7, 0x88);
}

void measure_voltage(){

    lcd_delay_clr();
    unsigned int voltage_volt = adc_spi(CHANNEL_0);

    if(voltage_volt >= 2048){
        is_neg_voltage = 0;
        voltage_volt_f = (((float)voltage_volt/1000.0) - 2.048)*97.65625;
    }else{
        is_neg_voltage = 1;
        voltage_volt_f = (((((float)voltage_volt)/1000.0) - 2.048)*(-1))*97.65625;
    }

    format_print_voltage();
}

void format_print_current(){
    buffer[0]='0';
    buffer[1]='0';
    buffer[2]='0';
    buffer[3]='0';
    buffer[4]='0';
    buffer[5]='0';
    buffer[6]='0';
    buffer[7]='0';

    if(is_neg_current){
        buffer[0] = '-';
    }else{
        buffer[0] = '+';
    }

    int whole_part = (int)current_amp_f;
    int fractional_part = (current_amp_f - whole_part)*1000;
    
    if( (fractional_part/10) != 99 && (fractional_part)%10 >= 5){
        fractional_part += 10;
    }

    buffer[1] = lcd_numbers[(whole_part/100)%10];
    buffer[2] = lcd_numbers[(whole_part/10)%10];
    buffer[3] = lcd_numbers[(whole_part)%10];
    buffer[4] = '.';
    buffer[5] = lcd_numbers[(fractional_part/100)%10];
    buffer[6] = lcd_numbers[(fractional_part/10)%10];

    lcd_write_word(buffer, 7, 0xc8);

}

void measure_current(){
    lcd_delay_clr();
    unsigned int current_amp = adc_spi(CHANNEL_1);

    if(current_amp >= 2048){
        is_neg_current = 0;
        current_amp_f = (((float)current_amp/1000.0) - 2.048)*100.0;
    }else{
        is_neg_current = 1;
        current_amp_f = (((((float)current_amp)/1000.0) - 2.048)*(-1.0))*100.0;
    }

    format_print_current();

}

void format_print_power(){
    buffer[0]='0';
    buffer[1]='0';
    buffer[2]='0';
    buffer[3]='0';
    buffer[4]='0';
    buffer[5]='0';
    buffer[6]='0';

    int whole_part = (int)power_wat_f;
    int fractional_part = (power_wat_f - whole_part)*100;
    
    buffer[0] = lcd_numbers[(whole_part/1000)%10];
    buffer[1] = lcd_numbers[(whole_part/100)%10];
    buffer[2] = lcd_numbers[(whole_part/10)%10];
    buffer[3] = lcd_numbers[(whole_part)%10];
    buffer[4] = '.';
    buffer[5] = lcd_numbers[(fractional_part/10)%10];
    buffer[6] = lcd_numbers[(fractional_part)%10];
    
    lcd_write_word(buffer, 7, 0x9a);

}

void calculate_power(){
    power_wat_f = voltage_volt_f * current_amp_f;

    format_print_power();
}

void lcd_print_seconds(unsigned long int seconds){
    unsigned char q = seconds/10;
    unsigned char dh = seconds%10;
    
    buffer[0] = lcd_numbers[q];
    buffer[1] = lcd_numbers[dh];

    lcd_write_word(buffer, 2, 0xa3);
}

void format_print_energy(){
    buffer[0]='0';
    buffer[1]='0';
    buffer[2]='0';
    buffer[3]='0';
    buffer[4]='0';
    buffer[5]='0';
    buffer[6]='0';
    
    int whole_part = (int)energy_wath_f;
    int fractional_part = (energy_wath_f - whole_part)*100;
    
    buffer[0] = lcd_numbers[(whole_part/1000)%10];
    buffer[1] = lcd_numbers[(whole_part/100)%10];
    buffer[2] = lcd_numbers[(whole_part/10)%10];
    buffer[3] = lcd_numbers[(whole_part)%10];
    buffer[4] = '.';
    buffer[5] = lcd_numbers[(fractional_part/10)%10];
    buffer[6] = lcd_numbers[(fractional_part)%10];

    lcd_write_word(buffer, 7, 0xdb);

}

void calculate_energy(){
    energy_wath_f = energy_wath_f + (power_wat_f*(1.0/3600.0)); // integrate power
    //lcd_print_seconds(seconds);
    format_print_energy();

}

void store_data_eeprom(){
    i2c_start();
    eeprom_write_page(0xa0, location_address);

    unsigned char* byte_f =  (unsigned char*)&voltage_volt_f;
    eeprom_write_byte(byte_f[0]);
    eeprom_write_byte(byte_f[1]);
    eeprom_write_byte(byte_f[2]);
    eeprom_write_byte(byte_f[3]);
    
    byte_f =  (unsigned char*)&current_amp_f;
    eeprom_write_byte(byte_f[0]);
    eeprom_write_byte(byte_f[1]);
    eeprom_write_byte(byte_f[2]);
    eeprom_write_byte(byte_f[3]);

    byte_f =  (unsigned char*)&power_wat_f;
    eeprom_write_byte(byte_f[0]);
    eeprom_write_byte(byte_f[1]);
    eeprom_write_byte(byte_f[2]);
    eeprom_write_byte(byte_f[3]);

    byte_f =  (unsigned char*)&energy_wath_f;
    eeprom_write_byte(byte_f[0]);
    eeprom_write_byte(byte_f[1]);
    eeprom_write_byte(byte_f[2]);
    eeprom_write_byte(byte_f[3]);
    
    location_address += 16;
    i2c_stop();
}

void inc_seconds(){
    seconds++;
}