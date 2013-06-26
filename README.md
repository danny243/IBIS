IBIS
====

Simulation eines IBIS-Bordcomputers (Siemens/HPW)

### Hardware

Derzeit wird ein Atmel ATMega8-Mikrocontroller verwendet, dieser genügt zur Ansteuerung der Matrix-Tastatur (3x8-Matrix) und des LCD-Displays (HD44780 im 4-Bit-Modus).

Da der Flash-Speicher von 8 KB nur für sehr wenige Linien und Routen ausreicht und für Erweiterungen mehr freie Portleitungen wünschenswert sind, wird zukünftig ein ATMega16 oder größer (z.B. ATmega644PA) verwendet.

Schaltpläne und so werden dann folgen.

### Software

Die Software ist in C geschrieben (ARV-GCC, Atmel Studio 6.1). Warnung: Der Code ist einigermaßen bis ziemlich grausam, insbesondere, was die Entprellung der Matrixtastatur und die Blinktexte (ich sag nur delay_ms) angeht. 
