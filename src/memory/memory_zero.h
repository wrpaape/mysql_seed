#ifndef MYSQL_SEED_MEMORY_MEMORY_ZERO_H_
#define MYSQL_SEED_MEMORY_MEMORY_ZERO_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "memory/word_rem_utils.h"	/* memory_utils, WORD_REM_SWITCH */

/* global constants
 * ────────────────────────────────────────────────────────────────────────── */
extern const Width1  width1_zero;
extern const Width2  width2_zero;
extern const Width3  width3_zero;
extern const Width4  width4_zero;
extern const Width5  width5_zero;
extern const Width6  width6_zero;
extern const Width7  width7_zero;
extern const Width8  width8_zero;
extern const Width9  width9_zero;
extern const Width10 width10_zero;
extern const Width11 width11_zero;
extern const Width12 width12_zero;
extern const Width13 width13_zero;
extern const Width14 width14_zero;
extern const Width15 width15_zero;
extern const Width16 width16_zero;

/* function-like macros
 * ────────────────────────────────────────────────────────────────────────── */
#define MEMORY_ZERO_WIDTH(PTR, WIDTH)					\
*((Width ## WIDTH *const restrict) PTR) = width ## WIDTH ## _zero;

/* word remainder case handlers */
#define HANDLE_ZERO_REM0(PTR)  return
#define HANDLE_ZERO_REM1(PTR)  MEMORY_ZERO_WIDTH(PTR, 1);  return
#define HANDLE_ZERO_REM2(PTR)  MEMORY_ZERO_WIDTH(PTR, 2);  return
#define HANDLE_ZERO_REM3(PTR)  MEMORY_ZERO_WIDTH(PTR, 3);  return
#define HANDLE_ZERO_REM4(PTR)  MEMORY_ZERO_WIDTH(PTR, 4);  return
#define HANDLE_ZERO_REM5(PTR)  MEMORY_ZERO_WIDTH(PTR, 5);  return
#define HANDLE_ZERO_REM6(PTR)  MEMORY_ZERO_WIDTH(PTR, 6);  return
#define HANDLE_ZERO_REM7(PTR)  MEMORY_ZERO_WIDTH(PTR, 7);  return
#define HANDLE_ZERO_REM8(PTR)  MEMORY_ZERO_WIDTH(PTR, 8);  return
#define HANDLE_ZERO_REM9(PTR)  MEMORY_ZERO_WIDTH(PTR, 9);  return
#define HANDLE_ZERO_REM10(PTR) MEMORY_ZERO_WIDTH(PTR, 10); return
#define HANDLE_ZERO_REM11(PTR) MEMORY_ZERO_WIDTH(PTR, 11); return
#define HANDLE_ZERO_REM12(PTR) MEMORY_ZERO_WIDTH(PTR, 12); return
#define HANDLE_ZERO_REM13(PTR) MEMORY_ZERO_WIDTH(PTR, 13); return
#define HANDLE_ZERO_REM14(PTR) MEMORY_ZERO_WIDTH(PTR, 14); return
#define HANDLE_ZERO_REM15(PTR) MEMORY_ZERO_WIDTH(PTR, 15); return
#define HANDLE_ZERO_REM16(PTR) MEMORY_ZERO_WIDTH(PTR, 16); return


inline void
memory_zero(void *const restrict ptr,
	    const size_t size)
{
	const size_t length_words = DIV_WORD_SIZE(size);
	const size_t rem_size     = REM_WORD_SIZE(size);

	word_t *restrict from =	(word_t *restrict) ptr;
	const word_t *const restrict until = from + length_words;

	while (from < until) {
		*from = 0;
		++from;
	}

	WORD_REM_SWITCH(rem_size,
			HANDLE_ZERO_REM,
			from)
}


#endif /* ifndef MYSQL_SEED_MEMORY_MEMORY_ZERO_H_ */
