IBIS
====

Simulation eines IBIS-Bordcomputers (Siemens/HPW)

### Hardware

Derzeit wird ein Atmel ATmega16-Mikrocontroller verwendet, dieser genügt zur Ansteuerung der Matrix-Tastatur (3x8-Matrix) und des LCD-Displays (HD44780 im 4-Bit-Modus) und bietet genug Reserven für Erweiterungen (Magnetkartenleser, Verbindung mit dem PC, Helligkeits- und Kontraststeuerung).

Der Flash-Speicher von 16 KB genügt für das Münchner U-Bahnnetz (8 Linien, 100 Bahnhöfe und 102 Routen). Für größere Netze wird ein Controller mit mehr Speicher benötigt (z.B. ATmega644PA).

#### Belegung der Ports (in der Software änderbar)

* **PORT A** *(PA0..PA2)*: Tastenmatrix Columns
* **PORT D** *(PD0..PD7)*: Tastenmatrix Rows
* **PORT B** *(PB0..PB3)*: LCD Daten DB4..DB7, *(PB4)*: RS, *(PB5)*: EN

#### Belegung der Tastatur

Die Tastatur verfügt über eine 16-polige Anschlussleiste, an die außer der 3x8-Matrix auch ein Helligkeitssensor (zur Einstellung der LCD-Hintergrundbeleuchtung) und zwei Tasten für den LCD-Kontrast angeschlossen sind. 

Die Pins 1..3 gehen an PA0 bis PA2, die Pins 6..13 sind mit PB0..PB7 verschaltet. 

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

Die Software ist in C geschrieben (ARV-GCC, Atmel Studio 6.1). Warnung: Der Code ist einigermaßen bis ziemlich grausam, insbesondere, was die Entprellung der Matrixtastatur, die Blinktexte (ich sag nur delay_ms) und die Datenablage der Routen angeht.

### Lizenz

Copyright 2013 Daniel Schuhmann

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
