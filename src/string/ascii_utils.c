#include "string/ascii.h" /* ascii_t, lookup tables */


/* ASCII groups (ordered by ascending ASCII value)
 * ========================================================================== */
const ascii_t ASCII_VALIDS[ASCII_VALID_CNT]		       = _ASCII_VALIDS();
const ascii_t ASCII_PRINTABLES[ASCII_PRINTABLE_CNT]	       = _ASCII_PRINTABLES();
const ascii_t ASCII_NUMBERS[ASCII_NUMBER_CNT]		       = _ASCII_NUMBERS();
const ascii_t ASCII_LETTERS[ASCII_LETTER_CNT]		       = _ASCII_LETTERS();
const ascii_t ASCII_CONSONANTS[ASCII_CONSONANT_CNT]	       = _ASCII_CONSONANTS();
const ascii_t ASCII_VOWELS[ASCII_VOWEL_CNT]		       = _ASCII_VOWELS();
const ascii_t ASCII_UPPER_LETTERS[ASCII_CASE_LETTER_CNT]       = _ASCII_UPPER_LETTERS();
const ascii_t ASCII_LOWER_LETTERS[ASCII_CASE_LETTER_CNT]       = _ASCII_LOWER_LETTERS();
const ascii_t ASCII_UPPER_CONSONANTS[ASCII_CASE_CONSONANT_CNT] = _ASCII_UPPER_CONSONANTS();
const ascii_t ASCII_LOWER_CONSONANTS[ASCII_CASE_CONSONANT_CNT] = _ASCII_LOWER_CONSONANTS();
const ascii_t ASCII_UPPER_VOWELS[ASCII_CASE_VOWEL_CNT]	       = _ASCII_UPPER_VOWELS();
const ascii_t ASCII_LOWER_VOWELS[ASCII_CASE_VOWEL_CNT]	       = _ASCII_LOWER_VOWELS();
const ascii_t ASCII_PUNCTUATION[ASCII_PUNCTUATION_CNT]	       = _ASCII_PUNCTUATION();
const ascii_t ASCII_MISC_SYMBOLS[ASCII_MISC_SYMBOL_CNT]	       = _ASCII_MISC_SYMBOLS();
const ascii_t ASCII_CONTROLS[ASCII_CONTROL_CNT]		       = _ASCII_CONTROLS();

/* ASCII sets (boolean indicates membership)
 * ========================================================================== */
const bool ASCII_LETTER_SET[ASCII_CNT]	  = _ASCII_LETTER_SET();
const bool ASCII_CONSONANT_SET[ASCII_CNT] = _ASCII_CONSONANT_SET();
const bool ASCII_VOWEL_SET[ASCII_CNT]	  = _ASCII_VOWEL_SET();

/* ASCII maps ('code' maps to 'MAP[code]')
 * ========================================================================== */
const ascii_t ASCII_LOWER_MAP[ASCII_CNT]  = _ASCII_LOWER_MAP();
const ascii_t ASCII_UPPER_MAP[ASCII_CNT]  = _ASCII_UPPER_MAP();
const ascii_t ASCII_TOGGLE_MAP[ASCII_CNT] = _ASCII_TOGGLE_MAP();


extern inline bool is_ascii_string(const char *restrict bytes);

/* character map case (ignores non-letters) */
extern inline ascii_t
lowercase_ascii(const ascii_t ascii);
extern inline ascii_t
uppercase_ascii(const ascii_t ascii);
extern inline ascii_t
togglecase_ascii(const ascii_t ascii);

/* string map case (ignores non-letters) */
extern inline void
uppercase_ascii_string(ascii_t *restrict string);
extern inline void
lowercase_ascii_string(ascii_t *restrict string);
extern inline void togglecase_ascii_string(ascii_t *restrict string);
