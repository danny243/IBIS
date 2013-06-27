/*
 * routes.h
 *
 * Created: 27.06.2013 01:32:14
 *  Author: DSchuhmann
 */ 


#ifndef ROUTES_H_
#define ROUTES_H_


////////////////////////////////////////////////////////////////////////////////
// Haltestellen- und Zielliste
const char haltestellen[][17] PROGMEM =
{
    "                ", //  0
    "KL. GROSSHADERN ", //  1
    "GROSSHADERN     ", //  2
    "HADERNER STERN  ", //  3
    "HOLZAPFELKREUTH ", //  4
    "WESTPARK        ", //  5
    "PARTNACHPLATZ   ", //  6
    "HARRAS          ", //  7
    "IMPLERSTRASSE   ", //  8
    "POCCISTRASSE    ", //  9
    "GOETHEPLATZ     ", // 10
    "SENDLINGER TOR  ", // 11
    "MARIENPLATZ     ", // 12
    "ODEONSPLATZ     ", // 13
    "UNIVERSITAET    ", // 14
    "GISELASTRASSE   ", // 15
    "MUENCHNER FREIH.", // 16
    "DIETLINDENSTR.  ", // 17
    "NORDFRIEDHOF    ", // 18
    "ALTE HEIDE      ", // 19
    "STUDENTENSTADT  ", // 20
    "FREIMANN        ", // 21
    "KIEFERNGARTEN   ", // 22
    "FROETTMANING    ", // 23
    "GARCHING-HOCHBR.", // 24
    "GARCHING        ", // 25
    "GARCHING-FORSCH.", // 26
    "FUERSTENRIED W. ", // 27
    "BASLER STRASSE  ", // 28
    "FORSTENRIEDER A.", // 29
    "MACHTLFINGERSTR.", // 30
    "AIDENBACHSTR.   ", // 31
    "OBERSENDLING    ", // 32
    "THALKIRCHEN     ", // 33
    "BRUDERMUEHLSTR. ", // 34
    "BONNER PLATZ    ", // 35
    "SCHEIDPLATZ     ", // 36
    "PETUELRING      ", // 37
    "OLYMPIAZENTRUM  ", // 38
    "OBERWIESENFELD  ", // 39
    "OLYMPIA-EINK. Z.", // 40
    "MOOS. ST-MARTPL.", // 41
    "MOOSACH         ", // 42
    "SONDERFAHRT     ", // 43
    "EINRUECKFAHRT   ", // 44
    "NICHT EINSTEIGEN", // 45
    "SCHULUNGSFAHRT  ", // 46
    "PARTYZUG        ", // 47
    "PROBEFAHRT      ", // 48
    "GEORG-BRAUCHLE-R", // 49
    "WESTFRIEDHOF    ", // 50
    "GERN            ", // 51
    "ROTKREUZPLATZ   ", // 52
    "MAILINGERSTRASSE", // 53
    "STIGLMAIERPLATZ ", // 54
    "HAUPTBAHNHOF    ", // 55
    "FRAUNHOFERSTR.  ", // 56
    "KOLUMBUSPLATZ   ", // 57
    "CANDIDPLATZ     ", // 58
    "WETTERSTEINPLATZ", // 59
    "ST.-QUIRIN-PLATZ", // 60
    "MANGFALLPLATZ   ", // 61
    "FELDMOCHING     ", // 62
    "HASENBERGL      ", // 63
    "DUELFERSTRASSE  ", // 64
    "HARTHOF         ", // 65
    "AM HART         ", // 66
    "FRANKFURTER RING", // 67
    "MILBERTSHOFEN   ", // 68
    "HOHENZOLLERNPL. ", // 69
    "JOSEPHSPLATZ    ", // 70
    "THERESIENSTR    ", // 71
    "KOENIGSPLATZ    ", // 72
    "SILBERHORNSTR.  ", // 73
    "UNTERSBERGSTR.  ", // 74
    "GIESING BF.     ", // 75
    "KARL-PREIS-PLATZ", // 76
    "INNSBRUCKER RING", // 77
    "JOSEPHSBURG     ", // 78
    "KREILLERSTRASSE ", // 79
    "TRUDERING       ", // 80
    "MOOSFELD        ", // 81
    "MESSESTADT WEST ", // 82
    "MESSESTADT OST  "  // 83
};

////////////////////////////////////////////////////////////////////////////////
// U1-Routen
const char u1_01 [] PROGMEM =
// WF - ML
{
    50, 51, 52, 53, 54, 55, 11,
    56, 57, 58, 59, 60, 61
};

const char u1_02 [] PROGMEM =
// ML - WF
{
    61, 60, 59, 58, 57, 56,
    11, 55, 54, 53, 52, 51, 50
};

const char u1_03 [] PROGMEM =
// WF - SU
{
    50, 51, 52, 53, 54, 55, 11,
};

const char u1_04 [] PROGMEM =
// SU - WF
{
    11, 55, 54, 53, 52, 51, 50
};

const char u1_07 [] PROGMEM =
// WF - ME
{
    50, 51, 52, 53, 54, 55, 11, 56, 57,
    73, 74, 75, 76, 77, 78, 79, 80, 81, 82
};

const char u1_08 [] PROGMEM =
// ME - WF
{
    82, 81, 80, 79, 78, 77, 76, 75, 74, 73,
    57, 56, 11, 55, 54, 53, 52, 51, 50
};

const char u1_11 [] PROGMEM =
// OE - ML
{
    40, 49, 50, 51, 52, 53, 54, 55, 11, 
    56, 57, 58, 59, 60, 61 
};

const char u1_12 [] PROGMEM =
// ML - OE
{
    61, 60, 59, 58, 57, 56,
    11, 55, 54, 53, 52, 51, 50, 49, 40
};

////////////////////////////////////////////////////////////////////////////////
// U2-Routen
const char u2_01 [] PROGMEM =
// FM - MS
{
    62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72,
    55, 11, 56, 57,
    73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83
};

const char u2_02 [] PROGMEM =
// MS - FM
{
    83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73,
    57, 56, 11, 55, 
    72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62
};

const char u2_03 [] PROGMEM =
// HF - IR
{
    65, 66, 67, 68, 69, 70, 71, 72,
    55, 11, 56, 57,
    73, 74, 75, 76, 77
};

const char u2_05 [] PROGMEM =
// FM - IR
{
    62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72,
    55, 11, 56, 57,
    73, 74, 75, 76, 77
};

const char u2_06 [] PROGMEM =
// IR - FM
{
    77, 76, 75, 74, 73,
    57, 56, 11, 55,
    72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62
};

const char u2_07 [] PROGMEM =
// MI - MS
{
    68, 69, 70, 71, 72,
    55, 11, 56, 57,
    73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83
};

const char u2_08 [] PROGMEM =
// MS - MI
{
    83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73,
    57, 56, 11, 55,
    72, 71, 70, 69, 68
};

const char u2_09 [] PROGMEM =
// HF - MS
{
    65, 66, 67, 68, 69, 70, 71, 72,
    55, 11, 56, 57,
    73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83
};

const char u2_10 [] PROGMEM =
// MS - HF
{
    83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73,
    57, 56, 11, 55,
    72, 71, 70, 69, 68, 67, 66, 65
};

const char u2_11 [] PROGMEM =
// HU - MS
{
    55, 11, 56, 57,
    73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83
};

const char u2_12 [] PROGMEM =
// MS - HU
{
    83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73,
    57, 56, 11, 55
};

const char u2_17 [] PROGMEM =
// MI - KO
{
    68, 69, 70, 71, 72,
    55, 11, 56, 57
};

const char u2_18 [] PROGMEM =
// KO - MI
{
    57, 56, 11, 55,
    72, 71, 70, 69, 68
};

////////////////////////////////////////////////////////////////////////////////
// U3-Routen
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

////////////////////////////////////////////////////////////////////////////////
// U6-Routen
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


#endif /* ROUTES_H_ */