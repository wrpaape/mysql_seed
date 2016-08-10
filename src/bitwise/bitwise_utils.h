#ifndef MYSQL_SEED_BITWISE_BITWISE_UTILS_H_
#define MYSQL_SEED_BITWISE_BITWISE_UTILS_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "utils/word_attrs.h"	/* word_t, WORD_BITS, stdint */

#ifndef WORD_BITS
#	error "compile-time constant 'WORD_BITS' unknown"
#endif /* ifndef WORD_BITS */


/* bitwise rotation */
inline uint8_t
uint8_rotate_left(const uint8_t value,
		  const unsigned int rotate)
{
	return (value << rotate) | (value >> (-rotate & 7));
}

inline uint8_t
uint8_rotate_right(const uint8_t value,
		   const unsigned int rotate)
{
	return (value >> rotate) | (value << (-rotate & 7));
}

inline uint16_t
uint16_rotate_left(const uint16_t value,
		   const unsigned int rotate)
{
	return (value << rotate) | (value >> (-rotate & 15));
}

inline uint16_t
uint16_rotate_right(const uint16_t value,
		    const unsigned int rotate)
{
	return (value >> rotate) | (value << (-rotate & 15));
}

inline uint32_t
uint32_rotate_left(const uint32_t value,
		   const unsigned int rotate)
{
	return (value << rotate) | (value >> (-rotate & 31));
}

inline uint32_t
uint32_rotate_right(const uint32_t value,
		    const unsigned int rotate)
{
	return (value >> rotate) | (value << (-rotate & 31));
}


inline uint64_t
uint64_rotate_left(const uint64_t value,
		   const unsigned int rotate)
{
	return (value << rotate) | (value >> (-rotate & 63));
}

inline uint64_t
uint64_rotate_right(const uint64_t value,
		    const unsigned int rotate)
{
	return (value >> rotate) | (value << (-rotate & 63));
}


inline word_t
word_rotate_left(const word_t word,
		 const unsigned int rotate)
{
	return (word << rotate) | (word >> (-rotate & (WORD_BITS - 1)));
}

inline word_t
word_rotate_right(const word_t word,
		  const unsigned int rotate)
{
	return (word >> rotate) | (word << (-rotate & (WORD_BITS - 1)));
}


#endif /* ifndef MYSQL_SEED_BITWISE_BITWISE_UTILS_H_ */
