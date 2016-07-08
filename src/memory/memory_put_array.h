#ifndef MYSQL_SEED_MEMORY_MEMORY_PUT_ARRAY_H_
#define MYSQL_SEED_MEMORY_MEMORY_PUT_ARRAY_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "memory/memory_put_width.h" /* Width<WIDTH>, MEMORY_PUT/GET_WIDTH */
#include "memory/word_rem_utils.h"   /* PUT_WORDS_LOOP, WORD_REM_SWITCH */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* put_array memory for a particular byte width */
typedef void *MemoryPutArray(void *restrict,
			     const void *restrict,
			     const size_t);

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* lookup for 'assign_memory_put_array' */
extern MemoryPutArray *const MEMORY_PUT_ARRAY_MAP[WIDTH_MAX_SIZE + 1ul];

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS
 *
 *
 * FUNCTION-LIKE MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define memory_put(X, Y, SIZE) memory_put_array1(X, Y, SIZE)

/* word remainder case handlers */
#define HANDLE_PUT_REM0(X, Y)  return X
#define HANDLE_PUT_REM1(X, Y)  MEMORY_PUT_WIDTH(X, Y, 1,  return)
#define HANDLE_PUT_REM2(X, Y)  MEMORY_PUT_WIDTH(X, Y, 2,  return)
#define HANDLE_PUT_REM3(X, Y)  MEMORY_PUT_WIDTH(X, Y, 3,  return)
#define HANDLE_PUT_REM4(X, Y)  MEMORY_PUT_WIDTH(X, Y, 4,  return)
#define HANDLE_PUT_REM5(X, Y)  MEMORY_PUT_WIDTH(X, Y, 5,  return)
#define HANDLE_PUT_REM6(X, Y)  MEMORY_PUT_WIDTH(X, Y, 6,  return)
#define HANDLE_PUT_REM7(X, Y)  MEMORY_PUT_WIDTH(X, Y, 7,  return)
#define HANDLE_PUT_REM8(X, Y)  MEMORY_PUT_WIDTH(X, Y, 8,  return)
#define HANDLE_PUT_REM9(X, Y)  MEMORY_PUT_WIDTH(X, Y, 9,  return)
#define HANDLE_PUT_REM10(X, Y) MEMORY_PUT_WIDTH(X, Y, 10, return)
#define HANDLE_PUT_REM11(X, Y) MEMORY_PUT_WIDTH(X, Y, 11, return)
#define HANDLE_PUT_REM12(X, Y) MEMORY_PUT_WIDTH(X, Y, 12, return)
#define HANDLE_PUT_REM13(X, Y) MEMORY_PUT_WIDTH(X, Y, 13, return)
#define HANDLE_PUT_REM14(X, Y) MEMORY_PUT_WIDTH(X, Y, 14, return)
#define HANDLE_PUT_REM15(X, Y) MEMORY_PUT_WIDTH(X, Y, 15, return)
#define HANDLE_PUT_REM16(X, Y) MEMORY_PUT_WIDTH(X, Y, 16, return)

#define PUT_WORDS_BODY(X, Y, LENGTH)					\
PUT_WORDS_LOOP_LENGTH(X, Y, LENGTH,					\
		      return X;)

#define PUT_WORDS_AND_REM_BODY(X, Y, LENGTH_WORDS, REM_SIZE)		\
PUT_WORDS_LOOP_LENGTH(X, Y, LENGTH_WORDS,				\
		      WORD_REM_SWITCH(REM_SIZE, HANDLE_PUT_REM, X, Y))

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * FUNCTION-LIKE MACROS
 *
 *
 * HELPER FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER FUNCTIONS
 *
 *
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */


inline MemoryPutArray *assign_memory_put_array(const size_t width)
{
	return (width > WIDTH_MAX_SIZE)
	     ? NULL
	     : MEMORY_PUT_ARRAY_MAP[width];
}

/* define memory_put_array<WIDTH> functions for WIDTH = 0 .. WIDTH_MAX_SIZE */
inline void *memory_put_array0(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
	return x;
}

inline void *memory_put_array1(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 1lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t length_words = DIV_WORD_SIZE(length);
	const size_t rem_size     = REM_WORD_SIZE(length);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array2(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 2lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length << 1;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array3(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 3lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 3lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array4(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 4lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length << 2;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array5(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 5lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 5lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array6(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 6lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 6lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array7(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 7lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 7lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array8(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 8lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length << 3;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array9(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 9lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 9lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array10(void *restrict x,
				const void *restrict y,
				const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 10lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 10lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array11(void *restrict x,
				const void *restrict y,
				const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 11lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 11lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array12(void *restrict x,
				const void *restrict y,
				const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 12lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 12lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array13(void *restrict x,
				const void *restrict y,
				const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 13lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 13lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array14(void *restrict x,
				const void *restrict y,
				const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 14lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 14lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array15(void *restrict x,
				const void *restrict y,
				const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 15lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 15lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void *memory_put_array16(void *restrict x,
				const void *restrict y,
				const size_t length)
{
	if (length == 0lu)
		return x;
#if (WORD_SIZE == 16lu)
	PUT_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length << 4;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	PUT_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

/* memory put_array arbitrary byte size, 'width' */
inline void *memory_put_array_width(void *restrict x,
				    const void *restrict y,
				    const size_t length,
				    const size_t width)
{
	return memory_put(x, y, length * width);
}

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS */

#endif /* ifndef MYSQL_SEED_MEMORY_MEMORY_PUT_ARRAY_H_ */
