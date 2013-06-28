/************************************************************************/
/*                                                                      */
/*                      IBIS Bordcomputer-Simulation                    */
/*                                                                      */
/************************************************************************/
/*                                                                      */
/* Copyright 2013 Daniel Schuhmann                                      */
/*                                                                      */
/* Licensed under the Apache License, Version 2.0 (the "License");      */
/* you may not use this file except in compliance with the License.     */
/* You may obtain a copy of the License at                              */
/*                                                                      */
/* http://www.apache.org/licenses/LICENSE-2.0                           */
/*                                                                      */
/* Unless required by applicable law or agreed to in writing, software  */
/* distributed under the License is distributed on an "AS IS" BASIS,    */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      */
/* implied.                                                             */
/* See the License for the specific language governing permissions and  */
/* limitations under the License.                                       */
/*                                                                      */
/************************************************************************/ 

#include <avr/io.h>
#include "switchpanel.h"
#include <util/delay.h>

void col_init(void)
{
    SWITCH_COL_DDR   = 0xF8;
    SWITCH_COL_PORT  = 0x07;
    
    SWITCH_ROW_DDR   = 0xFF;
    SWITCH_ROW_PORT  = 0x00;
    
    _delay_us(10);
}

void row_init(void)
{
    SWITCH_COL_DDR   = 0xFF;
    SWITCH_COL_PORT  = 0xF8;
    
    SWITCH_ROW_DDR   = 0x00;
    SWITCH_ROW_PORT  = 0xFF;
    
    _delay_us(10);
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
    _delay_ms(25);
    return value;
}