#include "system/file_utils.h"

extern inline char *file_permissions_string_put(char *restrict buffer,
						const int mode);

extern inline void file_permissions_string(char *restrict buffer,
					   const int mode);

extern inline void fildes_write_all(const int fildes,
				    const char *restrict contents);

extern inline void filename_write_all(const char *restrict filename,
				      const char *restrict contents);
