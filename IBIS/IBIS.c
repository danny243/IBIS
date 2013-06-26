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
 * 0x0E         = + Hst 
 * 0x11         = - Hst
 * 0x0F         = + Hst (Ansage unterdrückt)
 * 0x12         = - Hst (Ansage unterdrückt)
 */ 

#define F_CPU 4000000UL

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lcd-routines.h"
#include "switchpanel.h"

const char haltestellen[][17] PROGMEM =
{
    "                ", // 0
    "KL. GROSSHADERN ",
    "GROSSHADERN     ",
    "HADERNER STERN  ",
    "HOLZAPFELKREUTH ",
    "WESTPARK        ",
    "PARTNACHPLATZ   ",
    "HARRAS          ", // 7
    "IMPLERSTRASSE   ", // 8
    "POCCISTRASSE    ",
    "GOETHEPLATZ     ", // 10
    "SENDLINGER TOR  ", // 11
    "MARIENPLATZ     ",
    "ODEONSPLATZ     ",
    "UNIVERSITAET    ",
    "GISELASTRASSE   ",
    "MUENCHNER FREIH.", // 16
    "DIETLINDENSTR.  ",
    "NORDFRIEDHOF    ",
    "ALTE HEIDE      ",
    "STUDENTENSTADT  ", // 20
    "FREIMANN        ",
    "KIEFERNGARTEN   ", // 22
    "FROETTMANING    ", // 23
    "GARCHING-HOCHBR.",
    "GARCHING        ",
    "GARCHING-FORSCH.", // 26
    "FUERSTENRIED W. ", // 27
    "BASLER STRASSE  ",
    "FORSTENRIEDER A.",
    "MACHTLFINGERSTR.",
    "AIDENBACHSTR.   ",
    "OBERSENDLING    ",
    "THALKIRCHEN     ", // 33
    "BRUDERMUEHLSTR. ", // 34
    "BONNER PLATZ    ", // 35
    "SCHEIDPLATZ     ",
    "PETUELRING      ",
    "OLYMPIAZENTRUM  ", // 38
    "OBERWIESENFELD  ",
    "OLYMPIA-EINK. Z.", // 40
    "MOOS. ST-MARTPL.",
    "MOOSACH         ", // 42    
    "SONDERFAHRT     ",
    "EINRUECKFAHRT   ",
    "NICHT EINSTEIGEN",
    "SCHULUNGSFAHRT  ",
    "PARTYZUG        ",
    "PROBEFAHRT      "  // 48
};

const char u3_01 [] PROGMEM =
// OZ - FW
{
    38, 37, 36, 35,
    16, 15, 14, 13, 12, 11, 10, 9, 8,
    34, 33, 32, 31, 30, 29, 28, 27
};

const char u3_02 [] PROGMEM =
// FW - OZ
{
    27, 28, 29, 30, 31, 32, 33, 34,
    8, 9, 10, 11, 12, 13, 14, 15, 16,
    35, 36, 37, 38
};

const char u3_03 [] PROGMEM =
// OZ - MU
{
    38, 37, 36, 35, 16
};

const char u3_04 [] PROGMEM =
// MU - OZ
{
    16, 35, 36, 37, 38
};

const char u3_05 [] PROGMEM =
// IP - FW
{
    8, 34, 33, 32, 31, 30, 29, 28, 27
};

const char u3_06 [] PROGMEM =
// FW - IP
{
    27, 28, 29, 30, 31, 32, 33, 34, 8
};

const char u3_07 [] PROGMEM =
// OZ - SE
{
    38, 37, 36, 35,
    16, 15, 14, 13, 12, 11
};

const char u3_08 [] PROGMEM =
// SE - OZ
{
    11, 12, 13, 14, 15, 16,
    35, 36, 37, 38
};

const char u3_09 [] PROGMEM =
// OZ - HS
{
    38, 37, 36, 35,
    16, 15, 14, 13, 12, 11, 10, 9, 8, 7
};

const char u3_10 [] PROGMEM =
// HS - OZ
{
    7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    35, 36, 37, 38
};

const char u3_11 [] PROGMEM =
// OZ - TK
{
    38, 37, 36, 35,
    16, 15, 14, 13, 12, 11, 10, 9, 8,
    34, 33
};

const char u3_12 [] PROGMEM =
// TK - OZ
{
    33, 34,
    8, 9, 10, 11, 12, 13, 14, 15, 16,
    35, 36, 37, 38
};

const char u3_13 [] PROGMEM =
// KG - FW
{
    22, 21, 20, 19, 18, 17,
    16, 15, 14, 13, 12, 11, 10, 9, 8,
    34, 33, 32, 31, 30, 29, 28, 27
};


const char u3_17 [] PROGMEM =
// MO - FW
{
    42, 41, 40, 39, 38, 37, 36, 35,
    16, 15, 14, 13, 12, 11, 10, 9, 8,
    34, 33, 32, 31, 30, 29, 28, 27
};

const char u3_18 [] PROGMEM =
// FW - MO
{
    27, 28, 29, 30, 31, 32, 33, 34,
    8, 9, 10, 11, 12, 13, 14, 15, 16,
    35, 36, 37, 38, 39, 40, 41, 42
};


const char u6_03 [] PROGMEM =
// FT - KL
{
    23, 22, 21,
    20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
    10, 9, 8, 7, 6, 5, 4, 3, 2, 1
};

const char u6_04 [] PROGMEM =
// KL - FT
{
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23
};

const char u6_05 [] PROGMEM =
// MU - SE
{
    16, 15, 14, 13, 12, 11
};

const char u6_06 [] PROGMEM =
// SE - MU
{
    11, 12, 13, 14, 15, 16
};

const char u6_07 [] PROGMEM =
// MU - HS
{
    16, 15, 14, 13, 12, 11, 10, 9, 8, 7
};

const char u6_08 [] PROGMEM =
// HS - MU
{
    7, 8, 9, 10, 11, 12, 13, 14, 15, 16
};

const char u6_09 [] PROGMEM =
// FT - HS
{
    23, 22, 21, 20, 19, 18, 17,
    16, 15, 14, 13, 12, 11, 10, 9, 8, 7
};

const char u6_10 [] PROGMEM =
// HS - FT
{
    7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23
};

const char u6_11 [] PROGMEM =
// GF - KL
{
    26, 25, 24, 23, 22, 21,
    20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
    10, 9, 8, 7, 6, 5, 4, 3, 2, 1
};

const char u6_12 [] PROGMEM = 
// KL - GF
{
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26
};

const char u6_13 [] PROGMEM =
// FT - SE
{
    23, 22, 21, 20, 19, 18, 17,
    16, 15, 14, 13, 12, 11
};

const char u6_14 [] PROGMEM =
// SE - FT
{
    11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23
};

const char u6_15 [] PROGMEM =
// KG - HS
{
    22, 21, 20, 19, 18, 17,
    16, 15, 14, 13, 12, 11, 10, 9, 8, 7
};

const char u6_16 [] PROGMEM =
// HS - KG
{
    7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22
};

const char u6_17 [] PROGMEM =
// KG - KL
{
    22, 21, 20, 19, 18, 17,
    16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
};

const char u6_18 [] PROGMEM =
// KL - KG
{
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22
};

const char u6_19 [] PROGMEM =
// MU - KL
{
    16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
};

const char u6_20 [] PROGMEM =
// KL - MU
{
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
};

const char u6_21 [] PROGMEM =
// KG - MU
{
    22, 21, 20, 19, 18, 17, 16
};


/*
{
    "                ",
    "WESTFRIEDHOF    ", 
    "BORSTEI         ",
    "OLYMPIAPARK WEST", 
    "GOETHE-INSTITUT ",
    "LEONRODPLATZ    ",
    "LOTHSTRASSE     ",
    "SANDSTRASSE     ",
    "STIGLMAIERPLATZ ",
    "KARLSTRASSE     ",
    "HAUPTBHF NORD   ",
    "KARLSPLATZ      "
};
*/

uint8_t  linie;
uint8_t  kurs;
uint8_t  route;
uint16_t ziel;
uint8_t  hst;

uint8_t get_haltestellen_index()
{
    if (linie == 3)
    {
        if (route ==  1) { return pgm_read_byte (&u3_01 [hst-1]); }
        if (route ==  2) { return pgm_read_byte (&u3_02 [hst-1]); }
        if (route ==  3) { return pgm_read_byte (&u3_03 [hst-1]); }
        if (route ==  4) { return pgm_read_byte (&u3_04 [hst-1]); }
        if (route ==  5) { return pgm_read_byte (&u3_05 [hst-1]); }
        if (route ==  6) { return pgm_read_byte (&u3_06 [hst-1]); }
        if (route ==  7) { return pgm_read_byte (&u3_07 [hst-1]); }
        if (route ==  8) { return pgm_read_byte (&u3_08 [hst-1]); }
        if (route ==  9) { return pgm_read_byte (&u3_09 [hst-1]); }
        if (route == 10) { return pgm_read_byte (&u3_10 [hst-1]); }
        if (route == 11) { return pgm_read_byte (&u3_11 [hst-1]); }
        if (route == 12) { return pgm_read_byte (&u3_12 [hst-1]); }
        if (route == 13) { return pgm_read_byte (&u3_13 [hst-1]); }
        if (route == 17) { return pgm_read_byte (&u3_17 [hst-1]); }
        if (route == 18) { return pgm_read_byte (&u3_18 [hst-1]); }
    }
    if (linie == 6)
    {
        if (route ==  3) { return pgm_read_byte (&u6_03 [hst-1]); }
        if (route ==  4) { return pgm_read_byte (&u6_04 [hst-1]); }
        if (route ==  5) { return pgm_read_byte (&u6_05 [hst-1]); }
        if (route ==  6) { return pgm_read_byte (&u6_06 [hst-1]); }
        if (route ==  7) { return pgm_read_byte (&u6_07 [hst-1]); }
        if (route ==  8) { return pgm_read_byte (&u6_08 [hst-1]); }
        if (route ==  9) { return pgm_read_byte (&u6_09 [hst-1]); }
        if (route == 10) { return pgm_read_byte (&u6_10 [hst-1]); }
        if (route == 11) { return pgm_read_byte (&u6_11 [hst-1]); }
        if (route == 12) { return pgm_read_byte (&u6_12 [hst-1]); }
        if (route == 13) { return pgm_read_byte (&u6_13 [hst-1]); }
        if (route == 14) { return pgm_read_byte (&u6_14 [hst-1]); }
        if (route == 15) { return pgm_read_byte (&u6_15 [hst-1]); }
        if (route == 16) { return pgm_read_byte (&u6_16 [hst-1]); }
        if (route == 17) { return pgm_read_byte (&u6_17 [hst-1]); }
        if (route == 18) { return pgm_read_byte (&u6_18 [hst-1]); }
        if (route == 19) { return pgm_read_byte (&u6_19 [hst-1]); }
        if (route == 20) { return pgm_read_byte (&u6_20 [hst-1]); }
        if (route == 21) { return pgm_read_byte (&u6_21 [hst-1]); }
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
        strcpy_P(hstbuffer, haltestellen[get_haltestellen_index()]);
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
                        // Hst zurück, ohne Ton
                        hst--;
                        grundbild();
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
                        hst--;
                        grundbild();
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
                            if (!((i == 6) | (i ==3))) 
                            {
                                display_message(1);
                            } else {
                                linie = input / 100;
                                kurs = input % 100;
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