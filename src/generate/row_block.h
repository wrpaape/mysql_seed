#ifndef MYSQL_SEED_GENERATE_ROW_BLOCK_H_
#define MYSQL_SEED_GENERATE_ROW_BLOCK_H_

/* extern dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "generate/generator.h"	/* RowBlock, thread utils */

inline char *
put_row_span_cell(char *restrict ptr,
		  char *const restrict *restrict cell)
{
}

inline char *
put_row_block_row(char *restrict ptr,
		  struct Rowspan *restrict from,
		  const struct Rowspan *const restrict until)
{
	do {
		ptr = put_string(ptr,
				 &from->cell);
		++from;
	} while (from < until);
}

inline void
set_row_block_row(char *restrict ptr,
		  struct Rowspan *restrict from,
		  const struct Rowspan *const restrict until)
{
}

void
build_row_block(void *arg);




#endif /* ifndef MYSQL_SEED_GENERATE_ROW_BLOCK_H_ */
