#ifndef MYSQL_SEED_MYSQL_SEED_STRING_MACROS_H_
#define MYSQL_SEED_MYSQL_SEED_STRING_MACROS_H_

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
