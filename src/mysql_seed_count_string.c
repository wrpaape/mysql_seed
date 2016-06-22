#include "mysql_seed_count_string.h"



#define SIZE_1_9		18lu		/* (1 digit  + '\0') * 9 */
#define SIZE_10_99		270lu		/* (2 digits + '\0') * 90 */
#define SIZE_100_999		3600lu		/* (3 digits + '\0') * 900 */
#define SIZE_1000_9999		45000lu		/* (3 digits + '\0') * 9000 */
#define SIZE_10000_99999	540000lu	/* (4 digits + '\0') * 90000 */
#define SIZE_100000_999999	6300000lu	/* (5 digits + '\0') * 900000 */
#define SIZE_1000000_9999999	72000000lu	/* (6 digits + '\0') * 9000000 */

#define SIZE_1_99	(SIZE_1_9	+ SIZE_10_99)
#define SIZE_1_999	(SIZE_1_99	+ SIZE_100_999)
#define SIZE_1_9999	(SIZE_1_999	+ SIZE_1000_9999)
#define SIZE_1_99999	(SIZE_1_9999	+ SIZE_10000_99999)
#define SIZE_1_999999	(SIZE_1_99999	+ SIZE_100000_999999)
#define SIZE_1_9999999	(SIZE_1_999999	+ SIZE_1000000_9999999)

#define UPTO_MAX 99999999lu


size_t digits(const size_t upto)
{
	if (upto < 10lu)
		return upto * 2lu + sizeof(char *);

	if (upto < 100lu)
		return (((upto - 9lu) * 3lu) + 18lu +  sizeof(char *);
}

enum CountStringInitFlag
count_string_init(char *const *restrict *string_pointers,
		  char *const *restrict digits,
		  const size_t upto)
{
	if (upto > UPTO_MAX)
		return CSI_FAILURE_UPTO_MAX_EXCEEDED;

	/* room for string pointers + 1 (NULL terminator) */
	const size_t size_pointers = sizeof(char **) * (upto + 1lu);

	size_t size_digits;

	if (upto < 10lu)
		size_digits = (upto * 2lu);

	else if (upto < 100lu)
		size_digits = (upto * 3lu) + SIZE_1_99;


	else if (upto < 1000lu)
		size_digits = (upto * 4lu) + SIZE_1_999;

	else if (upto < 10000lu)
		size_digits = (upto * 5lu) + SIZE_1_9999;



	else if (upto < 100000lu)
		size_digits = (upto * 6lu) + SIZE_1_99999;

	else if (upto < 1000000lu)
		size_digits = (upto * 7lu) + SIZE_1_999999;

	else if (upto < 10000000lu)
		size_digits = (upto * 8lu) + SIZE_1_9999999;

	else
		size_digits = (upto * 9lu) + SIZE_1_99999999;


	if (upto < 10000lu) {

		if (upto < 100lu) {
			size_digits = (upto < 10lu)
				    ? (upto * 2lu)
				    : (upto * 3lu) + SIZE_1_99;

		} else {
			size_digits = (upto < 1000lu)
				    ? (upto * 4lu) + SIZE_1_999
				    : (upto * 5lu) + SIZE_1_9999;
		}
	} else {
		if (upto < 1000000lu) {
			size_digits = (upto < 100000lu)
				    ? (upto * 6lu) + SIZE_1_99999
				    : (upto * 7lu) + SIZE_1_999999;

		} else {
			size_digits = (upto < 10000000lu)
				    ? (upto * 8lu) + SIZE_1_9999999
				    : (upto * 9lu) + SIZE_1_99999999;
		}

	}


}
