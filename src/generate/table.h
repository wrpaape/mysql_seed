#ifndef MYSQL_SEED_GENERATE_TABLE_H_
#define MYSQL_SEED_GENERATE_TABLE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/row_block.h" /* generator.h, string/thread utils */

/* set table->file.contents.length to total file size and return count_joins */
inline unsigned int
table_size_contents(struct Table *const restrict table)
{
	const struct TblSpec *const restrict tbl_spec = table->spec;

	const struct ColSpec *restrict from	   = tbl_spec->col_specs.from;
	const struct ColSpec *const restrict until = tbl_spec->col_specs.until;

	size_t size_contents = TABLE_HEADER_BASE_SIZE
			     + table->file.path.length
			     + tbl_spec->name.length
			     + table->parent->spec->name.length
			     + table->total.length
			     + from->name.length;

	unsigned int count_joins = 0u;

	while (1) {
		++from;

		if (from == until)
			break;

		if (from->name.bytes == NULL)
			++count_joins;
		else
			size_contents += (1l + from->name.length);
	}

	/* no FIELD_DELIMs for join columns */
	table->file.contents.length = size_contents
				    - (count_joins * tbl_spec->row_count);

	return count_joins;
}

inline unsigned int
table_size_contents_no_header(struct Table *const restrict table)
{
	const struct TblSpec *const restrict tbl_spec = table->spec;

	const struct ColSpec *restrict from	   = tbl_spec->col_specs.from;
	const struct ColSpec *const restrict until = tbl_spec->col_specs.until;

	unsigned int count_joins = 0u;

	do {
		if (from->name.bytes == NULL)
			++count_joins;

		++from;
	} while (from < until);

	/* no FIELD_DELIMs for join columns */
	table->file.contents.length = table->total.length
				    - (  (count_joins * tbl_spec->row_count)
				       + 1lu);	/* no initial \n */

	return count_joins;
}

inline char *
table_put_header(char *restrict ptr,
		 const struct Table *const restrict table)
{
	PUT_TABLE_HEADER_1(ptr);

	ptr = put_string_size(ptr,
			      &table->file.path.buffer[0],
			      table->file.path.length);

	PUT_TABLE_HEADER_2(ptr);

	ptr = put_string_size(ptr,
			      table->spec->name.bytes,
			      table->spec->name.length);

	PUT_TABLE_HEADER_3(ptr);

	ptr = put_string_size(ptr,
			      table->parent->spec->name.bytes,
			      table->parent->spec->name.length);

	PUT_TABLE_HEADER_4(ptr);


	const struct ColSpec *const restrict until
	= table->spec->col_specs.until;

	const struct ColSpec *restrict from = table->spec->col_specs.from;

	ptr = put_string_size(ptr,
			      from->name.bytes,
			      from->name.length);

	while (1) {
		++from;

		if (from == until)
			break;

		if (from->name.bytes != NULL) {
			PUT_FIELD_DELIM(ptr);

			ptr = put_string_size(ptr,
					      from->name.bytes,
					      from->name.length);
		}
	}

	PUT_TABLE_HEADER_5(ptr);

	return ptr;
}

/* thread worker entry
 *─────────────────────────────────────────────────────────────────────────── */
void
build_table_init(void *arg);

void
build_table_init_no_header(void *arg);

void
build_table_write(void *arg);

#endif /* ifndef MYSQL_SEED_GENERATE_TABLE_H_ */
