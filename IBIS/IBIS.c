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

#ifndef __C51__
#define code
#define idata
#endif

#define F_CPU 4000000UL

#define FIRSTYEAR  2000      // start year
#define FIRSTDAY  6          // 0 = Sunday

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd-routines.h"
#include "switchpanel.h"
#include "routes.h"

typedef unsigned char  u8;
typedef   signed char  s8;
typedef unsigned short u16;
typedef   signed short s16;
typedef unsigned long  u32;
typedef   signed long  s32;

struct time {
    u8  second;
    u8  minute;
    u8  hour;
    u8  day;
    u8  month;
    u16 year;
    u8  wday;
};


volatile u32 mytime;
volatile u8 overflow;

u8 code DayOfMonth[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

uint8_t  linie;
uint8_t  kurs;
uint8_t  route;
uint16_t ziel;
uint8_t  hst;
uint8_t  hstindex;


ISR( TIMER2_OVF_vect ) {
    overflow++;
    if (overflow == 61)
    {   
        mytime++;
        overflow = 0;
    }    
}

void summertime( struct time idata *t )
{
    u8 hour, day, wday, month;      // locals for faster access

    hour = t->hour;
    day = t->day;
    wday = t->wday;
    month = t->month;

    if( month < 3 || month > 10 )      // month 1, 2, 11, 12
    return;          // -> Winter

    if( day - wday >= 25 && (wday || hour >= 2) ){ // after last Sunday 2:00
        if( month == 10 )        // October -> Winter
        return;
        }else{          // before last Sunday 2:00
        if( month == 3 )        // March -> Winter
        return;
    }
    hour++;          // add one hour
    if( hour == 24 ){        // next day
        hour = 0;
        wday++;          // next weekday
        if( wday == 7 )
        wday = 0;
        if( day == DayOfMonth[month-1] ){    // next month
            day = 0;
            month++;
        }
        day++;
    }
    t->month = month;
    t->hour = hour;
    t->day = day;
    t->wday = wday;
}

void gettime( u32 sec, struct time idata *t )
{
    u16 day;
    u8 year;
    u16 dayofyear;
    u8 leap400;
    u8 month;

    t->second = sec % 60;
    sec /= 60;
    t->minute = sec % 60;
    sec /= 60;
    t->hour = sec % 24;
    day = sec / 24;

    t->wday = (day + FIRSTDAY) % 7;    // weekday

    year = FIRSTYEAR % 100;      // 0..99
    leap400 = 4 - ((FIRSTYEAR - 1) / 100 & 3);  // 4, 3, 2, 1

    for(;;){
        dayofyear = 365;
        if( (year & 3) == 0 ){
            dayofyear = 366;          // leap year
            if( year == 0 || year == 100 || year == 200 )  // 100 year exception
            if( --leap400 )          // 400 year exception
            dayofyear = 365;
        }
        if( day < dayofyear )
        break;
        day -= dayofyear;
        year++;          // 00..136 / 99..235
    }
    t->year = year + FIRSTYEAR / 100 * 100;  // + century

    if( dayofyear & 1 && day > 58 )    // no leap year and after 28.2.
    day++;          // skip 29.2.

    for( month = 1; day >= DayOfMonth[month-1]; month++ )
    day -= DayOfMonth[month-1];

    t->month = month;        // 1..12
    t->day = day + 1;        // 1..31
}


uint8_t get_haltestellen_index()
{
    uint8_t linie_norm;
    if (linie > 90) linie_norm = linie - 90; else linie_norm = linie;
    if (linie_norm == 1)
    {
        switch (route)
        {
            case  1: if (sizeof(u1_01) < hst) { hst--; return hstindex; } 
                else { return pgm_read_byte (&u1_01 [hst-1]); }
            case  2: if (sizeof(u1_02) < hst) { hst--; return hstindex; } 
                else { return pgm_read_byte (&u1_02 [hst-1]); }
            case  3: if (sizeof(u1_03) < hst) { hst--; return hstindex; } 
                else { return pgm_read_byte (&u1_03 [hst-1]); }
            case  4: if (sizeof(u1_04) < hst) { hst--; return hstindex; } 
                else { return pgm_read_byte (&u1_04 [hst-1]); }
            case  7: if (sizeof(u1_07) < hst) { hst--; return hstindex; } 
                else { return pgm_read_byte (&u1_07 [hst-1]); }
            case  8: if (sizeof(u1_08) < hst) { hst--; return hstindex; } 
                else { return pgm_read_byte (&u1_08 [hst-1]); }
            case 11: if (sizeof(u1_11) < hst) { hst--; return hstindex; } 
                else { return pgm_read_byte (&u1_11 [hst-1]); }
            case 12: if (sizeof(u1_12) < hst) { hst--; return hstindex; } 
                else { return pgm_read_byte (&u1_12 [hst-1]); }
        }
    }

    if (linie_norm == 2)
    {
        switch (route)
        {
            case  1: if (sizeof(u2_01) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_01 [hst-1]); }
            case  2: if (sizeof(u2_02) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_02 [hst-1]); }
            case  3: if (sizeof(u2_03) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_03 [hst-1]); }
            case  5: if (sizeof(u2_05) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_05 [hst-1]); }
            case  6: if (sizeof(u2_06) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_06 [hst-1]); }
            case  7: if (sizeof(u2_07) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_07 [hst-1]); }
            case  8: if (sizeof(u2_08) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_08 [hst-1]); }
            case  9: if (sizeof(u2_09) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_09 [hst-1]); }
            case 10: if (sizeof(u2_10) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_10 [hst-1]); }
            case 11: if (sizeof(u2_11) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_11 [hst-1]); }
            case 12: if (sizeof(u2_12) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_12 [hst-1]); }
            case 17: if (sizeof(u2_17) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_17 [hst-1]); }
            case 18: if (sizeof(u2_18) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u2_18 [hst-1]); }
        }
    }
    
    if (linie_norm == 3)
    {
        switch (route)
        {
            case  1: if (sizeof(u3_01) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_01 [hst-1]); }
            case  2: if (sizeof(u3_02) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_02 [hst-1]); }
            case  3: if (sizeof(u3_03) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_03 [hst-1]); }
            case  4: if (sizeof(u3_04) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_04 [hst-1]); }
            case  5: if (sizeof(u3_05) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_05 [hst-1]); }
            case  6: if (sizeof(u3_06) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_06 [hst-1]); }
            case  7: if (sizeof(u3_07) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_07 [hst-1]); }
            case  8: if (sizeof(u3_08) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_08 [hst-1]); }
            case  9: if (sizeof(u3_09) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_09 [hst-1]); }
            case 10: if (sizeof(u3_10) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_10 [hst-1]); }
            case 11: if (sizeof(u3_11) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_11 [hst-1]); }
            case 12: if (sizeof(u3_12) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_12 [hst-1]); }
            case 13: if (sizeof(u3_13) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_13 [hst-1]); }
            case 17: if (sizeof(u3_17) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_17 [hst-1]); }
            case 18: if (sizeof(u3_18) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u3_18 [hst-1]); }
        }
    }    

    if (linie_norm == 4)
    {
        switch (route)
        {
            case  1: if (sizeof(u4_01) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u4_01 [hst-1]); }
            case  2: if (sizeof(u4_02) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u4_02 [hst-1]); }
            case  3: if (sizeof(u4_03) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u4_03 [hst-1]); }
            case  4: if (sizeof(u4_04) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u4_04 [hst-1]); }
            case  5: if (sizeof(u4_05) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u4_05 [hst-1]); }
            case  6: if (sizeof(u4_06) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u4_06 [hst-1]); }
            case  7: if (sizeof(u4_07) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u4_07 [hst-1]); }
            case  8: if (sizeof(u4_08) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u4_08 [hst-1]); }
            case 13: if (sizeof(u4_13) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u4_13 [hst-1]); }
            case 14: if (sizeof(u4_14) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u4_14 [hst-1]); }
        }
    }

    if (linie_norm == 5)
    {
        switch (route)
        {
            case  1: if (sizeof(u5_01) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_01 [hst-1]); }
            case  2: if (sizeof(u5_02) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_02 [hst-1]); }
            case  3: if (sizeof(u5_03) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_03 [hst-1]); }
            case  4: if (sizeof(u5_04) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_04 [hst-1]); }
            case  5: if (sizeof(u5_05) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_05 [hst-1]); }
            case  6: if (sizeof(u5_06) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_06 [hst-1]); }
            case  7: if (sizeof(u5_07) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_07 [hst-1]); }
            case  8: if (sizeof(u5_08) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_08 [hst-1]); }
            case  9: if (sizeof(u5_09) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_09 [hst-1]); }
            case 10: if (sizeof(u5_10) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_10 [hst-1]); }
            case 11: if (sizeof(u5_11) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_11 [hst-1]); }
            case 12: if (sizeof(u5_12) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_12 [hst-1]); }
            case 13: if (sizeof(u5_13) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_13 [hst-1]); }
            case 14: if (sizeof(u5_14) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_14 [hst-1]); }
            case 15: if (sizeof(u5_15) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_15 [hst-1]); }
            case 16: if (sizeof(u5_16) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u5_16 [hst-1]); }
        }
    }
    
    if (linie_norm == 6)
    {
        switch (route)
        {
            case  3: if (sizeof(u6_03) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_03 [hst-1]); }
            case  4: if (sizeof(u6_04) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_04 [hst-1]); }
            case  5: if (sizeof(u6_05) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_05 [hst-1]); }
            case  6: if (sizeof(u6_06) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_06 [hst-1]); }
            case  7: if (sizeof(u6_07) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_07 [hst-1]); }
            case  8: if (sizeof(u6_08) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_08 [hst-1]); }
            case  9: if (sizeof(u6_09) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_09 [hst-1]); }
            case 10: if (sizeof(u6_10) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_10 [hst-1]); }
            case 11: if (sizeof(u6_11) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_11 [hst-1]); }
            case 12: if (sizeof(u6_12) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_12 [hst-1]); }
            case 13: if (sizeof(u6_13) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_13 [hst-1]); }
            case 14: if (sizeof(u6_14) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_14 [hst-1]); }
            case 15: if (sizeof(u6_15) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_15 [hst-1]); }
            case 16: if (sizeof(u6_16) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_16 [hst-1]); }
            case 17: if (sizeof(u6_17) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_17 [hst-1]); }
            case 18: if (sizeof(u6_18) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_18 [hst-1]); }
            case 19: if (sizeof(u6_19) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_19 [hst-1]); }
            case 20: if (sizeof(u6_20) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_20 [hst-1]); }
            case 21: if (sizeof(u6_21) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u6_21 [hst-1]); }
        }
    }
    
    if (linie_norm == 7)
    {
        switch (route)
        {
            case  1: if (sizeof(u7_01) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u7_01 [hst-1]); }
            case  2: if (sizeof(u7_02) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u7_02 [hst-1]); }
            case  3: if (sizeof(u7_03) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u7_03 [hst-1]); }
            case  4: if (sizeof(u7_04) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u7_04 [hst-1]); }
            case  5: if (sizeof(u7_05) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u7_05 [hst-1]); }
            case  6: if (sizeof(u7_06) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u7_06 [hst-1]); }
            case  7: if (sizeof(u7_07) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u7_07 [hst-1]); }
            case  8: if (sizeof(u7_08) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u7_08 [hst-1]); }
            case  9: if (sizeof(u7_09) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u7_09 [hst-1]); }
            case 10: if (sizeof(u7_10) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u7_10 [hst-1]); }
            case 11: if (sizeof(u7_11) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u7_11 [hst-1]); }
            case 12: if (sizeof(u7_12) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u7_12 [hst-1]); }
        }
    }
    
    if (linie_norm == 8)
    {
        switch (route)
        {
            case  1: if (sizeof(u8_01) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u8_01 [hst-1]); }
            case  2: if (sizeof(u8_02) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u8_02 [hst-1]); }
            case  3: if (sizeof(u8_03) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u8_03 [hst-1]); }
            case  4: if (sizeof(u8_04) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u8_04 [hst-1]); }
            case  5: if (sizeof(u8_05) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u8_05 [hst-1]); }
            case  6: if (sizeof(u8_06) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u8_06 [hst-1]); }
            case  7: if (sizeof(u8_07) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u8_07 [hst-1]); }
            case  8: if (sizeof(u8_08) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u8_08 [hst-1]); }
            case  9: if (sizeof(u8_09) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u8_09 [hst-1]); }
            case 10: if (sizeof(u8_10) < hst) { hst--; return hstindex; }
                else { return pgm_read_byte (&u8_10 [hst-1]); }
        }
    }        
    
    return 0;
}


void display_message(uint8_t msg)
{
    int i;
    for(i=0; i<3; i++)
    {
        lcd_setcursor(0,1);
        switch (msg)
        {
            case 1:  lcd_string("FALSCHE LINIE   "); break; 
            case 2:  lcd_string("FALSCHE ROUTE   "); break; 
            case 3:  lcd_string("FALSCHES ZIEL   "); break; 
            case 7:  lcd_string("MELDUNG SENDEN  "); break; 
            default: lcd_string("UNBEK. FEHLER   ");
        }
        _delay_ms(500);
        lcd_setcursor(0,1);
        lcd_string("                ");
        _delay_ms(500);
    }

}

void display_time()
{
    lcd_setcursor(0, 1);
    struct time idata current_time;
    gettime(mytime, &current_time);
                        
    char buffer[5];
    // LCD-Ausgabe
    // Tag
    utoa(current_time.day, buffer, 10);
    if (current_time.day < 10) lcd_string("0");
    lcd_string(buffer);
    lcd_string(".");
    // Monat
    utoa(current_time.month, buffer, 10);
    if (current_time.month < 10) lcd_string("0");
    lcd_string(buffer);
    lcd_string(".");
    // Jahr
    utoa(current_time.year % 100, buffer, 10);
    if ((current_time.year % 100) < 10) lcd_string("0");
    lcd_string(buffer);
    lcd_string("   ");
    // Stunde
    utoa(current_time.hour, buffer, 10);
    if (current_time.hour < 10) lcd_string("0");
    lcd_string(buffer);
    lcd_string(":");
    // Minute
    utoa(current_time.minute, buffer, 10);
    if (current_time.minute < 10) lcd_string("0");
    lcd_string(buffer);
}


void grundbild()
{
    char hstbuffer[17];
    char buffer[6];
    int liniekurs;

    lcd_clear();
    if (hst == 0)
    {
        strcpy_P(hstbuffer, haltestellen[ziel]);
    } else {
        hstindex = get_haltestellen_index();
        strcpy_P(hstbuffer, haltestellen[hstindex]);
    }
    
    lcd_string(hstbuffer);

    // Ziel angeben
    lcd_setcursor(4, 2);
    
    if (ziel < 10)
        lcd_string("00");
    else if (ziel < 100)
        lcd_string("0");

    utoa(ziel, buffer, 10);
    lcd_string(buffer);
    
    // Abweichung
    lcd_setcursor(14, 2);
    
    lcd_string("+0");
    
    // Route setzen
    lcd_setcursor(0, 2);
    
    if ((route % 2) == 0) lcd_string("R"); else lcd_string("H");
    if (hst < 10)
        lcd_string("00");
    else if (hst < 100)
        lcd_string("0");
    utoa(hst, buffer, 10);
    lcd_string(buffer);
    
    // Linie und Kurs angeben
    lcd_setcursor(8, 2);
    liniekurs = (linie * 100) + kurs;
    
    if (liniekurs < 10)
        lcd_string("0000");
    else if (liniekurs < 100)
        lcd_string("000");
    else if (liniekurs < 1000)
        lcd_string("00");
    else if (liniekurs < 10000)
        lcd_string("0");

    utoa(liniekurs, buffer, 10);
    lcd_string(buffer);
}


int main(void)
{
    TCCR2  = (1<<CS22) | (1<<CS21); // Vorteiler 256 -> ~65ms Überlaufperiode
    TIMSK |= (1<<TOIE2);            // Timer Overflow Interrupt freischalten
    sei();
    
    unsigned char key, key1, key2, key3, key4;
    unsigned int input;
    unsigned char mode;
    unsigned char action;
    
    // Initialisieren
    key = 0; key1 = 0; key2 = 0; key3 = 0; key4 = 0;
    mode = 0;
    action = 0;
    input  = 0;
    linie = 0;
    kurs = 0;
    hst = 0;
    route = 0;
    ziel = 0;
    hstindex = 0;
    mytime = 410047740; 
    
    // LCD auf Grundfunktion setzen
    lcd_init();
    grundbild();
    
    col_init();
    
    while(1)
    {
        if (!(SWITCH_COL_PIN == 0x07))
        {
            
            // Entprellen der Schalter
            // Jeder Schalterdruck muss viermal hintereinander mit dem gleichen Wert erkannt werden
            // Ein neuer Schalterdruck wird erst erkannt, wenn viermal hintereinander der Wert
            // Null erkannt wurde. 
            key4 = key3; key3 = key2; key2 = key1; key1 = read_key();
            if ((key4 == key3) & (key1 == key2) & (key3 == key1)) {key = key1;}
            if (key == 0) {action = 1; continue;}
            if (action == 0) continue;
            action = 0;
            
            lcd_setcursor(0, 1);
            
            switch(mode)
            {
                case 0:
                    // Mode 0: Grundbild
                    
                    if (key == 1)
                    {
                        lcd_string("LINIE/KURS:      ");
                        mode = 1;
                    }
                    if (key == 2)
                    {
                        lcd_string("ROUTE        :  ");
                        mode = 2;
                    }
                    if (key == 3)
                    {
                        lcd_string("ZIEL        :   ");
                        mode = 3;
                    }
                    if (key == 7)
                    {
                        lcd_string("MELDUNG      :  ");
                        mode = 7;
                    }
                    if (key == 8)
                    {
                        // Mode 8/ohne Mode: Uhrzeit/Datum anzeigen
                        display_time();
                    }
                    if (key == 19)
                    {
                        // Mode 19:
                        mode = 19;
                        lcd_setcursor(0, 2);
                        lcd_string("UHRZEIT STELLEN ");
                        display_time();
                    }
                    if (key == 10)
                    {
                        grundbild();
                    }
                    if (key == 14)
                    {
                        // Hst vor, mit Ton
                        if ((linie == 0) | (route == 0)) break;
                        hst++;
                        grundbild();
                        
                    }
                    if (key == 17)
                    {
                        // Hst zurück, mit Ton
                        if ((linie == 0) | (route == 0)) break;
                        if (hst > 1)
                        {
                            hst--;
                            grundbild();
                        }                        
                    }
                    if (key == 15)
                    {
                        // Hst vor, ohne Ton
                        if ((linie == 0) | (route == 0)) break;
                        hst++;
                        grundbild();
                    }
                    if (key == 18)
                    {
                        // Hst zurück, ohne Ton
                        if ((linie == 0) | (route == 0)) break;
                        if (hst > 1)
                        {
                            hst--;
                            grundbild();
                        }
                    }
                    
                break;
                
                case 1:
                    {
                        // LINIE/KURS:
                        // Übernahme (Enter) oder Abbruch (Löschen) der Daten
                        if (key == 12)
                        {
                            uint8_t i;
                            
                            i = input / 100;
                            if (((input % 100) == 0) & ((input/100) != 0))
                            {
                                display_message(1); 
                                grundbild();
                                input = 0;
                                mode = 0;
                                continue;                            
                            }
                            switch (i)
                            {
                                case  0: linie = 0; kurs = 0; ziel = 0; hst = 0;  break; 
                                case  1:  
                                case  2:  
                                case  3:  
                                case  4:  
                                case  5:  
                                case  6:  
                                case  7:  
                                case  8:  
                                case 91: 
                                case 92: 
                                case 93: 
                                case 94: 
                                case 95: 
                                case 96: 
                                case 97: 
                                case 98: linie = i; kurs = input % 100; ziel = 0; break;
                                case 99: linie = 0; kurs = input % 100; ziel = 0; break;
                                default: display_message(1); 
                            }
                            
                            grundbild();
                            input = 0;
                            mode = 0;
                            continue;
                        }
                        
                        if (key == 10)
                        {
                            grundbild();
                            input = 0;
                            mode = 0;
                            continue;
                        }
                        // Unerwünschte Tasten abweisen
                        if (key > 12) {continue;}
                        
                        // Eingabe von Linie und Kurs
                        if (key == 11) {key = 0;}
                        if (input > 9999) {continue;}
                        input = (input * 10) + key;
                        lcd_setcursor(11,1);
                        if (input < 10) 
                            lcd_string("    ");
                        else if (input < 100) 
                            lcd_string("   ");
                        else if (input < 1000)
                            lcd_string("  ");
                        else if (input < 10000)
                            lcd_string(" ");

                        char buffer[6];
                        utoa(input, buffer, 10);
                        lcd_string(buffer);
                        
                    }
                break;

                case 2:
                    {
                        // ROUTE    :
                        // Übernahme (Enter) oder Abbruch (Löschen) der Daten
                        if (key == 12)
                        {
                            uint8_t found;
                            uint8_t i;
                            i = input;
                            found = 1;
                                
                            if (linie == 1) switch (i)
                            {
                                case  1: ziel = 61; break; 
                                case  2: ziel = 50; break; 
                                case  3: ziel = 11; break; 
                                case  4: ziel = 50; break; 
                                case  7: ziel = 82; break; 
                                case  8: ziel = 50; break; 
                                case 11: ziel = 61; break; 
                                case 12: ziel = 40; break; 
                                default: found = 0;
                            }

                            if (linie == 2) switch (i)
                            {
                                case  1: ziel = 83; break; 
                                case  2: ziel = 62; break; 
                                case  3: ziel = 77; break; 
                                case  5: ziel = 77; break; 
                                case  6: ziel = 62; break; 
                                case  7: ziel = 83; break; 
                                case  8: ziel = 68; break; 
                                case  9: ziel = 83; break; 
                                case 10: ziel = 65; break; 
                                case 11: ziel = 83; break; 
                                case 12: ziel = 55; break; 
                                case 17: ziel = 57; break; 
                                case 18: ziel = 68; break; 
                                default: found = 0;
                            }

                            if (linie == 3) switch (i)
                            {
                                case  1: ziel = 27; break; 
                                case  2: ziel = 38; break; 
                                case  3: ziel = 16; break; 
                                case  4: ziel = 38; break; 
                                case  5: ziel = 27; break; 
                                case  6: ziel =  8; break; 
                                case  7: ziel = 11; break; 
                                case  8: ziel = 38; break; 
                                case  9: ziel =  7; break; 
                                case 10: ziel = 38; break; 
                                case 11: ziel = 33; break; 
                                case 12: ziel = 38; break; 
                                case 13: ziel = 27; break; 
                                case 17: ziel = 27; break; 
                                case 18: ziel = 42; break; 
                                default: found = 0;
                            }

                            if (linie == 4) switch (i)
                            {
                                case  1: ziel = 96; break; 
                                case  2: ziel = 86; break; 
                                case  3: ziel = 96; break; 
                                case  4: ziel = 89; break; 
                                case  5: ziel = 96; break; 
                                case  6: ziel = 91; break; 
                                case  7: ziel = 13; break; 
                                case  8: ziel = 89; break; 
                                case 13: ziel = 96; break; 
                                case 14: ziel = 92; break; 
                                default: found = 0;
                            }
                            
                            if (linie == 5) switch (i)
                            {
                                case  1: ziel =102; break; 
                                case  2: ziel = 84; break; 
                                case  3: ziel = 77; break; 
                                case  4: ziel = 86; break; 
                                case  5: ziel = 97; break; 
                                case  6: ziel = 89; break; 
                                case  7: ziel = 77; break; 
                                case  8: ziel = 84; break; 
                                case  9: ziel = 13; break; 
                                case 10: ziel = 84; break; 
                                case 11: ziel = 13; break; 
                                case 12: ziel = 86; break; 
                                case 13: ziel =100; break; 
                                case 14: ziel = 84; break; 
                                case 15: ziel =100; break; 
                                case 16: ziel = 86; break; 
                                default: found = 0;
                            }
                                                        
                            if (linie == 6) switch (i)
                            {
                                case  3: ziel =  1; break; 
                                case  4: ziel = 23; break; 
                                case  5: ziel = 11; break; 
                                case  6: ziel = 16; break; 
                                case  7: ziel =  7; break; 
                                case  8: ziel = 16; break; 
                                case  9: ziel =  7; break; 
                                case 10: ziel = 23; break; 
                                case 11: ziel =  1; break; 
                                case 12: ziel = 26; break; 
                                case 13: ziel = 11; break; 
                                case 14: ziel = 23; break; 
                                case 15: ziel = 7;  break; 
                                case 16: ziel = 22; break; 
                                case 17: ziel = 1;  break; 
                                case 18: ziel = 22; break; 
                                case 19: ziel = 1;  break; 
                                case 20: ziel = 16; break; 
                                case 21: ziel = 16; break; 
                                default: found = 0;
                            }                                                                    

                            if (linie == 7) switch (i)
                            {
                                case  1: ziel =100; break; 
                                case  2: ziel = 50; break; 
                                case  3: ziel = 11; break; 
                                case  4: ziel = 50; break; 
                                case  5: ziel =100; break; 
                                case  6: ziel = 52; break; 
                                case  7: ziel = 11; break; 
                                case  8: ziel = 52; break; 
                                case  9: ziel =102; break; 
                                case 10: ziel = 50; break; 
                                case 11: ziel = 61; break; 
                                case 12: ziel = 50; break; 
                                default: found = 0;
                            }
                            
                            if (linie == 8) switch (i)
                            {
                                case  1: ziel = 11; break; 
                                case  2: ziel = 38; break; 
                                case  3: ziel = 57; break; 
                                case  4: ziel = 38; break; 
                                case  5: ziel = 83; break; 
                                case  6: ziel = 38; break; 
                                case  7: ziel = 61; break; 
                                case  8: ziel = 38; break; 
                                case  9: ziel =102; break; 
                                case 10: ziel = 38; break; 
                                default: found = 0;
                            }
                            
                            if ((found == 0) | (linie == 0))
                            {
                                display_message(2);
                            } else {
                                route = i;
                                hst = 0;
                            }
                            
                            grundbild();
                            input = 0;
                            mode = 0;
                            continue;
                        }
                    
                        if (key == 10)
                        {
                            grundbild();
                            input = 0;
                            mode = 0;
                            continue;
                        }
                        // Unerwünschte Tasten abweisen
                        if (key > 12) continue;
                    
                        // Eingabe der Route
                        if (key == 11) key = 0;
                        if (input > 99) continue;
                        input = (input * 10) + key;
                        lcd_setcursor(14,1);
                        if (input < 10) lcd_string(" ");

                        char buffer[3];
                        utoa(input, buffer, 10);
                        lcd_string(buffer);
                    
                    }
                break;
                
                case 3:
                    {
                        // ZIEL      :
                        // Übernahme (Enter) oder Abbruch (Löschen) der Daten
                        if (key == 12)
                        {
                            uint8_t i;
                            uint8_t found;
                            i = input;
                            found = 1;
                            
                            switch (i)
                            {
                                case  0: ziel =  0; break; 
                                case  1: ziel = 19; break; 
                                case  2: ziel = 96; break; 
                                case  3: ziel = 34; break; 
                                case  4: ziel = 62; break; 
                                case  5: ziel = 23; break; 
                                case  6: ziel = 27; break; 
                                case  7: ziel = 33; break; 
                                case  8: ziel =  7; break; 
                                case  9: ziel = 55; break; 
                                case 10: ziel = 24; break; 
                                case 11: ziel =  8; break; 
                                case 12: ziel = 77; break; 
                                case 13: ziel = 68; break; 
                                case 14: ziel = 22; break; 
                                case 15: ziel =  1; break; 
                                case 16: ziel = 57; break; 
                                case 17: ziel = 84; break; 
                                case 18: ziel = 91; break; 
                                case 19: ziel = 61; break; 
                                case 20: ziel = 92; break; 
                                case 21: ziel = 83; break; 
                                case 22: ziel = 42; break; 
                                case 23: ziel = 16; break; 
                                case 24: ziel = 49; break; 
                                case 25: ziel =102; break; 
                                case 26: ziel =100; break; 
                                case 27: ziel = 13; break; 
                                case 28: ziel = 38; break; 
                                case 29: ziel = 52; break; 
                                case 30: ziel = 97; break; 
                                case 31: ziel = 11; break; 
                                case 32: ziel = 89; break; 
                                case 33: ziel = 86; break; 
                                case 34: ziel = 50; break; 
                                case 35: ziel = 65; break; 
                                case 38: ziel = 26; break; 
                                case 39: ziel = 40; break; 

                                case 36: ziel = 43; break; 
                                case 37: ziel = 44; break; 
                                case 140:ziel = 45; break; 
                                case 101:ziel = 46; break; 
                                case 125:ziel = 47; break; 
                                case 115:ziel = 48; break; 
                                default: found = 0;
                            }                            
                            
                            if (found == 0)
                            {
                                display_message(3);
                            } 
                            grundbild();
                            input = 0;
                            mode = 0;
                            continue;
                        }
                    
                        if (key == 10)
                        {
                            grundbild();
                            input = 0;
                            mode = 0;
                            continue;
                        }
                        // Unerwünschte Tasten abweisen
                        if (key > 12) continue;
                    
                        // Eingabe des Ziels
                        if (key == 11) key = 0;
                        if (input > 999) continue;
                        input = (input * 10) + key;
                        lcd_setcursor(13,1);
                        if (input < 10)       
                            lcd_string("  ");
                        else if (input < 100) 
                            lcd_string(" ");

                        char buffer[4];
                        utoa(input, buffer, 10);
                        lcd_string(buffer);
                        
                    }
                break;

                case 7:
                    {
                        // MELDUNG     :
                        // Übernahme (Enter) oder Abbruch (Löschen) der Daten
                        if (key == 12)
                        {
                            display_message(7);
                            
                            grundbild();
                            input = 0;
                            mode = 0;
                            continue;
                        }
                    
                        if (key == 10)
                        {
                            grundbild();
                            input = 0;
                            mode = 0;
                            continue;
                        }
                        // Unerwünschte Tasten abweisen
                        if (key > 12) continue;
                    
                        // Eingabe der Meldung
                        if (key == 11) key = 0;
                        input = (input * 10) + key;
                        if (input > 9) continue;
                        lcd_setcursor(15,1);

                        char buffer[3];
                        utoa(input, buffer, 10);
                        lcd_string(buffer);
                    
                    }
                break;

                case 19:
                {
                    // UHRZEIT STELLEN:
                    // Übernahme (Enter) oder Abbruch (Löschen) der Daten
                    if (key == 12)
                    {
                        grundbild();
                        mode = 0;
                        input = 0;
                        continue;
                    }
                    
                    if (key == 10)
                    {
                        grundbild();
                        input = 0;
                        mode = 0;
                        continue;
                    }
                    switch (key)
                    {
                        case 15: mytime += 60;
                        case 18: mytime -= 60;
                        case 14: mytime += 3600;
                        case 17: mytime -= 3600;
                        case 13: mytime += 86400;
                        case 16: mytime -= 86400;
                        case 21: mytime += 2592000;
                        case 24: mytime -= 2592000;
                        case 20: mytime += 31536000;
                        case 23: mytime -= 31536000; display_time();
                    }
                    
                }
                break;



            }
/*
            {
                // Anzeige des Tastencodes rechts unten auf dem LCD
                // für Debugzwecke
                lcd_setcursor(14,2);
                char buffer[3];
                utoa(key, buffer, 10);
                lcd_string(buffer);
                lcd_string(" ");
            }
*/
        }
        
        
        
    }
}