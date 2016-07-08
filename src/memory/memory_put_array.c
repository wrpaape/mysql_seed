#include "memory/memory_put_array.h"

extern inline MemoryPutArray *assign_memory_put_array(const size_t width);

/* define lookup for 'assign_memory_put_array' (zero-width maps to NULL) */
MemoryPutArray *const MEMORY_PUT_ARRAY_MAP[WIDTH_MAX_SIZE + 1ul] = {
	&memory_put_array0,
	&memory_put_array1,  &memory_put_array2,  &memory_put_array3,
	&memory_put_array4,  &memory_put_array5,  &memory_put_array6,
	&memory_put_array7,  &memory_put_array8,  &memory_put_array9,
	&memory_put_array10, &memory_put_array11, &memory_put_array12,
	&memory_put_array13, &memory_put_array14, &memory_put_array15,
	&memory_put_array16
};

/* declare all memory_put_array<WIDTH> functions extern */
extern inline void *memory_put_array0(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void *memory_put_array1(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void *memory_put_array2(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void *memory_put_array3(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void *memory_put_array4(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void *memory_put_array5(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void *memory_put_array6(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void *memory_put_array7(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void *memory_put_array8(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void *memory_put_array9(void *restrict x,
				      const void *restrict y,
				      const size_t length);

extern inline void *memory_put_array10(void *restrict x,
				       const void *restrict y,
				       const size_t length);

extern inline void *memory_put_array11(void *restrict x,
				       const void *restrict y,
				       const size_t length);

extern inline void *memory_put_array12(void *restrict x,
				       const void *restrict y,
				       const size_t length);

extern inline void *memory_put_array13(void *restrict x,
				       const void *restrict y,
				       const size_t length);

extern inline void *memory_put_array14(void *restrict x,
				       const void *restrict y,
				       const size_t length);

extern inline void *memory_put_array15(void *restrict x,
				       const void *restrict y,
				       const size_t length);

extern inline void *memory_put_array16(void *restrict x,
				       const void *restrict y,
				       const size_t length);

/* memory put_array arbitrary byte size, 'width' */
extern inline void *memory_put_array_width(void *restrict x,
					   const void *restrict y,
					   const size_t length,
					   const size_t width);
