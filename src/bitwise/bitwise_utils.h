#ifndef MYSQL_SEED_BITWISE_BITWISE_UTILS_H_
#define MYSQL_SEED_BITWISE_BITWISE_UTILS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "utils/word_attrs.h"	/* word_t, WORD_BITS, stdint */

#ifdef WORD_BITS
#	define WORD_SHIFT_MAX WORD_BITS
#else
#	error "compile-time constant 'WORD_BITS' unknown"
#endif /* ifndef WORD_BITS */


/* bitwise rotation */
inline word_t
word_rotate_left(const word_t word,
		 const word_t rotate)
{
	return (word << rotate) | (word >> (-rotate & (WORD_BITS - 1)));
}

inline word_t
word_rotate_right(const word_t word,
		  const word_t rotate)
{
	return (word >> rotate) | (word << (-rotate & (WORD_BITS - 1)));
}


#endif /* ifndef MYSQL_SEED_BITWISE_BITWISE_UTILS_H_ */
