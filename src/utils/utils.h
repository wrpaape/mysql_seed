#ifndef MYSQL_SEED_UTILS_UTILS_H_
#define MYSQL_SEED_UTILS_UTILS_H_

/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <stdlib.h>	/* exit */
#include <stddef.h>	/* ptrdiff_t */
#include <stdio.h>	/* printf, fprintf */
#include <errno.h>	/* errno */
#include <string.h>	/* strerror */
#include <limits.h>	/* CHAR_BIT */

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */


/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define BIT_SIZE(TYPE) (sizeof(TYPE) * ((size_t) CHAR_BIT))

#define EXIT_ON_FAILURE(FORMAT, ...)					\
do {									\
	fprintf(stderr,							\
		"\n\e[31m\e[5mERROR:\e[25m\t\e[4m" FORMAT "\e[24m\n\n"	\
		"errno: %s\n\n"						\
		"file:  %s\n\n"						\
		"func:  %s\n\n"						\
		"line:  %d\e[0m\n",					\
		##__VA_ARGS__,						\
		strerror(errno), __FILE__, __func__, __LINE__);		\
	exit(EXIT_FAILURE);						\
} while (0)


#define MACRO_EXPAND_ARGS(MACRO, ...) MACRO(__VA_ARGS__)


/* returns 'THIS' or 'THAT' according to the predicate 'THIS CMP THAT',
 * where 'CMP' is a binary relational operator */
#define THIS_OR_THAT(THIS, THAT, CMP) (((THIS) CMP (THAT)) ? (THIS) : (THAT))

/* returns minimum of 'X' and 'Y' */
#define MIN(X, Y) THIS_OR_THAT(X, Y, <)

/* returns maximum of 'X' and 'Y' */
#define MAX(X, Y) THIS_OR_THAT(X, Y, >)


/* print elements of 'ARRAY' */
#define PRINT_ARRAY(ARRAY, LENGTH, FORMAT)		\
do {							\
	printf(#ARRAY ": {\n" FORMAT, ARRAY[0l]);	\
	for (ptrdiff_t i = 1; i < LENGTH; ++i)		\
		printf(", " FORMAT, ARRAY[i]);		\
	puts("\n}");					\
} while (0)

/* FUNCTION-LIKE MACROS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */


/* log₂(num) when num > 0 and num ≡ 0 (mod 2) */
inline unsigned long log_base_two_p2(const unsigned long num)
{
	return __builtin_ctzl(num);
}

/* exits if num == 0 */
inline unsigned long handle_log_base_two_p2(const unsigned long num)
{
	if (num == 0lu)
		EXIT_ON_FAILURE("'0' is not a power of two, log₂(0) undefined");

	return log_base_two_p2(num);
}

/* floor( log₂(num) ) when num > 0 */
inline unsigned long log_base_two(const unsigned long num)
{
	return BIT_SIZE(unsigned long) - 1lu - __builtin_clzl(num);
}

/* exits if num == 0 */
inline unsigned long handle_log_base_two(const unsigned long num)
{
	if (num == 0lu)
		EXIT_ON_FAILURE("log₂(0) undefined");

	return log_base_two(num);
}


/* defined results for 0 < num < LONG_MAX */
inline unsigned long next_pow_two_ib(const unsigned long num)
{
	return 1lu << (BIT_SIZE(unsigned long) - __builtin_clzl(num));
}

/* checks lower boundary */
inline unsigned long next_pow_two_lb(const unsigned long num)
{
	return (num > 0lu) ? next_pow_two_ib(num) : 1lu;
}

/* checks upper boundary */
inline unsigned long next_pow_two_ub(const unsigned long num)
{
	return (num < LONG_MAX) ? next_pow_two_ib(num) : SIZE_MAX;
}

/* checks both boundaries */
inline unsigned long next_pow_two(const unsigned long num)
{
	return (num > 0lu) ? next_pow_two_ub(num) : 1lu;
}

/* checks both boundaries, exits on integer overflow */
inline unsigned long handle_next_pow_two(const unsigned long num)
{
	if (num < LONG_MAX)
		return next_pow_two_lb(num);

	EXIT_ON_FAILURE("integer overflow, next_pow_two(%zu) > LONG_MAX "
			"(%zu)", num, LONG_MAX);
}


/* defined results for 1 < num <= LONG_MAX */
inline unsigned long round_pow_two_ib(const unsigned long num)
{
	return next_pow_two_ib(num - 1lu);
}

/* checks lower boundary */
inline unsigned long round_pow_two_lb(const unsigned long num)
{
	return (num > 1lu) ? round_pow_two_ib(num) : 1lu;
}

/* checks upper boundary */
inline unsigned long round_pow_two_ub(const unsigned long num)
{
	return (num > LONG_MAX) ? SIZE_MAX : round_pow_two_ib(num);
}

/* checks both boundaries */
inline unsigned long round_pow_two(const unsigned long num)
{
	return (num > 1lu) ? round_pow_two_ub(num) : 1lu;
}

/* checks both boundaries, exits on integer overflow */
inline unsigned long handle_round_pow_two(const unsigned long num)
{
	if (num > LONG_MAX)
		EXIT_ON_FAILURE("integer overflow, next_pow_two(%zu) > "
				"LONG_MAX (%zu)", num, LONG_MAX);

	return round_pow_two_lb(num);
}

#endif /* ifndef MYSQL_SEED_UTILS_UTILS_H_ */
