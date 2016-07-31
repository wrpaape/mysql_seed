#ifndef MYSQL_SEED_GENERATE_COLUMN_TIMESTAMP_H_
#define MYSQL_SEED_GENERATE_COLUMN_TIMESTAMP_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/generator.h" /* Column, string/thread/time utils */

/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define SIZE_TIMESTAMP_STRING 20lu

/* struct declarations, typedefs
 *─────────────────────────────────────────────────────────────────────────── */
struct TimestampBuffer {
	char bytes[SIZE_TIMESTAMP_STRING];
};

inline void
timestamp_string_init(const struct Timestamp *const restrict timestamp,
		      char *restrict string)
{
	unsigned int rem;

	/* "YYYY-" */
	rem = timestamp->year;

	*string = (char) DIGIT_TO_ASCII(rem / 1000u);
	rem %= 1000u;

	++string;

	*string = (char) DIGIT_TO_ASCII(rem / 100u);
	rem %= 100u;

	++string;

	*string = (char) DIGIT_TO_ASCII(rem / 10u);
	rem %= 10u;

	++string;

	*string = (char) DIGIT_TO_ASCII(rem);

	++string;

	*string = '-';

	++string;

	/* "MM-" */
	rem = timestamp->month;

	*string = (char) DIGIT_TO_ASCII(rem / 10u);
	rem %= 10u;

	++string;

	*string = (char) DIGIT_TO_ASCII(rem);

	++string;

	*string = '-';

	++string;

	/* "DD " */
	rem = timestamp->day;

	*string = (char) DIGIT_TO_ASCII(rem / 10u);
	rem %= 10u;

	++string;

	*string = (char) DIGIT_TO_ASCII(rem);

	++string;

	*string = ' ';

	++string;

	/* "HH:" */
	rem = timestamp->hours;

	*string = (char) DIGIT_TO_ASCII(rem / 10u);
	rem %= 10u;

	++string;

	*string = (char) DIGIT_TO_ASCII(rem);

	++string;

	*string = ':';

	++string;

	/* "MM:" */
	rem = timestamp->minutes;

	*string = (char) DIGIT_TO_ASCII(rem / 10u);
	rem %= 10u;

	++string;

	*string = (char) DIGIT_TO_ASCII(rem);

	++string;

	*string = ':';

	++string;

	/* "SS\0" */
	rem = timestamp->seconds;

	*string = (char) DIGIT_TO_ASCII(rem / 10u);
	rem %= 10u;

	++string;

	*string = (char) DIGIT_TO_ASCII(rem);

	++string;

	*string = '\0';
}

/* worker thread entry point */
void
build_column_timestamp_fixed(void *arg);

#endif /* ifndef MYSQL_SEED_GENERATE_COLUMN_TIMESTAMP_H_ */
