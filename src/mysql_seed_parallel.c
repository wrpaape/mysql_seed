#include "mysql_seed_parallel.h"

const SeedMutex seed_lock_prototype = SEED_LOCK_INITIALIZER;

extern inline void
seed_mutex_init(SeedMutex *const restrict lock);

extern inline bool
seed_mutex_lock(SeedMutex *const lock,
		char *const *restrict message_ptr);

extern inline bool
seed_mutex_unlock(SeedMutex *const lock,
		  char *const *restrict message_ptr);
