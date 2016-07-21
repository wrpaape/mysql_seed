#ifndef MEMORY_UTILS_MEMORY_COPY_ARRAY_H_
#define MEMORY_UTILS_MEMORY_COPY_ARRAY_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "memory/memory_set_width.h"	/* Width<WIDTH>, MEMORY_SET_WIDTH */
#include "memory/word_rem_utils.h"	/* PUT_WORDS_LOOP, WORD_REM_SWITCH */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* copy_array memory for a particular byte width */
typedef void MemoryCopyArray(void *restrict,
			     const void *restrict,
			     const size_t);

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* lookup for 'assign_memory_copy_array' */
extern MemoryCopyArray *const MEMORY_COPY_ARRAY_MAP[WIDTH_MAX_SIZE + 1ul];

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS
 *
 *
 * FUNCTION-LIKE MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define memory_copy(X, Y, SIZE) memory_copy_array1(X, Y, SIZE)

/* word remainder case handlers */
#define HANDLE_COPY_REM0(X, Y)  return
#define HANDLE_COPY_REM1(X, Y)  MEMORY_SET_WIDTH(X, Y, 1);  return
#define HANDLE_COPY_REM2(X, Y)  MEMORY_SET_WIDTH(X, Y, 2);  return
#define HANDLE_COPY_REM3(X, Y)  MEMORY_SET_WIDTH(X, Y, 3);  return
#define HANDLE_COPY_REM4(X, Y)  MEMORY_SET_WIDTH(X, Y, 4);  return
#define HANDLE_COPY_REM5(X, Y)  MEMORY_SET_WIDTH(X, Y, 5);  return
#define HANDLE_COPY_REM6(X, Y)  MEMORY_SET_WIDTH(X, Y, 6);  return
#define HANDLE_COPY_REM7(X, Y)  MEMORY_SET_WIDTH(X, Y, 7);  return
#define HANDLE_COPY_REM8(X, Y)  MEMORY_SET_WIDTH(X, Y, 8);  return
#define HANDLE_COPY_REM9(X, Y)  MEMORY_SET_WIDTH(X, Y, 9);  return
#define HANDLE_COPY_REM10(X, Y) MEMORY_SET_WIDTH(X, Y, 10); return
#define HANDLE_COPY_REM11(X, Y) MEMORY_SET_WIDTH(X, Y, 11); return
#define HANDLE_COPY_REM12(X, Y) MEMORY_SET_WIDTH(X, Y, 12); return
#define HANDLE_COPY_REM13(X, Y) MEMORY_SET_WIDTH(X, Y, 13); return
#define HANDLE_COPY_REM14(X, Y) MEMORY_SET_WIDTH(X, Y, 14); return
#define HANDLE_COPY_REM15(X, Y) MEMORY_SET_WIDTH(X, Y, 15); return
#define HANDLE_COPY_REM16(X, Y) MEMORY_SET_WIDTH(X, Y, 16); return

#define COPY_WORDS_BODY(X, Y, LENGTH)					\
PUT_WORDS_LOOP_LENGTH(X, Y, LENGTH,					\
		      return;)

#define COPY_REM_RETURN(X, Y, REM_SIZE)					\
WORD_REM_SWITCH(REM_SIZE, HANDLE_COPY_REM, X, Y)

#define COPY_WORDS_AND_REM_BODY(X, Y, LENGTH_WORDS, REM_SIZE)		\
PUT_WORDS_LOOP_LENGTH(X, Y, LENGTH_WORDS,				\
		      WORD_REM_SWITCH(REM_SIZE, HANDLE_COPY_REM,	\
				      X, (((const word_t *restrict) Y) + 1l)))

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

inline MemoryCopyArray *assign_memory_copy_array(const size_t width)
{
	return (width > WIDTH_MAX_SIZE)
	     ? NULL
	     : MEMORY_COPY_ARRAY_MAP[width];
}

/* define memory_copy_array<WIDTH> functions for WIDTH = 0 .. WIDTH_MAX_SIZE */
inline void memory_copy_array0(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
}
inline void memory_copy_array1(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
#if (WORD_SIZE == 1lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t length_words = DIV_WORD_SIZE(length);
	const size_t rem_size     = REM_WORD_SIZE(length);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array2(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
#if (WORD_SIZE == 2lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length << 1;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array3(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
#if (WORD_SIZE == 3lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 3lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array4(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
#if (WORD_SIZE == 4lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length << 2;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array5(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
#if (WORD_SIZE == 5lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 5lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array6(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
#if (WORD_SIZE == 6lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 6lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array7(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
#if (WORD_SIZE == 7lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 7lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array8(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
#if (WORD_SIZE == 8lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length << 3;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array9(void *restrict x,
			       const void *restrict y,
			       const size_t length)
{
#if (WORD_SIZE == 9lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 9lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array10(void *restrict x,
				const void *restrict y,
				const size_t length)
{
#if (WORD_SIZE == 10lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 10lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array11(void *restrict x,
				const void *restrict y,
				const size_t length)
{
#if (WORD_SIZE == 11lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 11lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array12(void *restrict x,
				const void *restrict y,
				const size_t length)
{
#if (WORD_SIZE == 12lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 12lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array13(void *restrict x,
				const void *restrict y,
				const size_t length)
{
#if (WORD_SIZE == 13lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 13lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array14(void *restrict x,
				const void *restrict y,
				const size_t length)
{
#if (WORD_SIZE == 14lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 14lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array15(void *restrict x,
				const void *restrict y,
				const size_t length)
{
#if (WORD_SIZE == 15lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length * 15lu;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

inline void memory_copy_array16(void *restrict x,
				const void *restrict y,
				const size_t length)
{
#if (WORD_SIZE == 16lu)
	if (length == 0lu)
		return;
	COPY_WORDS_BODY(x, y, length)
#else
	const size_t array_size	  = length << 4;
	const size_t length_words = DIV_WORD_SIZE(array_size);
	const size_t rem_size     = REM_WORD_SIZE(array_size);
	if (length_words == 0lu)
		COPY_REM_RETURN(x, y, rem_size)
	COPY_WORDS_AND_REM_BODY(x, y, length_words, rem_size)
#endif
}

/* memory_copy_array arbitrary byte size, 'width' */
inline void memory_copy_array_width(void *restrict x,
				    const void *restrict y,
				    const size_t length,
				    const size_t width)
{
	memory_copy(x, y, length * width);
}
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS */

#endif /* ifndef MEMORY_UTILS_MEMORY_COPY_ARRAY_H_ */
