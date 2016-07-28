#include "memory/memory_utils.h"

extern inline void *
memory_offset(const void *const restrict pointer,
	      const ptrdiff_t offset);

extern inline void
free_nullify(void *restrict *const restrict alloc);

void
free_nullify_cleanup(void *arg)
{
	void *restrict *const restrict alloc
	= (void *restrict *const restrict) arg;

	free(*alloc);
	*alloc = NULL;
}
