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

/* Tasteninterface
 * 3 Zeilen * 8 Spalten
 *
 * 0x00            0 = Keine Taste gedrückt
 * 0x01 .. 0x09 1..9 = Tastenfeld 1..9
 * 0x0B           11 = Tastenfeld 0
 * 0x0A           10 = Löschen
 * 0x0C           12 = Eingabe/Quittieren
 * 0x0E           14 = + Hst 
 * 0x11           17 = - Hst
 * 0x0F           15 = + Hst (Ansage unterdrückt)
 * 0x12           18 = - Hst (Ansage unterdrückt)
 * 0x0D           13 = Rundspruch Quittieren
 * 0x10           16 = Unfall
 * 0x15           21 = Ohne Ausweis
 * 0x18           24 = Sprechwunsch
 * 0x14           20 = + Zahlgrenze
 * 0x17           23 = - Zahlgrenze
 * 0x13           19 = H/R
 * 0x16           22 = LZA
 */ 


#ifndef SWITCHPANEL_H_
#define SWITCHPANEL_H_


#ifndef F_CPU
#define F_CPU 4000000UL
#endif

////////////////////////////////////////////////////////////////////////////////
// Pinbelegung für das Switchpanel, für die Spalten werden 3 Pins benötigt,
// die Zeilen benötigen einen Port (8 Pins)

//  COL Pins 1..3 <-->   PORTA Bit PD0-PD2
#define SWITCH_COL_PORT  PORTA
#define SWITCH_COL_DDR   DDRA
#define SWITCH_COL_PIN   PINA

//  ROW Pins 6..13 <-->   PORTD Bit PD0-PD7
#define SWITCH_ROW_PORT  PORTD
#define SWITCH_ROW_DDR   DDRD
#define SWITCH_ROW_PIN   PIND

void col_init(void);

void row_init(void);

unsigned char read_key(void);

#endif /* SWITCHPANEL_H_ */