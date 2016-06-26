#ifndef MYSQL_SEED_MYSQL_SEED_STRING_MACROS_H_
#define MYSQL_SEED_MYSQL_SEED_STRING_MACROS_H_

/* copy string of a fixed size
 *─────────────────────────────────────────────────────────────────────────── */
typedef char CharBuff1;
typedef struct CharBuff2  { char chars[ 2] } CharBuff2;
typedef struct CharBuff3  { char chars[ 3] } CharBuff3;
typedef struct CharBuff4  { char chars[ 4] } CharBuff4;
typedef struct CharBuff5  { char chars[ 5] } CharBuff5;
typedef struct CharBuff6  { char chars[ 6] } CharBuff6;
typedef struct CharBuff7  { char chars[ 7] } CharBuff7;
typedef struct CharBuff8  { char chars[ 8] } CharBuff8;
typedef struct CharBuff9  { char chars[ 9] } CharBuff9;
typedef struct CharBuff10 { char chars[10] } CharBuff10;
typedef struct CharBuff11 { char chars[11] } CharBuff11;
typedef struct CharBuff12 { char chars[12] } CharBuff12;
typedef struct CharBuff13 { char chars[13] } CharBuff13;
typedef struct CharBuff14 { char chars[14] } CharBuff14;
typedef struct CharBuff15 { char chars[15] } CharBuff15;
typedef struct CharBuff16 { char chars[16] } CharBuff16;


/* helper macros
 *─────────────────────────────────────────────────────────────────────────── */
#define STRINGIFY(X) #X
#define EXPAND_STRINGIFY(X) STRINGIFY(X)

/* 0..9 → '0'..'9' */
#define ASCII_DIGIT(DIGIT) ((char) (((unsigned int) (DIGIT)) | 48u))

/* string putters */
#define PUT_CHAR_BUFF(PTR, BUFFER, WIDTH)			\
do {								\
	*((CharBuff ## WIDTH *restrict) PTR)			\
	= (CharBuff ## WIDTH) BUFFER;				\
	PTR = (__type_of__(PTR))				\
	      (((CharBuff ## WIDTH *restrict) PTR) + 1l);	\
} while (0)

#define PUT_CHAR(PTR, CHAR)	\
do {				\
	*(PTR) = CHAR;		\
	++(PTR);		\
} while (0)

#define PUTS_CLOSE(PTR)		\
do {				\
	PUT_CHAR(PTR, '\n');	\
	PUT_CHAR(PTR, '\0');	\
} while (0)


/* ANSI escape sequences
 *─────────────────────────────────────────────────────────────────────────── */
#define ANSI_BRIGHT "\e[1m"
#define ANSI_RED "\e[31m"
#define ANSI_RESET "\e[0m"
#define ANSI_UNDERLINE "\e[4m"
#define ANSI_NO_UNDERLINE "\e[24m"

#define UNDERLINE(STRING) ANSI_UNDERLINE STRING ANSI_NO_UNDERLINE
#define BRIGHTEN(STRING)  ANSI_BRIGHT    STRING ANSI_RESET
#define ERROR_HEADER(STRING) ANSI_BRIGHT ANSI_RED STRING ANSI_RESET

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_STRING_MACROS_H_ */
