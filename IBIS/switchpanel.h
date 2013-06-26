/*
 * switchpanel.h
 *
 * Created: 22.06.2013 18:03:11
 *  Author: DSchuhmann
 */ 


#ifndef SWITCHPANEL_H_
#define SWITCHPANEL_H_


#ifndef F_CPU
#define F_CPU 4000000UL
#endif

////////////////////////////////////////////////////////////////////////////////
// Pinbelegung f�r das Switchpanel, f�r die Spalten werden 3 Pins ben�tigt,
// die Zeilen ben�tigen einen Port (8 Pins)

//  LCD DB4-DB7 <-->   PORTD Bit PD0-PD3
#define SWITCH_COL_PORT  PORTC
#define SWITCH_COL_DDR   DDRC
#define SWITCH_COL_PIN   PINC

#define SWITCH_ROW_PORT  PORTD
#define SWITCH_ROW_DDR   DDRD
#define SWITCH_ROW_PIN   PIND

void col_init(void);

void row_init(void);

unsigned char read_key(void);

#endif /* SWITCHPANEL_H_ */