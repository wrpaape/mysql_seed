#ifndef MEMORY_UTILS_WORD_PATTERN_H_
#define MEMORY_UTILS_WORD_PATTERN_H_

#ifdef __cplusplus /* ensure C linkage */
extern "C" {
#ifndef restrict /* replace 'restrict' with c++ compatible '__restrict__' */
#define restrict __restrict__
#endif
#endif


/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "memory_utils.h"	/* Width<WIDTH> word_t, WORD_SIZE */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

struct WordLink {
	word_t word;
	struct WordLink *next;
};

struct WordPattern {
	struct WordLink *words;
	const unsigned int word_count;
	const unsigned int base_count;
};

#if   !defined(WORD_SIZE)
#	error "sizeof(word_t) is unknown to preprocessor: 'WORD_SIZE' is undefined"
#elif (WORD_SIZE == 8lu) /*		    buffer | LCM(WORD_SIZE, <WIDTH> */
struct WordPattern1  { struct WordLink words[ 1]; };	/*   8 */
struct WordPattern2  { struct WordLink words[ 1]; };	/*   8 */
struct WordPattern3  { struct WordLink words[ 3]; };	/*  24 */
struct WordPattern4  { struct WordLink words[ 1]; };	/*   8 */
struct WordPattern5  { struct WordLink words[ 5]; };	/*  40 */
struct WordPattern6  { struct WordLink words[ 3]; };	/*  24 */
struct WordPattern7  { struct WordLink words[ 7]; };	/*  56 */
struct WordPattern8  { struct WordLink words[ 1]; };	/*   8 */
struct WordPattern9  { struct WordLink words[ 9]; };	/*  72 */
struct WordPattern10 { struct WordLink words[ 5]; };	/*  40 */
struct WordPattern11 { struct WordLink words[11]; };	/*  88 */
struct WordPattern12 { struct WordLink words[ 3]; };	/*  24 */
struct WordPattern13 { struct WordLink words[13]; };	/* 104 */
struct WordPattern14 { struct WordLink words[ 7]; };	/*  56 */
struct WordPattern15 { struct WordLink words[15]; };	/* 120 */
struct WordPattern16 { struct WordLink words[ 2]; };	/*  16 */
#elif (WORD_SIZE == 7lu)
struct WordPattern1  { struct WordLink words[ 1]; };	/*   8 */
struct WordPattern2  { struct WordLink words[ 1]; };	/*   8 */
struct WordPattern3  { struct WordLink words[ 3]; };	/*  24 */
struct WordPattern4  { struct WordLink words[ 1]; };	/*   8 */
struct WordPattern5  { struct WordLink words[ 5]; };	/*  40 */
struct WordPattern6  { struct WordLink words[ 3]; };	/*  24 */
struct WordPattern7  { struct WordLink words[ 7]; };	/*  56 */
struct WordPattern8  { struct WordLink words[ 1]; };	/*   8 */
struct WordPattern9  { struct WordLink words[ 9]; };	/*  72 */
struct WordPattern10 { struct WordLink words[ 5]; };	/*  40 */
struct WordPattern11 { struct WordLink words[11]; };	/*  88 */
struct WordPattern12 { struct WordLink words[ 3]; };	/*  24 */
struct WordPattern13 { struct WordLink words[13]; };	/* 104 */
struct WordPattern14 { struct WordLink words[ 7]; };	/*  56 */
struct WordPattern15 { struct WordLink words[15]; };	/* 120 */
struct WordPattern16 { struct WordLink words[ 2]; };	/*  16 */
#elif (WORD_SIZE == 6lu)
#elif (WORD_SIZE == 5lu)
#elif (WORD_SIZE == 4lu)
#elif (WORD_SIZE == 3lu)
#elif (WORD_SIZE == 2lu)
#else
#endif

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
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
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS
 *
 *
 * HELPER FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER FUNCTIONS */


#ifdef __cplusplus /* close 'extern "C" {' */
}
#endif

#endif /* ifndef MEMORY_UTILS_WORD_PATTERN_H_ */
