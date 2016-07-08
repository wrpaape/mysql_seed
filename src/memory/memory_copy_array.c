#include "memory/memory_copy_array.h"

extern inline MemoryCopyArray *assign_memory_copy_array(const size_t width);

/* define lookup for 'assign_memory_copy_array' */
MemoryCopyArray *const MEMORY_COPY_ARRAY_MAP[WIDTH_MAX_SIZE + 1ul] = {
	&memory_copy_array0,
	&memory_copy_array1,  &memory_copy_array2,  &memory_copy_array3,
	&memory_copy_array4,  &memory_copy_array5,  &memory_copy_array6,
	&memory_copy_array7,  &memory_copy_array8,  &memory_copy_array9,
	&memory_copy_array10, &memory_copy_array11, &memory_copy_array12,
	&memory_copy_array13, &memory_copy_array14, &memory_copy_array15,
	&memory_copy_array16
};

/* declare all memory_copy_array<WIDTH> functions extern */
extern inline void memory_copy_array0(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void memory_copy_array1(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void memory_copy_array2(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void memory_copy_array3(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void memory_copy_array4(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void memory_copy_array5(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void memory_copy_array6(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void memory_copy_array7(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void memory_copy_array8(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void memory_copy_array9(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void memory_copy_array10(void *restrict x,
				       const void *restrict y,
				       const size_t length);

extern inline void memory_copy_array11(void *restrict x,
				       const void *restrict y,
				       const size_t length);

extern inline void memory_copy_array12(void *restrict x,
				       const void *restrict y,
				       const size_t length);

extern inline void memory_copy_array13(void *restrict x,
				       const void *restrict y,
				       const size_t length);

extern inline void memory_copy_array14(void *restrict x,
				       const void *restrict y,
				       const size_t length);

extern inline void memory_copy_array15(void *restrict x,
				       const void *restrict y,
				       const size_t length);

extern inline void memory_copy_array16(void *restrict x,
				       const void *restrict y,
				       const size_t length);

/* memory_copy_array arbitrary byte size, 'width' */
extern inline void memory_copy_array_width(void *restrict x,
					   const void *restrict y,
					   const size_t length,
					   const size_t width);
