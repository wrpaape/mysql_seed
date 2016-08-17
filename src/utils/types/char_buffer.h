#ifndef UTILS_TYPES_CHAR_BUFFER_H_
#define UTILS_TYPES_CHAR_BUFFER_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* for copying a string of a fixed size */
typedef char   CharBuffer1;
typedef struct CharBuffer2  { char chars[ 2]; } CharBuffer2;
typedef struct CharBuffer3  { char chars[ 3]; } CharBuffer3;
typedef struct CharBuffer4  { char chars[ 4]; } CharBuffer4;
typedef struct CharBuffer5  { char chars[ 5]; } CharBuffer5;
typedef struct CharBuffer6  { char chars[ 6]; } CharBuffer6;
typedef struct CharBuffer7  { char chars[ 7]; } CharBuffer7;
typedef struct CharBuffer8  { char chars[ 8]; } CharBuffer8;
typedef struct CharBuffer9  { char chars[ 9]; } CharBuffer9;
typedef struct CharBuffer10 { char chars[10]; } CharBuffer10;
typedef struct CharBuffer11 { char chars[11]; } CharBuffer11;
typedef struct CharBuffer12 { char chars[12]; } CharBuffer12;
typedef struct CharBuffer13 { char chars[13]; } CharBuffer13;
typedef struct CharBuffer14 { char chars[14]; } CharBuffer14;
typedef struct CharBuffer15 { char chars[15]; } CharBuffer15;
typedef struct CharBuffer16 { char chars[16]; } CharBuffer16;
typedef struct CharBuffer17 { char chars[17]; } CharBuffer17;
typedef struct CharBuffer18 { char chars[18]; } CharBuffer18;
typedef struct CharBuffer19 { char chars[19]; } CharBuffer19;
typedef struct CharBuffer20 { char chars[20]; } CharBuffer20;
typedef struct CharBuffer21 { char chars[21]; } CharBuffer21;
typedef struct CharBuffer22 { char chars[22]; } CharBuffer22;
typedef struct CharBuffer23 { char chars[23]; } CharBuffer23;
typedef struct CharBuffer24 { char chars[24]; } CharBuffer24;
typedef struct CharBuffer25 { char chars[25]; } CharBuffer25;
typedef struct CharBuffer26 { char chars[26]; } CharBuffer26;
typedef struct CharBuffer27 { char chars[27]; } CharBuffer27;
typedef struct CharBuffer28 { char chars[28]; } CharBuffer28;
typedef struct CharBuffer29 { char chars[29]; } CharBuffer29;
typedef struct CharBuffer30 { char chars[30]; } CharBuffer30;
typedef struct CharBuffer31 { char chars[31]; } CharBuffer31;
typedef struct CharBuffer32 { char chars[32]; } CharBuffer32;
typedef struct CharBuffer33 { char chars[33]; } CharBuffer33;

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define CHAR_BUFFER_WIDTH_MAX 32u

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS
 *
 *
 * HELPER MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define FOR_ALL_CHAR_BUFFER_WIDTHS(MACRO)				\
MACRO(1)								\
MACRO(2)								\
MACRO(3)								\
MACRO(4)								\
MACRO(5)								\
MACRO(6)								\
MACRO(7)								\
MACRO(8)								\
MACRO(9)								\
MACRO(10)								\
MACRO(11)								\
MACRO(12)								\
MACRO(13)								\
MACRO(14)								\
MACRO(15)								\
MACRO(16)								\
MACRO(17)								\
MACRO(18)								\
MACRO(19)								\
MACRO(20)								\
MACRO(21)								\
MACRO(22)								\
MACRO(23)								\
MACRO(24)								\
MACRO(25)								\
MACRO(26)								\
MACRO(27)								\
MACRO(28)								\
MACRO(29)								\
MACRO(30)								\
MACRO(31)								\
MACRO(32)

#define FOR_ALL_CHAR_BUFFER_WIDTHS_STOP(MACRO)				\
MACRO(1,   2)								\
MACRO(2,   3)								\
MACRO(3,   4)								\
MACRO(4,   5)								\
MACRO(5,   6)								\
MACRO(6,   7)								\
MACRO(7,   8)								\
MACRO(8,   9)								\
MACRO(9,  10)								\
MACRO(10, 11)								\
MACRO(11, 12)								\
MACRO(12, 13)								\
MACRO(13, 14)								\
MACRO(14, 15)								\
MACRO(15, 16)								\
MACRO(16, 17)								\
MACRO(17, 18)								\
MACRO(18, 19)								\
MACRO(19, 20)								\
MACRO(20, 21)								\
MACRO(21, 22)								\
MACRO(22, 23)								\
MACRO(23, 24)								\
MACRO(24, 25)								\
MACRO(25, 26)								\
MACRO(26, 27)								\
MACRO(27, 28)								\
MACRO(28, 29)								\
MACRO(29, 30)								\
MACRO(30, 31)								\
MACRO(31, 32)								\
MACRO(32, 33)

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER MACROS */
#endif /* ifndef UTILS_TYPES_CHAR_BUFFER_H_ */
