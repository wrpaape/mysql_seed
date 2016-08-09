#include "bitwise/bitwise_utils.h"

/* bitwise rotation */
extern inline uint8_t
uint8_rotate_left(const uint8_t value,
		  const unsigned int rotate);
extern inline uint8_t
uint8_rotate_right(const uint8_t value,
		   const unsigned int rotate);
extern inline uint16_t
uint16_rotate_left(const uint16_t value,
		   const unsigned int rotate);
extern inline uint16_t
uint16_rotate_right(const uint16_t value,
		    const unsigned int rotate);
extern inline uint32_t
uint32_rotate_left(const uint32_t value,
		   const unsigned int rotate);
extern inline uint32_t
uint32_rotate_right(const uint32_t value,
		    const unsigned int rotate);
extern inline uint64_t
uint64_rotate_left(const uint64_t value,
		   const unsigned int rotate);
extern inline uint64_t
uint64_rotate_right(const uint64_t value,
		    const unsigned int rotate);
extern inline word_t
word_rotate_left(const word_t word,
		 const unsigned int rotate);
extern inline word_t
word_rotate_right(const word_t word,
		  const unsigned int rotate);
