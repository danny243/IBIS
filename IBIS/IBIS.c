/************************************************************************/
/*                                                                      */
/*                      IBIS Bordcomputer-Simulation                    */
/*                                                                      */
/*              Author: Daniel Schuhmann                                */
/*                                                                      */
/*                                                                      */
/************************************************************************/
/* Tasteninterface
 * 3 Zeilen * 8 Spalten
 *
 * 0x00         = Keine Taste gedrückt
 * 0x01 .. 0x09 = Tastenfeld 1..9
 * 0x0B         = Tastenfeld 0
 * 0x0A         = Löschen
 * 0x0C         = Eingabe/Quittieren
 * 0x0E         = + Hst 
 * 0x11         = - Hst
 * 0x0F         = + Hst (Ansage unterdrückt)
 * 0x12         = - Hst (Ansage unterdrückt)
 *              = Rundspruch Quittieren
 *              = Unfall
 *              = Ohne Ausweis
 *              = Sprechwunsch
 *              = + Zahlgrenze
 *              = - Zahlgrenze
 *              = H/R
 *              = LZA
 */ 

#define F_CPU 4000000UL

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd-routines.h"
#include "switchpanel.h"
#include "routes.h"


uint8_t  linie;
uint8_t  kurs;
uint8_t  route;
uint16_t ziel;
uint8_t  hst;
uint8_t  hstindex;


uint8_t get_haltestellen_index()
{
    if (linie == 1)
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

    if (linie == 2)
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
    
    if (linie == 3)
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

    if (linie == 6)
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
            case 1: { lcd_string("FALSCHE LINIE   "); break; }
            case 2: { lcd_string("FALSCHE ROUTE   "); break; }
            case 3: { lcd_string("FALSCHES ZIEL   "); break; }
            case 7: { lcd_string("MELDUNG SENDEN  "); break; }
            default: lcd_string("UNBEK. FEHLER   ");
        }
        _delay_ms(500);
        lcd_setcursor(0,1);
        lcd_string("                ");
        _delay_ms(500);
    }

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
    {lcd_string("00");}
    else if (ziel < 100)
    {lcd_string("0");}

    utoa(ziel, buffer, 10);
    lcd_string(buffer);
    
    // Route setzen
    lcd_setcursor(0, 2);
    
    if ((route % 2) == 0) {lcd_string("R");} else {lcd_string("H");}
    if (hst < 10)
    {lcd_string("00");}
    else if (hst < 100)
    {lcd_string("0");}
    utoa(hst, buffer, 10);
    lcd_string(buffer);
    
    // Linie und Kurs angeben
    lcd_setcursor(8, 2);
    liniekurs = (linie * 100) + kurs;
    
    if (liniekurs < 10)
    {lcd_string("0000");}
    else if (liniekurs < 100)
    {lcd_string("000");}
    else if (liniekurs < 1000)
    {lcd_string("00");}
    else if (liniekurs < 10000)
    {lcd_string("0");}

    utoa(liniekurs, buffer, 10);
    lcd_string(buffer);
}


int main(void)
{
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
            if (action == 0) {continue;}
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
                    if (key == 14)
                    {
                        // Hst vor, mit Ton
                        hst++;
                        grundbild();
                        
                    }
                    if (key == 17)
                    {
                        // Hst zurück, mit Ton
                        if (hst > 1)
                        {
                            hst--;
                            grundbild();
                        }                        
                    }
                    if (key == 15)
                    {
                        // Hst vor, ohne Ton
                        hst++;
                        grundbild();
                    }
                    if (key == 18)
                    {
                        // Hst zurück, ohne Ton
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
                            switch (i)
                            {
                                case 1:  { linie = i; kurs = input % 100; ziel = 0; break; }
                                case 2:  { linie = i; kurs = input % 100; ziel = 0; break; }
                                case 3:  { linie = i; kurs = input % 100; ziel = 0; break; }
                                case 6:  { linie = i; kurs = input % 100; ziel = 0; break; }
                                default: { display_message(1); }
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
                            {lcd_string("    ");}
                        else if (input < 100) 
                            {lcd_string("   ");}
                        else if (input < 1000)
                             {lcd_string("  ");}
                        else if (input < 10000)
                        {lcd_string(" ");}

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
                                case  1: { ziel = 61; break; }
                                case  2: { ziel = 50; break; }
                                case  3: { ziel = 11; break; }
                                case  4: { ziel = 50; break; }
                                case  7: { ziel = 82; break; }
                                case  8: { ziel = 50; break; }
                                case 11: { ziel = 61; break; }
                                case 12: { ziel = 40; break; }
                                default: found = 0;
                            }

                            if (linie == 2) switch (i)
                            {
                                case  1: { ziel = 83; break; }
                                case  2: { ziel = 62; break; }
                                case  3: { ziel = 77; break; }
                                case  5: { ziel = 77; break; }
                                case  6: { ziel = 62; break; }
                                case  7: { ziel = 83; break; }
                                case  8: { ziel = 68; break; }
                                case  9: { ziel = 83; break; }
                                case 10: { ziel = 65; break; }
                                case 11: { ziel = 83; break; }
                                case 12: { ziel = 55; break; }
                                case 17: { ziel = 57; break; }
                                case 18: { ziel = 68; break; }
                                default: found = 0;
                            }

                            if (linie == 3) switch (i)
                            {
                                case  1: { ziel = 27; break; }
                                case  2: { ziel = 38; break; }
                                case  3: { ziel = 16; break; }
                                case  4: { ziel = 38; break; }
                                case  5: { ziel = 27; break; }
                                case  6: { ziel =  8; break; }
                                case  7: { ziel = 11; break; }
                                case  8: { ziel = 38; break; }
                                case  9: { ziel =  7; break; }
                                case 10: { ziel = 38; break; }
                                case 11: { ziel = 33; break; }
                                case 12: { ziel = 38; break; }
                                case 13: { ziel = 27; break; }
                                case 17: { ziel = 27; break; }
                                case 18: { ziel = 42; break; }
                                default: found = 0;
                            }

                            if (linie == 6) switch (i)
                            {
                                case  3: { ziel =  1; break; }
                                case  4: { ziel = 23; break; }
                                case  5: { ziel = 11; break; }
                                case  6: { ziel = 16; break; }
                                case  7: { ziel =  7; break; }
                                case  8: { ziel = 16; break; }
                                case  9: { ziel =  7; break; }
                                case 10: { ziel = 23; break; }
                                case 11: { ziel =  1; break; }
                                case 12: { ziel = 26; break; }
                                case 13: { ziel = 11; break; }
                                case 14: { ziel = 23; break; }
                                case 15: { ziel = 7;  break; }
                                case 16: { ziel = 22; break; }
                                case 17: { ziel = 1;  break; }
                                case 18: { ziel = 22; break; }
                                case 19: { ziel = 1;  break; }
                                case 20: { ziel = 16; break; }
                                case 21: { ziel = 16; break; }
                                default: found = 0;
                            }                                                                    
                            
                            
                            if (found == 0)
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
                        if (key > 12) {continue;}
                    
                        // Eingabe der Route
                        if (key == 11) {key = 0;}
                        if (input > 99) {continue;}
                        input = (input * 10) + key;
                        lcd_setcursor(14,1);
                        if (input < 10) {lcd_string(" ");}

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
                                case  0: { ziel =  0; break; }
                                case  1: { ziel = 19; break; }
                                case  3: { ziel = 34; break; }
                                case 38: { ziel = 26; break; }
                                case  6: { ziel = 27; break; }
                                case 10: { ziel = 24; break; }
                                case  8: { ziel =  7; break; }
                                case 11: { ziel =  8; break; }
                                case 14: { ziel = 22; break; }
                                case 15: { ziel =  1; break; }
                                case 22: { ziel = 42; break; }
                                case 23: { ziel = 16; break; }
                                case 27: { ziel = 13; break; }
                                case 39: { ziel = 40; break; }
                                case 28: { ziel = 38; break; }
                                case 31: { ziel = 11; break; }
                                case  7: { ziel = 33; break; }

                                case 36: { ziel = 43; break; }
                                case 37: { ziel = 44; break; }
                                case 140:{ ziel = 45; break; }
                                case 101:{ ziel = 46; break; }
                                case 125:{ ziel = 47; break; }
                                case 115:{ ziel = 48; break; }
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
                        if (key > 12) {continue;}
                    
                        // Eingabe des Ziels
                        if (key == 11) {key = 0;}
                        if (input > 999) {continue;}
                        input = (input * 10) + key;
                        lcd_setcursor(13,1);
                        if (input < 10)       {lcd_string("  ");}
                        else if (input < 100) {lcd_string(" ");}

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
                        if (key > 12) {continue;}
                    
                        // Eingabe der Meldung
                        if (key == 11) {key = 0;}
                        input = (input * 10) + key;
                        if (input > 9) {continue;}
                        lcd_setcursor(15,1);

                        char buffer[3];
                        utoa(input, buffer, 10);
                        lcd_string(buffer);
                    
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