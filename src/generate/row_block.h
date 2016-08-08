#ifndef MYSQL_SEED_GENERATE_ROW_BLOCK_H_
#define MYSQL_SEED_GENERATE_ROW_BLOCK_H_

/* extern dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "generate/generator.h"	/* RowBlock, thread utils */

inline char *
put_rowspan_cell(char *restrict ptr,
		 char *restrict *const restrict cell_ptr)
{
	char *restrict cell;

	for (cell = *cell_ptr; *cell != '\0'; ++cell) {
		*ptr = *cell;
		++ptr;
	}

	*cell_ptr = cell + 1l; /* skip NULL separator */

	return ptr;
}

inline char *
put_row_block_row(char *restrict ptr,
		  struct Rowspan *restrict from,
		  const struct Rowspan *const restrict until)
{
	*ptr = '\n';
	ptr  = put_rowspan_cell(ptr + 1l,
				&from->cell);
	++from;

	while (from < until) {
		*ptr = FIELD_DELIM;
		ptr  = put_rowspan_cell(ptr + 1l,
					&from->cell);
		++from;
	}

	return ptr;
}

inline void
copy_row_block_row(char *restrict ptr,
		   struct Rowspan *restrict from,
		   const struct Rowspan *const restrict until)
{
	const struct Rowspan *const restrict last = until - 1l;

	*ptr = '\n';

	while (from < last) {
		ptr  = put_string(ptr + 1l,
				  from->cell);
		*ptr = FIELD_DELIM;

		++from;
	}

	copy_string(ptr + 1l,
		    last->cell);
}

void
build_row_block(void *arg);




#endif /* ifndef MYSQL_SEED_GENERATE_ROW_BLOCK_H_ */
