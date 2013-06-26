/*
 * routes.h
 *
 * Created: 27.06.2013 01:32:14
 *  Author: DSchuhmann
 */ 


#ifndef ROUTES_H_
#define ROUTES_H_


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


#endif /* ROUTES_H_ */