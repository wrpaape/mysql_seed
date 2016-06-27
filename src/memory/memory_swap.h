#ifndef MEMORY_UTILS_MEMORY_SWAP_H_
#define MEMORY_UTILS_MEMORY_SWAP_H_

/* macros defined with leading underscores used for keeping consistency between
 * declarations and definitions with 'memory_swap.c', not needed for interface */

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include "memory/memory_swap_width.h" /* Width<WIDTH>, MEMORY_SWAP_WIDTH */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* swap memory for a particular byte width */
typedef void MemorySwap(void *const restrict,
			void *const restrict);

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *

 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* lookup for 'assign_memory_swap' (+1 for extra NULL slot) */
extern MemorySwap *const MEMORY_SWAP_MAP[WIDTH_MAX_SIZE + 1ul];

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS
 *
 *
 * FUNCTION-LIKE MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* swap variables (same type) */
#define VAR_SWAP(X, Y)				\
do {						\
	const __typeof__(X) __swap_tmp = X;	\
	X = Y;					\
	Y = __swap_tmp;				\
} while(0)

/* swap elements of 'ARRAY' at indices 'I', 'J' */
#define EL_SWAP(ARRAY, I, J)				\
do {							\
	const __typeof__(*ARRAY) __swap_tmp = ARRAY[I];	\
	ARRAY[I] = ARRAY[J];				\
	ARRAY[J] =  __swap_tmp;				\
} while(0)

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * FUNCTION-LIKE MACROS
 *
 *
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* memory swap arbitrary byte size, 'width' */
inline void memory_swap_width(void *const restrict x,
			      void *const restrict y,
			      const size_t width)
{
	Width1 buffer[width];
	memcpy(&buffer[0l], x,		 width);
	memcpy(x,	    y,		 width);
	memcpy(y,	    &buffer[0l], width);
}

/* same as 'memory_swap_width' except 'buffer' is provided by caller, not
 * allocated on stack */
inline void memory_swap_buffer(void *const restrict x,
			       void *const restrict y,
			       void *const restrict buffer,
			       const size_t width)
{
	memcpy(buffer, x,      width);
	memcpy(x,      y,      width);
	memcpy(y,      buffer, width);
}

inline MemorySwap *assign_memory_swap(const size_t width)
{
	return (width > WIDTH_MAX_SIZE) ? NULL : MEMORY_SWAP_MAP[width];
}

/* define memory_swap<WIDTH> functions for WIDTH = 1 .. WIDTH_MAX_SIZE */
inline void memory_swap0(void *const restrict x,
			 void *const restrict y)
{
}

inline void memory_swap1(void *const restrict x,
			 void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 1);
}

inline void memory_swap2(void *const restrict x,
			 void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 2);
}

inline void memory_swap3(void *const restrict x,
			 void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 3);
}

inline void memory_swap4(void *const restrict x,
			 void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 4);
}

inline void memory_swap5(void *const restrict x,
			 void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 5);
}

inline void memory_swap6(void *const restrict x,
			 void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 6);
}

inline void memory_swap7(void *const restrict x,
			 void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 7);
}

inline void memory_swap8(void *const restrict x,
			 void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 8);
}

inline void memory_swap9(void *const restrict x,
			 void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 9);
}

inline void memory_swap10(void *const restrict x,
			  void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 10);
}

inline void memory_swap11(void *const restrict x,
			  void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 11);
}

inline void memory_swap12(void *const restrict x,
			  void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 12);
}

inline void memory_swap13(void *const restrict x,
			  void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 13);
}

inline void memory_swap14(void *const restrict x,
			  void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 14);
}

inline void memory_swap15(void *const restrict x,
			  void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 15);
}

inline void memory_swap16(void *const restrict x,
			  void *const restrict y)
{
	MEMORY_SWAP_WIDTH(x, y, 16);
}

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS
 *
 *
 * HELPER FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER FUNCTIONS */


#endif /* ifndef MEMORY_UTILS_MEMORY_SWAP_H_ */
