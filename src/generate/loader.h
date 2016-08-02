#ifndef MYSQL_SEED_GENERATE_LOADER_H_
#define MYSQL_SEED_GENERATE_LOADER_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/generator.h"	/* Specs, string, file utils */


inline size_t
loader_estimate_size(const unsigned int tbl_count,
		     const unsigned int col_count)
{
	return LOADER_HEADER_BASE_SIZE_MAX
	     + (tbl_count * ((TABLE_FILEPATH_SIZE_MAX * 2lu)
			     + LOADER_CREATE_TABLE_BASE_SIZE
			     + LOADER_LOAD_TABLE_BASE_SIZE
			     + TBL_NAME_NN_SIZE_MAX))
	     + ((col_count - tbl_count) * (WIDTH_MAX_SIZE + 3lu));
}

inline char *
loader_put_header(char *restrict ptr,
		  const struct Database *const restrict database)
{
	PUT_LOADER_HEADER_1(ptr);

	ptr = put_string_size(ptr,
			      &database->loader.path.buffer[0],
			      database->loader.path.length);

	PUT_LOADER_HEADER_2(ptr);

	ptr = put_string_size(ptr,
			      database->spec->name.bytes,
			      database->spec->name.length);

	PUT_LOADER_HEADER_3(ptr);

	const struct Table *const restrict until = database->tables.until;
	struct Table *restrict from		 = database->tables.from;

	while (1) {
		table_file_init(&from->file,
				&from->spec->name,
				&database->dirpath);

		ptr = put_string_size(ptr,
				      &from->file.path.buffer[0],
				      from->file.path.length);

		++from;

		if (from == until)
			break;

		PUT_LOADER_TABLE_LI(ptr);
	}

	PUT_LOADER_HEADER_4(ptr);

	ptr = put_string_size(ptr,
			      database->spec->name.bytes,
			      database->spec->name.length);

	PUT_LOADER_HEADER_5(ptr);

	ptr = put_string_size(ptr,
			      database->spec->name.bytes,
			      database->spec->name.length);

	PUT_LOADER_HEADER_6(ptr);

	return ptr;
}

inline char *
loader_put_body(char *restrict ptr,
		const struct Database *const restrict database)
{
	const struct Table *restrict from	 = database->tables.from;
	const struct Table *const restrict until = database->tables.until;

	const struct ColSpec *restrict col_spec_from;
	const struct ColSpec *restrict col_spec_until;


	do {
		PUT_LOADER_CREATE_TABLE_1(ptr);

		ptr = put_string_size(ptr,
				      from->spec->name.bytes,
				      from->spec->name.length);

		PUT_LOADER_CREATE_TABLE_2(ptr);

		col_spec_from  = from->spec->col_specs.from;
		col_spec_until = from->spec->col_specs.until;

		while (1) {
			ptr = put_string_size(ptr,
					      col_spec_from->name.bytes,
					      col_spec_from->name.length);
			*ptr = ' ';
			++ptr;

			ptr = put_label(ptr,
					&col_spec_from->type);

			++col_spec_from;

			if (col_spec_from == col_spec_until)
				break;

			PUT_LOADER_CREATE_TABLE_FIELD_DELIM(ptr);
		}


		PUT_LOADER_LOAD_TABLE_1(ptr);

		ptr = put_string_size(ptr,
				      &from->file.path.buffer[0],
				      from->file.path.length);

		PUT_LOADER_LOAD_TABLE_2(ptr);

		ptr = put_string_size(ptr,
				      from->spec->name.bytes,
				      from->spec->name.length);

		PUT_LOADER_LOAD_TABLE_3(ptr);

		++from;
	} while (from < until);

	return ptr;
}

/* worker task entry point
 * ────────────────────────────────────────────────────────────────────────── */
void
build_loader(void *arg);



#endif /* ifndef MYSQL_SEED_GENERATE_LOADER_H_ */
