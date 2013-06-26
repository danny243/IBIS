/*
 * switchpanel.c
 *
 * Created: 22.06.2013 18:02:53
 *  Author: DSchuhmann
 */ 

#include <avr/io.h>
#include "switchpanel.h"
#include <util/delay.h>

void col_init(void)
{
    SWITCH_COL_DDR   = 0xF8;
    SWITCH_COL_PORT  = 0x07;
    
    SWITCH_ROW_DDR   = 0xFF;
    SWITCH_ROW_PORT  = 0x00;
    
    _delay_ms(1);
}

void row_init(void)
{
    SWITCH_COL_DDR   = 0xFF;
    SWITCH_COL_PORT  = 0xF8;
    
    SWITCH_ROW_DDR   = 0x00;
    SWITCH_ROW_PORT  = 0xFF;
    
    _delay_ms(1);
}

unsigned char read_key(void)
{
    unsigned char value;
    
    col_init();
    value = 0;
    
    // Spalten übrprüfen
    if      (!(SWITCH_COL_PIN & 0x04))
        {value = 2;}
    else if (!(SWITCH_COL_PIN & 0x02))
        {value = 0;}
    else if (!(SWITCH_COL_PIN & 0x01))
        {value = 1;}
    
    row_init();
    
    // Zeilen überprüfen
    if      (!(SWITCH_ROW_PIN & 0x80))
        {value += 0x07;}
    else if (!(SWITCH_ROW_PIN & 0x40))
        {value += 0x0A;}
    else if (!(SWITCH_ROW_PIN & 0x20))
        {value += 0x04;}
    else if (!(SWITCH_ROW_PIN & 0x10))
        {value += 0x01;}
       
       
    else if (!(SWITCH_ROW_PIN & 0x08))
        {value += 0x0D;}
    else if (!(SWITCH_ROW_PIN & 0x04))
        {value += 0x10;}
    else if (!(SWITCH_ROW_PIN & 0x02))
        {value += 0x13;}
    else if (!(SWITCH_ROW_PIN & 0x01))
        {value += 0x16;}
    
    // Entprellen
    _delay_ms(50);
    return value;
}