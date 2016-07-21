
inline void memory_copy_array1(void *restrict x,
          const void *restrict y,
          const size_t length)
{
 if (length == 0lu)
  return;



 const size_t length_words = ((length) >> 3);
 const size_t rem_size = ((length) & 7lu);

 void *const restrict end_ptr = (void *const restrict) (((word_t *const restrict) x) + (length_words));
 while (1) {

	 *((word_t *restrict) x) = *((const word_t *restrict) y);

	 x = (void *restrict) (((word_t *restrict) x) + 1l);

	 if (x == end_ptr)
		 switch (rem_size) {
		 case 0lu: return;
		 case 1lu:
			   *((Width1 *const restrict) x) = *((const Width1 *const restrict) (((const word_t *restrict) y) + 1l));
			   return;
		 case 2lu:
			   *((Width2 *const restrict) x) = *((const Width2 *const restrict) (((const word_t *restrict) y) + 1l));
			   return;
		 case 3lu:
			   *((Width3 *const restrict) x) = *((const Width3 *const restrict) (((const word_t *restrict) y) + 1l));
			   return;
		 case 4lu:
			   *((Width4 *const restrict) x) = *((const Width4 *const restrict) (((const word_t *restrict) y) + 1l));
			   return;
		 case 5lu:
			   *((Width5 *const restrict) x) = *((const Width5 *const restrict) (((const word_t *restrict) y) + 1l));
			   return;
		 case 6lu:
			   *((Width6 *const restrict) x) = *((const Width6 *const restrict) (((const word_t *restrict) y) + 1l));
			   return;
		 default:
			   *((Width7 *const restrict) x) = *((const Width7 *const restrict) (((const word_t *restrict) y) + 1l));
			  return;
	 }
	 y = (void *restrict) (((word_t *restrict) y) + 1l);
	}

}


