IBIS
====

Simulation eines IBIS-Bordcomputers (Siemens/HPW)

### Hardware

Derzeit wird ein Atmel ATMega8-Mikrocontroller verwendet, dieser genügt zur Ansteuerung der Matrix-Tastatur (3x8-Matrix) und des LCD-Displays (HD44780 im 4-Bit-Modus).

Da der Flash-Speicher von 8 KB nur für sehr wenige Linien und Routen ausreicht und für Erweiterungen mehr freie Portleitungen wünschenswert sind, wird zukünftig ein ATMega16 oder größer (z.B. ATmega644PA) verwendet.

#### Belegung der Ports (in der Software änderbar)

* **PORT B** *(PB0..PB3)*: Daten DB4..DB7, *(PB4)*: RS, *(PB5)*: EN
* **PORT C** *(PC0..PC2)*: Tastenmatrix Columns
* **PORT D** *(PD0..PD7)*: Tastenmatrix Rows

#### Belegung der Tastatur

* **02 - 07**: H/R
* **02 - 06**: LZA
* **01 - 07**: Zahlgrenze +
* **01 - 06**: Zahlgrenze -
* **03 - 07**: Ohne Ausweis
* **03 - 06**: Sprechwunsch
* **02 - 09**: Rundspruch quittieren
* **02 - 08**: Unfall
* **01 - 09**: + Hst
* **01 - 08**: - Hst
* **03 - 09**: + Hst (ohne Ansage)
* **03 - 08**: - Hst (ohne Ansage)
* **02 - 10**: 1 (Linie/Kurs)
* **01 - 10**: 2 (Route)
* **03 - 10**: 3 (Ziel)
* **02 - 11**: 4 (Zahlgrenze)
* **01 - 11**: 5 (Kanal)
* **03 - 11**: 6 (Entwerter sperren)
* **02 - 13**: 7 (Meldung)
* **01 - 13**: 8 (Uhrzeit/Datum)
* **03 - 13**: 9 (Entwerter entsperren)
* **01 - 12**: 0 (Keine Fahrgäste)
* **02 - 12**: Löschen
* **03 - 12**: Eingabe/Quittieren

Schaltpläne und so werden dann folgen.

### Software

Die Software ist in C geschrieben (ARV-GCC, Atmel Studio 6.1). Warnung: Der Code ist einigermaßen bis ziemlich grausam, insbesondere, was die Entprellung der Matrixtastatur und die Blinktexte (ich sag nur delay_ms) angeht. 
