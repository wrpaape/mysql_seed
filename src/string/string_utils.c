#include "string/string_utils.h"

#ifdef DIGIT_COUNT_MAX
const size_t ten_pow_map[DIGIT_COUNT_MAX] = {
	[ 0] = 1lu,
	[ 1] = 10lu,
	[ 2] = 100lu,
	[ 3] = 1000lu,
	[ 4] = 10000lu
#	if (DIGIT_COUNT_MAX > 5u)
		      ,
	[ 5] = 100000lu,
	[ 6] = 1000000lu,
	[ 7] = 10000000lu,
	[ 8] = 100000000lu,
	[ 9] = 1000000000lu
#		if (DIGIT_COUNT_MAX > 10u)
			   ,
	[10] = 10000000000lu,
	[11] = 100000000000lu,
	[12] = 1000000000000lu,
	[13] = 10000000000000lu,
	[14] = 100000000000000lu,
	[15] = 1000000000000000lu,
	[16] = 10000000000000000lu,
	[17] = 100000000000000000lu,
	[18] = 1000000000000000000lu,
	[19] = 10000000000000000000lu
#		endif /* if (DIGIT_COUNT_MAX > 10u) */
#	endif /* if (DIGIT_COUNT_MAX > 5u) */
};

extern inline unsigned int
digit_count(size_t n);

extern inline void
do_put_digits(char *restrict buffer,
	      size_t n);
#endif	/* ifdef (DIGIT_COUNT_MAX) */


#ifdef POINTER_ID_LENGTH_MAX
const size_t ninety_five_pow_map[POINTER_ID_LENGTH_MAX] = {
	[0] = 1lu,
	[1] = 95lu
#	if (POINTER_ID_LENGTH_MAX > 2u)
		  ,
	[2] = 9025lu
#		if (POINTER_ID_LENGTH_MAX > 3u)
		    ,
	[3] = 857375lu,
	[4] = 81450625lu
#			if (POINTER_ID_LENGTH_MAX > 5u)
			,
	[5] = 7737809375lu,
	[6] = 735091890625lu,
	[7] = 69833729609375lu,
	[8] = 6634204312890625lu,
	[9] = 630249409724609375lu
#			endif /* if (POINTER_ID_LENGTH_MAX > 5u) */
#		endif /* if (POINTER_ID_LENGTH_MAX > 3u) */
#	endif /* if (POINTER_ID_LENGTH_MAX > 2u) */
};

extern inline unsigned int
pointer_id_length(const uintptr_t ptr_n);

extern inline void
#else
extern inline char *
#endif /* ifdef POINTER_ID_LENGTH_MAX */
do_put_pointer_id(char *restrict buffer,
		  uintptr_t ptr_n);

extern inline char *
put_digits(char *restrict buffer,
	   size_t n);

extern inline char *
put_digits_length(char *restrict buffer,
		  size_t n,
		  const size_t length);

extern inline char *
put_digits_until(char *restrict buffer,
		 const size_t n,
		 char *const restrict until_ptr);

extern inline char *
put_number(char *restrict buffer,
	   ssize_t n);

extern inline char *
put_number_length(char *restrict buffer,
		  ssize_t n,
		  unsigned int length);

extern inline char *
put_number_until(char *restrict buffer,
		 const ssize_t n,
		 char *const restrict until_ptr);

extern inline char *
put_pointer_id(char *restrict buffer,
	       void *const restrict pointer);

extern inline char *
put_pointer_id_length(char *restrict buffer,
		      void *const restrict pointer,
		      const unsigned int length);

extern inline char *
put_pointer_id_until(char *restrict buffer,
		     void *const restrict pointer,
		     char *const restrict until_ptr);

extern inline char *
put_string(char *restrict buffer,
	   const char *restrict string);

extern inline char *
put_string_length(char *restrict buffer,
		  const char *restrict string,
		  size_t length);

extern inline char *
put_string_until(char *restrict buffer,
		 const char *restrict string,
		 char *const restrict until_ptr);

extern inline bool
strings_equal(const char *restrict string1,
	      const char *restrict string2);

extern inline size_t
string_length(const char *const restrict string);

extern inline ssize_t
string_length_limit(const char *const restrict string,
		    ssize_t limit);

extern inline size_t
string_size(const char *const restrict string);

extern inline size_t
string_size_limit(const char *const restrict string,
		  size_t limit);
