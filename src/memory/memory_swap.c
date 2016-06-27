#include "memory/memory_swap.h"

extern inline MemorySwap *assign_memory_swap(const size_t width);

/* define lookup for 'assign_memory_swap' */
MemorySwap *const MEMORY_SWAP_MAP[WIDTH_MAX_SIZE + 1ul] = {
	&memory_swap0,
	&memory_swap1,  &memory_swap2,  &memory_swap3,  &memory_swap4,
	&memory_swap5,  &memory_swap6,  &memory_swap7,  &memory_swap8,
	&memory_swap9,  &memory_swap10, &memory_swap11, &memory_swap12,
	&memory_swap13, &memory_swap14, &memory_swap15, &memory_swap16,
};

extern inline void memory_swap_width(void *const restrict x,
				     void *const restrict y,
				     const size_t width);

extern inline void memory_swap_buffer(void *const restrict x,
				      void *const restrict y,
				      void *const restrict buffer,
				      const size_t width);

/* declare all memory_swap<WIDTH> functions extern */
extern inline void memory_swap0(void *const restrict x,
				void *const restrict y);

extern inline void memory_swap1(void *const restrict x,
				void *const restrict y);

extern inline void memory_swap2(void *const restrict x,
				void *const restrict y);

extern inline void memory_swap3(void *const restrict x,
				void *const restrict y);

extern inline void memory_swap4(void *const restrict x,
				void *const restrict y);

extern inline void memory_swap5(void *const restrict x,
				void *const restrict y);

extern inline void memory_swap6(void *const restrict x,
				void *const restrict y);

extern inline void memory_swap7(void *const restrict x,
				void *const restrict y);

extern inline void memory_swap8(void *const restrict x,
				void *const restrict y);

extern inline void memory_swap9(void *const restrict x,
				void *const restrict y);

extern inline void memory_swap10(void *const restrict x,
				 void *const restrict y);

extern inline void memory_swap11(void *const restrict x,
				 void *const restrict y);

extern inline void memory_swap12(void *const restrict x,
				 void *const restrict y);

extern inline void memory_swap13(void *const restrict x,
				 void *const restrict y);

extern inline void memory_swap14(void *const restrict x,
				 void *const restrict y);

extern inline void memory_swap15(void *const restrict x,
				 void *const restrict y);

extern inline void memory_swap16(void *const restrict x,
				 void *const restrict y);
