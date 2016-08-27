#ifndef MYSQL_SEED_STRING_ASCII_UTILS_H_
#define MYSQL_SEED_STRING_ASCII_UTILS_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "utils/types/octet.h"	/* octet_t, OCTET_MAX */
#include <stdbool.h>		/* bool */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

typedef octet_t ascii_t;

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* ASCII limits, bounds
 * ========================================================================== */
#define ASCII_MAX OCTET_MAX
#define ASCII_VALID_MAX 127u
#define ASCII_CNT (ASCII_MAX + 1lu)
#define ASCII_VALID_CNT (ASCII_VALID_MAX + 1lu)
#define ASCII_CONTROL_CNT 33lu
#define ASCII_PRINTABLE_MIN ' '
#define ASCII_PRINTABLE_MAX '~'
#define ASCII_PRINTABLE_CNT 95lu
#define ASCII_NUMBER_CNT 10lu
#define ASCII_LETTER_CNT (ASCII_CASE_LETTER_CNT * 2lu)
#define ASCII_CONSONANT_CNT (ASCII_CASE_CONSONANT_CNT * 2lu)
#define ASCII_VOWEL_CNT (ASCII_CASE_VOWEL_CNT * 2lu)
#define ASCII_CASE_LETTER_CNT 26lu
#define ASCII_CASE_CONSONANT_CNT (ASCII_CASE_LETTER_CNT - ASCII_CASE_VOWEL_CNT)
#define ASCII_CASE_VOWEL_CNT 6lu
#define ASCII_PUNCTUATION_CNT 18lu
#define ASCII_MISC_SYMBOL_CNT 15lu

/* ASCII block macros
 * ========================================================================== */
#define _ASCII_CONTROL_BLOCK						\
  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,	\
 14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,	\
 28,  29,  30,  31
#define _ASCII_SYMBOL_BLOCK_A						\
' ',  '!',  '"',  '#',  '$',  '%',  '&',  '\'', '(',  ')',  '*',  '+',	\
',',  '-',  '.',  '/'
#define _ASCII_NUMBER_BLOCK						\
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
#define _ASCII_SYMBOL_BLOCK_B						\
':',  ';',  '<',  '=',  '>',  '?',  '@'
#define _ASCII_UPPER_BLOCK						\
'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',	\
'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
#define _ASCII_SYMBOL_BLOCK_C						\
'[', '\\', ']',  '^',  '_',  '`'
#define _ASCII_LOWER_BLOCK						\
'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',	\
'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
#define _ASCII_SYMBOL_BLOCK_D						\
'{',  '|',  '}',  '~'
#define _ASCII_DELETE ASCII_VALID_MAX
#define _ASCII_VALID_BLOCK						\
_ASCII_CONTROL_BLOCK,							\
_ASCII_PRINTABLE_BLOCK(UPPER, LOWER),					\
_ASCII_DELETE
#define _ASCII_INVALID_BLOCK						\
128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141,	\
142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155,	\
156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169,	\
170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183,	\
184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197,	\
198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211,	\
212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225,	\
226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,	\
240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253,	\
254, 255
#define _ASCII_UPPER_CONSONANTS_BLOCK					\
'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R',	\
'S', 'T', 'V', 'W', 'X', 'Z'
#define _ASCII_LOWER_CONSONANTS_BLOCK					\
'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r',	\
's', 't', 'v', 'w', 'x', 'z'
#define _ASCII_UPPER_VOWEL_BLOCK					\
'A', 'E', 'I', 'O', 'U', 'Y'
#define _ASCII_LOWER_VOWEL_BLOCK					\
'a', 'e', 'i', 'o', 'u', 'y'


/* ASCII set macros
 * ========================================================================== */
#define _ASCII_X_RANGE_CC(I, J, X) [(I) ... (J)] = (X)
#define _ASCII_X_RANGE_OC(I, J, X) _ASCII_X_RANGE_CC((I) + 1, J,       X)
#define _ASCII_X_RANGE_CO(I, J, X) _ASCII_X_RANGE_CC(I,       (J) - 1, X)
#define _ASCII_X_RANGE_OO(I, J, X) _ASCII_X_RANGE_CC((I) + 1, (J) - 1, X)
#define _ASCII_T_RANGE_CC(I, J) _ASCII_X_RANGE_CC(I, J, true)
#define _ASCII_T_RANGE_OO(I, J) _ASCII_X_RANGE_OO(I, J, true)
#define _ASCII_F_RANGE_CC(I, J) _ASCII_X_RANGE_CC(I, J, false)
#define _ASCII_F_RANGE_OC(I, J) _ASCII_X_RANGE_OC(I, J, false)
#define _ASCII_F_RANGE_CO(I, J) _ASCII_X_RANGE_CO(I, J, false)
#define _ASCII_F_RANGE_OO(I, J) _ASCII_X_RANGE_OO(I, J, false)
#define _ASCII_RANGE_T_VOWEL(I, J) [I] = true, _ASCII_F_RANGE_OO(I, J)
#define _ASCII_RANGE_F_VOWEL(I, J) _ASCII_T_RANGE_OO(I, J), [J] = false
#define _ASCII_LETTER_SWEEP(B, A, E, I, O, U, Y)			\
	_ASCII_RANGE_ ## B ## _VOWEL(A, E),				\
	_ASCII_RANGE_ ## B ## _VOWEL(E, I),				\
	_ASCII_RANGE_ ## B ## _VOWEL(I, O),				\
	_ASCII_RANGE_ ## B ## _VOWEL(O, U),				\
	_ASCII_RANGE_ ## B ## _VOWEL(U, Y)
#define _ASCII_CONSONANT_SWEEP(A, E, I, O, U, Y, Z)			\
	_ASCII_LETTER_SWEEP(F, A, E, I, O, U, Y), [Z] = true
#define _ASCII_VOWEL_SWEEP(A, E, I, O, U, Y)				\
	_ASCII_LETTER_SWEEP(T, A, E, I, O, U, Y), [Y] = true


/* ASCII map macros
 * ========================================================================== */
#define _ASCII_PRINTABLE_BLOCK(UPPER_MAP, LOWER_MAP)			\
_ASCII_SYMBOL_BLOCK_A,							\
_ASCII_NUMBER_BLOCK,							\
_ASCII_SYMBOL_BLOCK_B,							\
_ASCII_ ## UPPER_MAP ## _BLOCK,						\
_ASCII_SYMBOL_BLOCK_C,							\
_ASCII_ ## LOWER_MAP ## _BLOCK,						\
_ASCII_SYMBOL_BLOCK_D
#define _ASCII_MAP(UPPER_MAP, LOWER_MAP)				\
{									\
	_ASCII_PRINTABLE_BLOCK(UPPER_MAP, LOWER_MAP),			\
	_ASCII_INVALID_BLOCK						\
}

/* ASCII lookup table initializers
 * ========================================================================== */
#define _ASCII_VALIDS() { _ASCII_VALID_BLOCK }
#define _ASCII_PRINTABLES() { _ASCII_PRINTABLE_BLOCK(UPPER, LOWER) }
#define _ASCII_NUMBERS() { _ASCII_NUMBER_BLOCK }
#define _ASCII_LETTERS() { _ASCII_UPPER_BLOCK, _ASCII_LOWER_BLOCK }
#define _ASCII_CONSONANTS()						\
{									\
	_ASCII_UPPER_CONSONANTS_BLOCK,					\
	_ASCII_LOWER_CONSONANTS_BLOCK					\
}
#define _ASCII_VOWELS()							\
{									\
	_ASCII_UPPER_VOWEL_BLOCK,					\
	_ASCII_LOWER_VOWEL_BLOCK					\
}
#define _ASCII_UPPER_LETTERS() { _ASCII_UPPER_BLOCK }
#define _ASCII_LOWER_LETTERS() { _ASCII_LOWER_BLOCK }
#define _ASCII_UPPER_CONSONANTS() { _ASCII_UPPER_CONSONANTS_BLOCK }
#define _ASCII_LOWER_CONSONANTS() { _ASCII_LOWER_CONSONANTS_BLOCK }
#define _ASCII_UPPER_VOWELS() { _ASCII_UPPER_VOWEL_BLOCK }
#define _ASCII_LOWER_VOWELS() { _ASCII_LOWER_VOWEL_BLOCK }
#define _ASCII_PUNCTUATION()						\
{									\
	' ',  '!', '"',  '\'', '(',  ')',  ',',  '-',  '.',  '/',	\
	':',  ';', '?',  '[', '\\',  ']',  '{',  '}'			\
}
#define _ASCII_MISC_SYMBOLS()					\
{									\
	'#', '$', '%', '&', '*', '+', '<', '=', '>', '@', '^', '_',	\
	'`', '|', '~'							\
}
#define _ASCII_CONTROLS() { _ASCII_CONTROL_BLOCK, _ASCII_DELETE }

#define _ASCII_LOWER_MAP() _ASCII_MAP(LOWER, LOWER)
#define _ASCII_UPPER_MAP() _ASCII_MAP(UPPER, UPPER)
#define _ASCII_TOGGLE_MAP() _ASCII_MAP(LOWER, UPPER)
#define _ASCII_LETTER_SET()						\
{									\
	_ASCII_F_RANGE_CO(0,   'A'),					\
	_ASCII_T_RANGE_CC('A', 'Z'),					\
	_ASCII_F_RANGE_OO('Z', 'a'),					\
	_ASCII_T_RANGE_CC('a', 'z'),					\
	_ASCII_F_RANGE_OC('z', ASCII_MAX)				\
}
#define _ASCII_CONSONANT_SET()						\
{									\
	_ASCII_F_RANGE_CC(0,   'A'),					\
	_ASCII_CONSONANT_SWEEP('A', 'E', 'I', 'O', 'U', 'Y', 'Z'),	\
	_ASCII_F_RANGE_OC('Z', 'a'),					\
	_ASCII_CONSONANT_SWEEP('a', 'e', 'i', 'o', 'u', 'y', 'z'),	\
	_ASCII_F_RANGE_OC('z', ASCII_MAX)				\
}
#define _ASCII_VOWEL_SET()						\
{									\
	_ASCII_F_RANGE_CO(0, 'A'),					\
	_ASCII_VOWEL_SWEEP('A', 'E', 'I', 'O', 'U', 'Y'),		\
	_ASCII_F_RANGE_CO('Z', 'a'),					\
	_ASCII_VOWEL_SWEEP('a', 'e', 'i', 'o', 'u', 'y'),		\
	_ASCII_F_RANGE_CC('z', ASCII_MAX)				\
}

/* ASCII code macros
 * ========================================================================== */
#define IS_ASCII_DIGIT(DIGIT)	(((DIGIT) < ':') && ((DIGIT) > '/'))

/* 0..9 → '0'..'9' */
#define DIGIT_TO_ASCII(DIGIT)	(((unsigned int) (DIGIT)) | 48u)

/* '0'..'9' → 0..9 */
#define ASCII_TO_DIGIT(ASCII)	(((unsigned int) (ASCII)) & 15u)

/* 'a' → 'A', 'A' → 'A' */
#define ASCII_UPPERCASE(CHAR)	(((unsigned int) (CHAR))  & 95u)

/* 'a' → 'a', 'A' → 'a' */
#define ASCII_LOWERCASE(CHAR)	(((unsigned int) (CHAR))  | 32u)

/* 'a' → 'A', 'A' → 'a' */
#define ASCII_TOGGLECASE(CHAR)	(((unsigned int) (CHAR))  ^ 32u)

/* ASCII lookup tables
 * ========================================================================== */
/* ordered groups */
extern const ascii_t ASCII_VALIDS[ASCII_VALID_CNT];
extern const ascii_t ASCII_PRINTABLES[ASCII_PRINTABLE_CNT];
extern const ascii_t ASCII_NUMBERS[ASCII_NUMBER_CNT];
extern const ascii_t ASCII_LETTERS[ASCII_LETTER_CNT];
extern const ascii_t ASCII_CONSONANTS[ASCII_CONSONANT_CNT];
extern const ascii_t ASCII_VOWELS[ASCII_VOWEL_CNT];
extern const ascii_t ASCII_UPPER_LETTERS[ASCII_CASE_LETTER_CNT];
extern const ascii_t ASCII_LOWER_LETTERS[ASCII_CASE_LETTER_CNT];
extern const ascii_t ASCII_UPPER_CONSONANTS[ASCII_CASE_CONSONANT_CNT];
extern const ascii_t ASCII_LOWER_CONSONANTS[ASCII_CASE_CONSONANT_CNT];
extern const ascii_t ASCII_UPPER_VOWELS[ASCII_CASE_VOWEL_CNT];
extern const ascii_t ASCII_LOWER_VOWELS[ASCII_CASE_VOWEL_CNT];
extern const ascii_t ASCII_PUNCTUATION[ASCII_PUNCTUATION_CNT];
extern const ascii_t ASCII_MISC_SYMBOLS[ASCII_MISC_SYMBOL_CNT];
extern const ascii_t ASCII_CONTROLS[ASCII_CONTROL_CNT];

/* sets */
extern const bool ASCII_LETTER_SET[ASCII_CNT];
extern const bool ASCII_CONSONANT_SET[ASCII_CNT];
extern const bool ASCII_VOWEL_SET[ASCII_CNT];

/* maps */
extern const ascii_t ASCII_LOWER_MAP[ASCII_CNT];
extern const ascii_t ASCII_UPPER_MAP[ASCII_CNT];
extern const ascii_t ASCII_TOGGLE_MAP[ASCII_CNT];

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS
 *
 *
 * FUNCTION-LIKE MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * FUNCTION-LIKE MACROS
 *
 *
 * HELPER FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline bool
is_ascii(const char byte)
{
	return (byte & 0x80) == 0x00;
}

inline bool
is_printable_ascii(const char byte)
{
	return (byte >= 0x20) && (byte <= 0x7E);
}

/* character map case (ignores non-letters) */
inline ascii_t
lowercase_ascii(const ascii_t ascii)
{
	return ASCII_LOWER_MAP[ascii];
}

inline ascii_t
uppercase_ascii(ascii_t ascii)
{
	return ASCII_UPPER_MAP[ascii];
}

inline ascii_t
togglecase_ascii(ascii_t ascii)
{
	return ASCII_TOGGLE_MAP[ascii];
}

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER FUNCTIONS
 *
 *
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline bool
is_ascii_string(const char *restrict string)
{
	while (1) {
		if (*string == '\0')
			return true;

		if (is_ascii(*string))
			++string;
		else
			return false;
	}
}

inline bool
is_printable_ascii_string(const char *restrict bytes)
{
	while (is_printable_ascii(*bytes))
		++bytes;

	return *bytes == '\0';
}


/* string map case (ignores non-letters) */
inline void
lowercase_ascii_string(ascii_t *restrict string)
{
	while (*string != '\0') {
		*string = lowercase_ascii(*string);
		++string;
	}
}

inline void
uppercase_ascii_string(ascii_t *restrict string)
{
	while (*string != '\0') {
		*string = uppercase_ascii(*string);
		++string;
	}
}

inline void
togglecase_ascii_string(ascii_t *restrict string)
{
	while (*string != '\0') {
		*string = togglecase_ascii(*string);
		++string;
	}
}

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS */

#endif /* ifndef MYSQL_SEED_STRING_ASCII_UTILS_H_ */
