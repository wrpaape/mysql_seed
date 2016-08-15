#ifndef MYSQL_SEED_TIME_TIME_STRING_H_
#define MYSQL_SEED_TIME_TIME_STRING_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "time/time_utils.h"		/* Timestamp, time utils */
#include "string/string_utils.h"	/* string utils */

/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define SIZE_TIMESTAMP_STRING 20lu
#define SIZE_DATETIME_STRING  20lu

/* struct declarations, typedefs
 *─────────────────────────────────────────────────────────────────────────── */
struct TimestampBuffer {
	char bytes[SIZE_TIMESTAMP_STRING];
};

struct DatetimeBuffer {
	char bytes[SIZE_DATETIME_STRING];
};

/* function-like macros
 *─────────────────────────────────────────────────────────────────────────── */
#define PUT_TIMESTAMP_STRING(PTR, STRING)				\
({*((struct TimestampBuffer *restrict) PTR)				\
= *((const struct TimestampBuffer *const restrict) STRING);		\
PTR = (__typeof__(PTR)) (((struct TimestampBuffer *restrict) PTR) + 1l);})

#define SET_TIMESTAMP_STRING(PTR, STRING)				\
  *((struct TimestampBuffer *restrict) PTR)				\
= *((const struct TimestampBuffer *const restrict) STRING)

#define PUT_DATETIME_STRING(PTR, STRING)				\
({*((struct DatetimeBuffer *restrict) PTR)				\
= *((const struct DatetimeBuffer *const restrict) STRING);		\
PTR = (__typeof__(PTR)) (((struct DatetimeBuffer *restrict) PTR) + 1l);})


inline void
timestamp_string_init(char *restrict string,
		      const struct Timestamp *const restrict timestamp)
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

	/* "-MM-" */
	switch (timestamp->month) {
	case 12u: PUT_STRING_WIDTH(string, "-12-", 4); break;
	case 11u: PUT_STRING_WIDTH(string, "-11-", 4); break;
	case 10u: PUT_STRING_WIDTH(string, "-10-", 4); break;
	case  9u: PUT_STRING_WIDTH(string, "-09-", 4); break;
	case  8u: PUT_STRING_WIDTH(string, "-08-", 4); break;
	case  7u: PUT_STRING_WIDTH(string, "-07-", 4); break;
	case  6u: PUT_STRING_WIDTH(string, "-06-", 4); break;
	case  5u: PUT_STRING_WIDTH(string, "-05-", 4); break;
	case  4u: PUT_STRING_WIDTH(string, "-04-", 4); break;
	case  3u: PUT_STRING_WIDTH(string, "-03-", 4); break;
	case  2u: PUT_STRING_WIDTH(string, "-02-", 4); break;
	default:  PUT_STRING_WIDTH(string, "-01-", 4);
	}

	/* "DD " */
	switch (timestamp->day) {
	case 31u: PUT_STRING_WIDTH(string, "31 ", 3); break;
	case 30u: PUT_STRING_WIDTH(string, "30 ", 3); break;
	case 29u: PUT_STRING_WIDTH(string, "29 ", 3); break;
	case 28u: PUT_STRING_WIDTH(string, "28 ", 3); break;
	case 27u: PUT_STRING_WIDTH(string, "27 ", 3); break;
	case 26u: PUT_STRING_WIDTH(string, "26 ", 3); break;
	case 25u: PUT_STRING_WIDTH(string, "25 ", 3); break;
	case 24u: PUT_STRING_WIDTH(string, "24 ", 3); break;
	case 23u: PUT_STRING_WIDTH(string, "23 ", 3); break;
	case 22u: PUT_STRING_WIDTH(string, "22 ", 3); break;
	case 21u: PUT_STRING_WIDTH(string, "21 ", 3); break;
	case 20u: PUT_STRING_WIDTH(string, "20 ", 3); break;
	case 19u: PUT_STRING_WIDTH(string, "19 ", 3); break;
	case 18u: PUT_STRING_WIDTH(string, "18 ", 3); break;
	case 17u: PUT_STRING_WIDTH(string, "17 ", 3); break;
	case 16u: PUT_STRING_WIDTH(string, "16 ", 3); break;
	case 15u: PUT_STRING_WIDTH(string, "15 ", 3); break;
	case 14u: PUT_STRING_WIDTH(string, "14 ", 3); break;
	case 13u: PUT_STRING_WIDTH(string, "13 ", 3); break;
	case 12u: PUT_STRING_WIDTH(string, "12 ", 3); break;
	case 11u: PUT_STRING_WIDTH(string, "11 ", 3); break;
	case 10u: PUT_STRING_WIDTH(string, "10 ", 3); break;
	case  9u: PUT_STRING_WIDTH(string, "09 ", 3); break;
	case  8u: PUT_STRING_WIDTH(string, "08 ", 3); break;
	case  7u: PUT_STRING_WIDTH(string, "07 ", 3); break;
	case  6u: PUT_STRING_WIDTH(string, "06 ", 3); break;
	case  3u: PUT_STRING_WIDTH(string, "03 ", 3); break;
	case  2u: PUT_STRING_WIDTH(string, "02 ", 3); break;
	default:  PUT_STRING_WIDTH(string, "01 ", 3);
	}

	/* "HH:" */
	switch (timestamp->hour) {
	case 23u: PUT_STRING_WIDTH(string, "23:", 3); break;
	case 22u: PUT_STRING_WIDTH(string, "22:", 3); break;
	case 21u: PUT_STRING_WIDTH(string, "21:", 3); break;
	case 20u: PUT_STRING_WIDTH(string, "20:", 3); break;
	case 19u: PUT_STRING_WIDTH(string, "19:", 3); break;
	case 18u: PUT_STRING_WIDTH(string, "18:", 3); break;
	case 17u: PUT_STRING_WIDTH(string, "17:", 3); break;
	case 16u: PUT_STRING_WIDTH(string, "16:", 3); break;
	case 15u: PUT_STRING_WIDTH(string, "15:", 3); break;
	case 14u: PUT_STRING_WIDTH(string, "14:", 3); break;
	case 13u: PUT_STRING_WIDTH(string, "13:", 3); break;
	case 12u: PUT_STRING_WIDTH(string, "12:", 3); break;
	case 11u: PUT_STRING_WIDTH(string, "11:", 3); break;
	case 10u: PUT_STRING_WIDTH(string, "10:", 3); break;
	case  9u: PUT_STRING_WIDTH(string, "09:", 3); break;
	case  8u: PUT_STRING_WIDTH(string, "08:", 3); break;
	case  7u: PUT_STRING_WIDTH(string, "07:", 3); break;
	case  6u: PUT_STRING_WIDTH(string, "06:", 3); break;
	case  5u: PUT_STRING_WIDTH(string, "05:", 3); break;
	case  4u: PUT_STRING_WIDTH(string, "04:", 3); break;
	case  3u: PUT_STRING_WIDTH(string, "03:", 3); break;
	case  2u: PUT_STRING_WIDTH(string, "02:", 3); break;
	case  1u: PUT_STRING_WIDTH(string, "01:", 3); break;
	default:  PUT_STRING_WIDTH(string, "00:", 3);
	}

	/* "MM:" */
	switch (timestamp->minute) {
	case 59u: PUT_STRING_WIDTH(string, "59:", 3); break;
	case 58u: PUT_STRING_WIDTH(string, "58:", 3); break;
	case 57u: PUT_STRING_WIDTH(string, "57:", 3); break;
	case 56u: PUT_STRING_WIDTH(string, "56:", 3); break;
	case 55u: PUT_STRING_WIDTH(string, "55:", 3); break;
	case 54u: PUT_STRING_WIDTH(string, "54:", 3); break;
	case 53u: PUT_STRING_WIDTH(string, "53:", 3); break;
	case 52u: PUT_STRING_WIDTH(string, "52:", 3); break;
	case 51u: PUT_STRING_WIDTH(string, "51:", 3); break;
	case 50u: PUT_STRING_WIDTH(string, "50:", 3); break;
	case 49u: PUT_STRING_WIDTH(string, "49:", 3); break;
	case 48u: PUT_STRING_WIDTH(string, "48:", 3); break;
	case 47u: PUT_STRING_WIDTH(string, "47:", 3); break;
	case 46u: PUT_STRING_WIDTH(string, "46:", 3); break;
	case 45u: PUT_STRING_WIDTH(string, "45:", 3); break;
	case 44u: PUT_STRING_WIDTH(string, "44:", 3); break;
	case 43u: PUT_STRING_WIDTH(string, "43:", 3); break;
	case 42u: PUT_STRING_WIDTH(string, "42:", 3); break;
	case 41u: PUT_STRING_WIDTH(string, "41:", 3); break;
	case 40u: PUT_STRING_WIDTH(string, "40:", 3); break;
	case 39u: PUT_STRING_WIDTH(string, "39:", 3); break;
	case 38u: PUT_STRING_WIDTH(string, "38:", 3); break;
	case 37u: PUT_STRING_WIDTH(string, "37:", 3); break;
	case 36u: PUT_STRING_WIDTH(string, "36:", 3); break;
	case 35u: PUT_STRING_WIDTH(string, "35:", 3); break;
	case 34u: PUT_STRING_WIDTH(string, "34:", 3); break;
	case 33u: PUT_STRING_WIDTH(string, "33:", 3); break;
	case 32u: PUT_STRING_WIDTH(string, "32:", 3); break;
	case 31u: PUT_STRING_WIDTH(string, "31:", 3); break;
	case 30u: PUT_STRING_WIDTH(string, "30:", 3); break;
	case 29u: PUT_STRING_WIDTH(string, "29:", 3); break;
	case 28u: PUT_STRING_WIDTH(string, "28:", 3); break;
	case 27u: PUT_STRING_WIDTH(string, "27:", 3); break;
	case 26u: PUT_STRING_WIDTH(string, "26:", 3); break;
	case 25u: PUT_STRING_WIDTH(string, "25:", 3); break;
	case 24u: PUT_STRING_WIDTH(string, "24:", 3); break;
	case 23u: PUT_STRING_WIDTH(string, "23:", 3); break;
	case 22u: PUT_STRING_WIDTH(string, "22:", 3); break;
	case 21u: PUT_STRING_WIDTH(string, "21:", 3); break;
	case 20u: PUT_STRING_WIDTH(string, "20:", 3); break;
	case 19u: PUT_STRING_WIDTH(string, "19:", 3); break;
	case 18u: PUT_STRING_WIDTH(string, "18:", 3); break;
	case 17u: PUT_STRING_WIDTH(string, "17:", 3); break;
	case 16u: PUT_STRING_WIDTH(string, "16:", 3); break;
	case 15u: PUT_STRING_WIDTH(string, "15:", 3); break;
	case 14u: PUT_STRING_WIDTH(string, "14:", 3); break;
	case 13u: PUT_STRING_WIDTH(string, "13:", 3); break;
	case 12u: PUT_STRING_WIDTH(string, "12:", 3); break;
	case 11u: PUT_STRING_WIDTH(string, "11:", 3); break;
	case 10u: PUT_STRING_WIDTH(string, "10:", 3); break;
	case  9u: PUT_STRING_WIDTH(string, "09:", 3); break;
	case  8u: PUT_STRING_WIDTH(string, "08:", 3); break;
	case  7u: PUT_STRING_WIDTH(string, "07:", 3); break;
	case  6u: PUT_STRING_WIDTH(string, "06:", 3); break;
	case  5u: PUT_STRING_WIDTH(string, "05:", 3); break;
	case  4u: PUT_STRING_WIDTH(string, "04:", 3); break;
	case  3u: PUT_STRING_WIDTH(string, "03:", 3); break;
	case  2u: PUT_STRING_WIDTH(string, "02:", 3); break;
	case  1u: PUT_STRING_WIDTH(string, "01:", 3); break;
	default:  PUT_STRING_WIDTH(string, "00:", 3);
	}

	/* "SS\0" */
	switch (timestamp->second) {
	case 59u: SET_STRING_WIDTH(string, "59", 3); return;
	case 58u: SET_STRING_WIDTH(string, "58", 3); return;
	case 57u: SET_STRING_WIDTH(string, "57", 3); return;
	case 56u: SET_STRING_WIDTH(string, "56", 3); return;
	case 55u: SET_STRING_WIDTH(string, "55", 3); return;
	case 54u: SET_STRING_WIDTH(string, "54", 3); return;
	case 53u: SET_STRING_WIDTH(string, "53", 3); return;
	case 52u: SET_STRING_WIDTH(string, "52", 3); return;
	case 51u: SET_STRING_WIDTH(string, "51", 3); return;
	case 50u: SET_STRING_WIDTH(string, "50", 3); return;
	case 49u: SET_STRING_WIDTH(string, "49", 3); return;
	case 48u: SET_STRING_WIDTH(string, "48", 3); return;
	case 47u: SET_STRING_WIDTH(string, "47", 3); return;
	case 46u: SET_STRING_WIDTH(string, "46", 3); return;
	case 45u: SET_STRING_WIDTH(string, "45", 3); return;
	case 44u: SET_STRING_WIDTH(string, "44", 3); return;
	case 43u: SET_STRING_WIDTH(string, "43", 3); return;
	case 42u: SET_STRING_WIDTH(string, "42", 3); return;
	case 41u: SET_STRING_WIDTH(string, "41", 3); return;
	case 40u: SET_STRING_WIDTH(string, "40", 3); return;
	case 39u: SET_STRING_WIDTH(string, "39", 3); return;
	case 38u: SET_STRING_WIDTH(string, "38", 3); return;
	case 37u: SET_STRING_WIDTH(string, "37", 3); return;
	case 36u: SET_STRING_WIDTH(string, "36", 3); return;
	case 35u: SET_STRING_WIDTH(string, "35", 3); return;
	case 34u: SET_STRING_WIDTH(string, "34", 3); return;
	case 33u: SET_STRING_WIDTH(string, "33", 3); return;
	case 32u: SET_STRING_WIDTH(string, "32", 3); return;
	case 31u: SET_STRING_WIDTH(string, "31", 3); return;
	case 30u: SET_STRING_WIDTH(string, "30", 3); return;
	case 29u: SET_STRING_WIDTH(string, "29", 3); return;
	case 28u: SET_STRING_WIDTH(string, "28", 3); return;
	case 27u: SET_STRING_WIDTH(string, "27", 3); return;
	case 26u: SET_STRING_WIDTH(string, "26", 3); return;
	case 25u: SET_STRING_WIDTH(string, "25", 3); return;
	case 24u: SET_STRING_WIDTH(string, "24", 3); return;
	case 23u: SET_STRING_WIDTH(string, "23", 3); return;
	case 22u: SET_STRING_WIDTH(string, "22", 3); return;
	case 21u: SET_STRING_WIDTH(string, "21", 3); return;
	case 20u: SET_STRING_WIDTH(string, "20", 3); return;
	case 19u: SET_STRING_WIDTH(string, "19", 3); return;
	case 18u: SET_STRING_WIDTH(string, "18", 3); return;
	case 17u: SET_STRING_WIDTH(string, "17", 3); return;
	case 16u: SET_STRING_WIDTH(string, "16", 3); return;
	case 15u: SET_STRING_WIDTH(string, "15", 3); return;
	case 14u: SET_STRING_WIDTH(string, "14", 3); return;
	case 13u: SET_STRING_WIDTH(string, "13", 3); return;
	case 12u: SET_STRING_WIDTH(string, "12", 3); return;
	case 11u: SET_STRING_WIDTH(string, "11", 3); return;
	case 10u: SET_STRING_WIDTH(string, "10", 3); return;
	case  9u: SET_STRING_WIDTH(string, "09", 3); return;
	case  8u: SET_STRING_WIDTH(string, "08", 3); return;
	case  7u: SET_STRING_WIDTH(string, "07", 3); return;
	case  6u: SET_STRING_WIDTH(string, "06", 3); return;
	case  5u: SET_STRING_WIDTH(string, "05", 3); return;
	case  4u: SET_STRING_WIDTH(string, "04", 3); return;
	case  3u: SET_STRING_WIDTH(string, "03", 3); return;
	case  2u: SET_STRING_WIDTH(string, "02", 3); return;
	case  1u: SET_STRING_WIDTH(string, "01", 3); return;
	default:  SET_STRING_WIDTH(string, "00", 3);
	}
}

#define datetime_string_init(STRING, TIMESTAMP)				\
timestamp_string_init(STRING, TIMESTAMP)

inline void
timestamp_string_increment_overflow(char *const restrict last)
{
	/* "YYYY-MM-DD HH:MM:S8" */
	/* min:	1970-01-01 00:00:01 */
	/* max: 2038-01-19 03:14:07 */

	char *restrict ptr = last - 1l;

	if (*ptr != '0') {
		*last = '8';
		return;
	}

	ptr -= 2l;

	if (*ptr != '4') {
		*last = '8';
		return;
	}

	--ptr;

	if (*ptr != '1') {
		*last = '8';
		return;
	}

	ptr -= 2l;

	if (*ptr != '3') {
		*last = '8';
		return;
	}

	--ptr;

	if (*ptr != '0') {
		*last = '8';
		return;
	}

	ptr -= 2l;

	if (*ptr != '9') {
		*last = '8';
		return;
	}

	--ptr;

	if (*ptr != '1') {
		*last = '8';
		return;
	}

	ptr -= 2l;

	if (*ptr != '1') {
		*last = '8';
		return;
	}

	--ptr;

	if (*ptr != '0') {
		*last = '8';
		return;
	}

	ptr -= 2l;

	if (*ptr != '8') {
		*last = '8';
		return;
	}

	--ptr;

	if (*ptr != '3') {
		*last = '8';
		return;
	}

	--ptr;

	if (*ptr != '0') {
		*last = '8';
		return;
	}

	--ptr;

	if (*ptr == '2')
		SET_TIMESTAMP_STRING(ptr, "1970-01-01 00:00:01");
	else
		*last = '8';
}

inline void
timestamp_string_increment(char *restrict ptr)
{
	/* "YYYY-MM-DD HH:MM:Sx" */
	switch (*ptr) {
	case '0': *ptr = '1'; return;
	case '1': *ptr = '2'; return;
	case '2': *ptr = '3'; return;
	case '3': *ptr = '4'; return;
	case '4': *ptr = '5'; return;
	case '5': *ptr = '6'; return;
	case '6': *ptr = '7'; return;
	case '7': timestamp_string_increment_overflow(ptr); return;
	case '8': *ptr = '9'; return;
	default: --ptr;
	}

	/* "YYYY-MM-DD HH:MM:x0" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "10", 2); return;
	case '1': SET_STRING_WIDTH(ptr, "20", 2); return;
	case '2': SET_STRING_WIDTH(ptr, "30", 2); return;
	case '3': SET_STRING_WIDTH(ptr, "40", 2); return;
	case '4': SET_STRING_WIDTH(ptr, "50", 2); return;
	default:
		ptr -= 2l;
	}

	/* "YYYY-MM-DD HH:Mx:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "1:00", 4); return;
	case '1': SET_STRING_WIDTH(ptr, "2:00", 4); return;
	case '2': SET_STRING_WIDTH(ptr, "3:00", 4); return;
	case '3': SET_STRING_WIDTH(ptr, "4:00", 4); return;
	case '4': SET_STRING_WIDTH(ptr, "5:00", 4); return;
	case '5': SET_STRING_WIDTH(ptr, "6:00", 4); return;
	case '6': SET_STRING_WIDTH(ptr, "7:00", 4); return;
	case '7': SET_STRING_WIDTH(ptr, "8:00", 4); return;
	case '8': SET_STRING_WIDTH(ptr, "9:00", 4); return;
	default:
		--ptr;
	}

	/* "YYYY-MM-DD HH:x0:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "10:00", 5); return;
	case '1': SET_STRING_WIDTH(ptr, "20:00", 5); return;
	case '2': SET_STRING_WIDTH(ptr, "30:00", 5); return;
	case '3': SET_STRING_WIDTH(ptr, "40:00", 5); return;
	case '4': SET_STRING_WIDTH(ptr, "50:00", 5); return;
	default:
		ptr -= 2l;
	}

	/* "YYYY-MM-DD Hx:00:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "1:00:00", 7); return;
	case '1': SET_STRING_WIDTH(ptr, "2:00:00", 7); return;
	case '2': SET_STRING_WIDTH(ptr, "3:00:00", 7); return;
	case '3':
		if (ptr[-1] == '2') {
			SET_STRING_WIDTH(&ptr[-1], "00:00:00", 8);
			ptr -= 3l;
			break;
		}
		  SET_STRING_WIDTH(ptr, "4:00:00", 7); return;
	case '4': SET_STRING_WIDTH(ptr, "5:00:00", 7); return;
	case '5': SET_STRING_WIDTH(ptr, "6:00:00", 7); return;
	case '6': SET_STRING_WIDTH(ptr, "7:00:00", 7); return;
	case '7': SET_STRING_WIDTH(ptr, "8:00:00", 7); return;
	case '8': SET_STRING_WIDTH(ptr, "9:00:00", 7); return;
	default:
		--ptr;

		if (*ptr == '0')
			SET_STRING_WIDTH(ptr, "10:00:00", 8);
		else
			SET_STRING_WIDTH(ptr, "20:00:00", 8);

		return;
	}

	/* "YYYY-MM-Dx 00:00:00" */
	switch (*ptr) {
	default: /* 'X0' and ill-formed days, guaranteed to set valid, return */
		if (ptr[-1] != '3') {
			*ptr = '1';

		} else if (ptr[-4] == '1') {
			if (ptr[-3] == '2')
				*ptr = '1';
			else
				SET_STRING_WIDTH(&ptr[-3],  "2-01", 4);

		} else {
			switch (ptr[-3]) {
			case '4':
				SET_STRING_WIDTH(&ptr[-3],  "5-01", 4);
				return;
			case '6':
				SET_STRING_WIDTH(&ptr[-3],  "7-01", 4);
				return;
			case '9':
				SET_STRING_WIDTH(&ptr[-4], "10-01", 5);
				return;
			default:
				*ptr = '1';
			}
		}
		return;


	case '1':
		if (ptr[-1] != '3') {
			*ptr = '2';
			return;

		} else if (ptr[-4] == '1') {	/* new year */
			ptr -= 6l;
			break;
		}

		ptr -= 3l;

		switch (*ptr) {
		case '0': SET_STRING_WIDTH(ptr, "1-01", 4); return;
		case '1': SET_STRING_WIDTH(ptr, "2-01", 4); return;
		case '3': SET_STRING_WIDTH(ptr, "4-01", 4); return;
		case '5': SET_STRING_WIDTH(ptr, "6-01", 4); return;
		case '7': SET_STRING_WIDTH(ptr, "8-01", 4); return;
		default:  SET_STRING_WIDTH(ptr, "9-01", 4); return;
		}


	case '2': *ptr = '3'; return;
	case '3': *ptr = '4'; return;
	case '4': *ptr = '5'; return;
	case '5': *ptr = '6'; return;
	case '6': *ptr = '7'; return;
	case '7': *ptr = '8'; return;


	case '8':
		if ((ptr[-4] == '1') || (ptr[-3] != '2') || (ptr[-1] != '2')) {
			++(ptr[-1]);
			*ptr = '0';

		} else {	/* 02-28 → check if leap year */

			const char *restrict year_ptr = ptr - 6l;
			unsigned int year = ASCII_TO_DIGIT(*year_ptr);
			--year_ptr;

			year += ASCII_TO_DIGIT(*year_ptr) * 10u;
			--year_ptr;

			year += ASCII_TO_DIGIT(*year_ptr) * 100u;
			--year_ptr;

			year += ASCII_TO_DIGIT(*year_ptr) * 1000u;

			if (is_leap_year(year))
				*ptr = '9';
			else
				SET_STRING_WIDTH(&ptr[-3], "3-01", 4);
		}
		return;


	case '9':
		if ((ptr[-4] == '1') || (ptr[-3] != '2') || (ptr[-1] != '2')) {
			++(ptr[-1]);
			*ptr = '0';

		} else {	/* 02-29 → 03-01 */
			SET_STRING_WIDTH(&ptr[-4], "03-01", 5);
		}
		return;
	}

	/* "YYYx-01-01 00:00:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "1-01-01", 7); return;
	case '1': SET_STRING_WIDTH(ptr, "2-01-01", 7); return;
	case '2': SET_STRING_WIDTH(ptr, "3-01-01", 7); return;
	case '3': SET_STRING_WIDTH(ptr, "4-01-01", 7); return;
	case '4': SET_STRING_WIDTH(ptr, "5-01-01", 7); return;
	case '5': SET_STRING_WIDTH(ptr, "6-01-01", 7); return;
	case '6': SET_STRING_WIDTH(ptr, "7-01-01", 7); return;
	case '7': SET_STRING_WIDTH(ptr, "8-01-01", 7); return;
	case '8': SET_STRING_WIDTH(ptr, "9-01-01", 7); return;
	default:
		--ptr;
	}

	/* "YYx0-01-01 00:00:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "10-01-01", 8); return;
	case '1': SET_STRING_WIDTH(ptr, "20-01-01", 8); return;
	case '2': SET_STRING_WIDTH(ptr, "30-01-01", 8); return;
	case '3': SET_STRING_WIDTH(ptr, "40-01-01", 8); return;
	case '4': SET_STRING_WIDTH(ptr, "50-01-01", 8); return;
	case '5': SET_STRING_WIDTH(ptr, "60-01-01", 8); return;
	case '6': SET_STRING_WIDTH(ptr, "70-01-01", 8); return;
	case '7': SET_STRING_WIDTH(ptr, "80-01-01", 8); return;
	case '8': SET_STRING_WIDTH(ptr, "90-01-01", 8); return;
	default:
		--ptr;
	}

	/* "Yx00-01-01 00:00:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "100-01-01", 9); return;
	case '1': SET_STRING_WIDTH(ptr, "200-01-01", 9); return;
	case '2': SET_STRING_WIDTH(ptr, "300-01-01", 9); return;
	case '3': SET_STRING_WIDTH(ptr, "400-01-01", 9); return;
	case '4': SET_STRING_WIDTH(ptr, "500-01-01", 9); return;
	case '5': SET_STRING_WIDTH(ptr, "600-01-01", 9); return;
	case '6': SET_STRING_WIDTH(ptr, "700-01-01", 9); return;
	case '7': SET_STRING_WIDTH(ptr, "800-01-01", 9); return;
	case '8': SET_STRING_WIDTH(ptr, "900-01-01", 9); return;
	default: /* must be Y2K if valid MySQL TIMESTAMP */
		  SET_STRING_WIDTH(&ptr[-1], "2000-01-01", 10);
	}
}


inline void
datetime_string_increment(char *restrict ptr)
{
	/* "YYYY-MM-DD HH:MM:Sx" */
	switch (*ptr) {
	case '0': *ptr = '1'; return;
	case '1': *ptr = '2'; return;
	case '2': *ptr = '3'; return;
	case '3': *ptr = '4'; return;
	case '4': *ptr = '5'; return;
	case '5': *ptr = '6'; return;
	case '6': *ptr = '7'; return;
	case '7': *ptr = '8'; return;
	case '8': *ptr = '9'; return;
	default: --ptr;
	}

	/* "YYYY-MM-DD HH:MM:x0" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "10", 2); return;
	case '1': SET_STRING_WIDTH(ptr, "20", 2); return;
	case '2': SET_STRING_WIDTH(ptr, "30", 2); return;
	case '3': SET_STRING_WIDTH(ptr, "40", 2); return;
	case '4': SET_STRING_WIDTH(ptr, "50", 2); return;
	default:
		ptr -= 2l;
	}

	/* "YYYY-MM-DD HH:Mx:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "1:00", 4); return;
	case '1': SET_STRING_WIDTH(ptr, "2:00", 4); return;
	case '2': SET_STRING_WIDTH(ptr, "3:00", 4); return;
	case '3': SET_STRING_WIDTH(ptr, "4:00", 4); return;
	case '4': SET_STRING_WIDTH(ptr, "5:00", 4); return;
	case '5': SET_STRING_WIDTH(ptr, "6:00", 4); return;
	case '6': SET_STRING_WIDTH(ptr, "7:00", 4); return;
	case '7': SET_STRING_WIDTH(ptr, "8:00", 4); return;
	case '8': SET_STRING_WIDTH(ptr, "9:00", 4); return;
	default:
		--ptr;
	}

	/* "YYYY-MM-DD HH:x0:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "10:00", 5); return;
	case '1': SET_STRING_WIDTH(ptr, "20:00", 5); return;
	case '2': SET_STRING_WIDTH(ptr, "30:00", 5); return;
	case '3': SET_STRING_WIDTH(ptr, "40:00", 5); return;
	case '4': SET_STRING_WIDTH(ptr, "50:00", 5); return;
	default:
		ptr -= 2l;
	}

	/* "YYYY-MM-DD Hx:00:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "1:00:00", 7); return;
	case '1': SET_STRING_WIDTH(ptr, "2:00:00", 7); return;
	case '2': SET_STRING_WIDTH(ptr, "3:00:00", 7); return;
	case '3':
		if (ptr[-1] == '2') {
			SET_STRING_WIDTH(&ptr[-1], "00:00:00", 8);
			ptr -= 3l;
			break;
		}
		  SET_STRING_WIDTH(ptr, "4:00:00", 7); return;
	case '4': SET_STRING_WIDTH(ptr, "5:00:00", 7); return;
	case '5': SET_STRING_WIDTH(ptr, "6:00:00", 7); return;
	case '6': SET_STRING_WIDTH(ptr, "7:00:00", 7); return;
	case '7': SET_STRING_WIDTH(ptr, "8:00:00", 7); return;
	case '8': SET_STRING_WIDTH(ptr, "9:00:00", 7); return;
	default:
		--ptr;

		if (*ptr == '0')
			SET_STRING_WIDTH(ptr, "10:00:00", 8);
		else
			SET_STRING_WIDTH(ptr, "20:00:00", 8);

		return;
	}

	/* "YYYY-MM-Dx 00:00:00" */
	switch (*ptr) {
	default: /* 'X0' and ill-formed days, guaranteed to set valid, return */
		if (ptr[-1] != '3') {
			*ptr = '1';

		} else if (ptr[-4] == '1') {
			if (ptr[-3] == '2')
				*ptr = '1';
			else
				SET_STRING_WIDTH(&ptr[-3],  "2-01", 4);

		} else {
			switch (ptr[-3]) {
			case '4':
				SET_STRING_WIDTH(&ptr[-3],  "5-01", 4);
				return;
			case '6':
				SET_STRING_WIDTH(&ptr[-3],  "7-01", 4);
				return;
			case '9':
				SET_STRING_WIDTH(&ptr[-4], "10-01", 5);
				return;
			default:
				*ptr = '1';
			}
		}
		return;


	case '1':
		if (ptr[-1] != '3') {
			*ptr = '2';
			return;

		} else if (ptr[-4] == '1') {	/* new year */
			ptr -= 6l;
			break;
		}

		ptr -= 3l;

		switch (*ptr) {
		case '0': SET_STRING_WIDTH(ptr, "1-01", 4); return;
		case '1': SET_STRING_WIDTH(ptr, "2-01", 4); return;
		case '3': SET_STRING_WIDTH(ptr, "4-01", 4); return;
		case '5': SET_STRING_WIDTH(ptr, "6-01", 4); return;
		case '7': SET_STRING_WIDTH(ptr, "8-01", 4); return;
		default:  SET_STRING_WIDTH(ptr, "9-01", 4); return;
		}


	case '2': *ptr = '3'; return;
	case '3': *ptr = '4'; return;
	case '4': *ptr = '5'; return;
	case '5': *ptr = '6'; return;
	case '6': *ptr = '7'; return;
	case '7': *ptr = '8'; return;


	case '8':
		if ((ptr[-4] == '1') || (ptr[-3] != '2') || (ptr[-1] != '2')) {
			++(ptr[-1]);
			*ptr = '0';

		} else {	/* 02-28 → check if leap year */

			const char *restrict year_ptr = ptr - 6l;
			unsigned int year = ASCII_TO_DIGIT(*year_ptr);
			--year_ptr;

			year += ASCII_TO_DIGIT(*year_ptr) * 10u;
			--year_ptr;

			year += ASCII_TO_DIGIT(*year_ptr) * 100u;
			--year_ptr;

			year += ASCII_TO_DIGIT(*year_ptr) * 1000u;

			if (is_leap_year(year))
				*ptr = '9';
			else
				SET_STRING_WIDTH(&ptr[-3], "3-01", 4);
		}
		return;


	case '9':
		if ((ptr[-4] == '1') || (ptr[-3] != '2') || (ptr[-1] != '2')) {
			++(ptr[-1]);
			*ptr = '0';

		} else {	/* 02-29 → 03-01 */
			SET_STRING_WIDTH(&ptr[-4], "03-01", 5);
		}
		return;
	}

	/* "YYYx-01-01 00:00:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "1-01-01", 7); return;
	case '1': SET_STRING_WIDTH(ptr, "2-01-01", 7); return;
	case '2': SET_STRING_WIDTH(ptr, "3-01-01", 7); return;
	case '3': SET_STRING_WIDTH(ptr, "4-01-01", 7); return;
	case '4': SET_STRING_WIDTH(ptr, "5-01-01", 7); return;
	case '5': SET_STRING_WIDTH(ptr, "6-01-01", 7); return;
	case '6': SET_STRING_WIDTH(ptr, "7-01-01", 7); return;
	case '7': SET_STRING_WIDTH(ptr, "8-01-01", 7); return;
	case '8': SET_STRING_WIDTH(ptr, "9-01-01", 7); return;
	default:
		--ptr;
	}

	/* "YYx0-01-01 00:00:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "10-01-01", 8); return;
	case '1': SET_STRING_WIDTH(ptr, "20-01-01", 8); return;
	case '2': SET_STRING_WIDTH(ptr, "30-01-01", 8); return;
	case '3': SET_STRING_WIDTH(ptr, "40-01-01", 8); return;
	case '4': SET_STRING_WIDTH(ptr, "50-01-01", 8); return;
	case '5': SET_STRING_WIDTH(ptr, "60-01-01", 8); return;
	case '6': SET_STRING_WIDTH(ptr, "70-01-01", 8); return;
	case '7': SET_STRING_WIDTH(ptr, "80-01-01", 8); return;
	case '8': SET_STRING_WIDTH(ptr, "90-01-01", 8); return;
	default:
		--ptr;
	}

	/* "Yx00-01-01 00:00:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "100-01-01", 9); return;
	case '1': SET_STRING_WIDTH(ptr, "200-01-01", 9); return;
	case '2': SET_STRING_WIDTH(ptr, "300-01-01", 9); return;
	case '3': SET_STRING_WIDTH(ptr, "400-01-01", 9); return;
	case '4': SET_STRING_WIDTH(ptr, "500-01-01", 9); return;
	case '5': SET_STRING_WIDTH(ptr, "600-01-01", 9); return;
	case '6': SET_STRING_WIDTH(ptr, "700-01-01", 9); return;
	case '7': SET_STRING_WIDTH(ptr, "800-01-01", 9); return;
	case '8': SET_STRING_WIDTH(ptr, "900-01-01", 9); return;
	default:
		--ptr;
	}

	/* "x000-01-01 00:00:00" */
	switch (*ptr) {
	case '0': SET_STRING_WIDTH(ptr, "1000-01-01", 10); return;
	case '1': SET_STRING_WIDTH(ptr, "2000-01-01", 10); return;
	case '2': SET_STRING_WIDTH(ptr, "3000-01-01", 10); return;
	case '3': SET_STRING_WIDTH(ptr, "4000-01-01", 10); return;
	case '4': SET_STRING_WIDTH(ptr, "5000-01-01", 10); return;
	case '5': SET_STRING_WIDTH(ptr, "6000-01-01", 10); return;
	case '6': SET_STRING_WIDTH(ptr, "7000-01-01", 10); return;
	case '7': SET_STRING_WIDTH(ptr, "8000-01-01", 10); return;
	case '8': SET_STRING_WIDTH(ptr, "9000-01-01", 10); return;
	default:  SET_STRING_WIDTH(ptr, "1000-01-01", 10); /* MySQL min date */
	}
}

#endif /* ifndef MYSQL_SEED_TIME_TIME_STRING_H_ */
