#ifndef MYSQL_SEED_SYSTEM_FILE_UTILS_H_
#define MYSQL_SEED_SYSTEM_FILE_UTILS_H_

/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#ifdef WIN32
#	include <io.h>		/* _open, _write, _close */
#	include <direct.h>	/* _chdir */
#else
#	include <fcntl.h>	/* open */
#endif /* ifdef WIN32 */

#include <unistd.h>		     /* close, getcwd, STDOUT/IN/ERR_FILENO */
#include "utils/utils.h"	     /* FILE/stream API */
#include "system/system_utils.h"     /* sys headers, FAIL_SWITCH, misc macros */
#include "string/string_utils.h"     /* string_compare */
#include "utils/types/bool_status.h" /* BoolStatus */

/* EXTERNAL DEPENDENCIES ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */

/* CONSTANTS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* open 'oflag's (from <fcntl.h>)
 *
 * The flags specified for the 'oflag' argument are formed by or'ing the
 * following values:
 *
 *O_RDONLY        open for reading only
 *O_WRONLY        open for writing only
 *O_RDWR          open for reading and writing
 *O_NONBLOCK      do not block on open or for data to become available
 *O_APPEND        append on each write
 *O_CREAT         create file if it does not exist
 *O_TRUNC         truncate size to 0
 *O_EXCL          error if O_CREAT and the file exists
 *O_SHLOCK        atomically obtain a shared lock
 *O_EXLOCK        atomically obtain an exclusive lock
 *O_NOFOLLOW      do not follow symlinks
 *O_SYMLINK       allow open of symlinks
 *O_EVTONLY       descriptor requested for event notifications only
 *O_CLOEXEC       mark as close-on-exe */


/* chmod permission bitmasks (from <sys/stat.h>)
 *
 * A 'mode' is created from or'd permission bit masks:
 *
 * S_IRWXU 0000700    RWX mask for owner
 * S_IRUSR 0000400    R for owner
 * S_IWUSR 0000200    W for owner
 * S_IXUSR 0000100    X for owner
 *
 * S_IRWXG 0000070    RWX mask for group
 * S_IRGRP 0000040    R for group
 * S_IWGRP 0000020    W for group
 * S_IXGRP 0000010    X for group
 *
 * S_IRWXO 0000007    RWX mask for other
 * S_IROTH 0000004    R for other
 * S_IWOTH 0000002    W for other
 * S_IXOTH 0000001    X for other
 *
 * S_ISUID 0004000    set user id on execution
 * S_ISGID 0002000    set group id on execution
 * S_ISVTX 0001000    save swapped text even after use */


/* flags for the 'at' functions (from <fcntl.h>)
 *
 * AT_FDCWD	-2
 *
 * AT_EACCESS		0x0010	Use effective ids in access check
 * AT_SYMLINK_NOFOLLOW	0x0020	Act on the symlink itself not the target
 * AT_SYMLINK_FOLLOW	0x0040	Act on target of symlink
 * AT_REMOVEDIR		0x0080	Path refers to directory */

/* iovec struct for 'readv' (from <sys/types.h>)
 *
 * struct iovec {
 * 	char   *iov_base;  Base address.
 *	size_t iov_len;    Length.
 * }; */

/* TYPEDEFS, STRUCT DECLARATIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, STRUCT DECLARATIONS
 *
 *
 * FUNCTION-LIKE MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#ifdef WIN32
#	include <windows.h>	/* FindFirst/NextFile */
#	include <direct.h>	/* directory API */

/* check accessability of a file */
#	define access_imp(PATH,						\
			  MODE)						\
	_access_s(PATH,							\
		  MODE)

/* open a file */
#	define open_imp(PATH,						\
			OPEN_FLAG)					\
	_open(PATH,							\
	      OPEN_FLAG)
#	define open_mode_imp(PATH,					\
			     OPEN_FLAG,					\
			     MODE)					\
	_open(PATH,							\
	      OPEN_FLAG,						\
	      MODE)
#	undef open_relative_imp
#	warning "open_relative undefined"
#	undef open_relative_mode_imp
#	warning "open_relative_mode undefined"

/* read a file */
#	define read_imp(FILE_DESCRIPTOR,				\
			BUFFER,						\
			SIZE)						\
	_read(FILE_DESCRIPTOR,						\
	      BUFFER,							\
	      (unsigned int) (SIZE))

/* write to a file */
#	define write_imp(FILE_DESCRIPTOR,				\
			 BUFFER,					\
			 SIZE)						\
	_write(FILE_DESCRIPTOR,						\
	       BUFFER,							\
	       (unsigned int) (SIZE))

/* close a file */
#	define close_imp(FILE_DESCRIPTOR)				\
	_close(FILE_DESCRIPTOR)
#	define close_imp(FILE_DESCRIPTOR)				\

/* delete a file */
#	define unlink_imp(PATH)						\
	_unlink(PATH)
#	undef unlink_relative_imp
#	warning "unlink_relative undefined"

/* fetch info on a file */
#	define stat_imp(PATH,						\
			BUFFER)						\
	_stat(PATH,							\
	      BUFFER)
#	define StatBuffer _stat

/* make a directory */
#	define mkdir_imp(PATH,						\
			 MODE)						\
	_mkdir(PATH)
#	undef mkdir_relative_imp
#	warning "mkdir_relative undefined"

/* change working directory */
#	define chdir_imp(PATH)						\
	_chdir(PATH)

/* delete a directory */
#	define rmdir_imp(PATH)						\
	_rmdir(PATH)

#else
#	include <dirent.h>
#	include <fts.h>

/* check accessability of a file */
#	define access_imp(PATH,						\
			  MODE)						\
	access(PATH,							\
	       MODE)

/* open a file */
#	define open_imp(PATH,						\
			OPEN_FLAG)					\
	open(PATH,							\
	     OPEN_FLAG)
#	define open_mode_imp(PATH,					\
			     OPEN_FLAG,					\
			     MODE)					\
	open(PATH,							\
	     OPEN_FLAG,							\
	     MODE)
#	define open_relative_imp(DIRECTORY_DESCRIPTOR,			\
				 RELATIVE_PATH,				\
				 OPEN_FLAG)				\
	openat(DIRECTORY_DESCRIPTOR,					\
	       RELATIVE_PATH,						\
	       OPEN_FLAG)
#	define open_relative_mode_imp(DIRECTORY_DESCRIPTOR,		\
				      RELATIVE_PATH,			\
				      OPEN_FLAG,			\
				      MODE)				\
	openat(DIRECTORY_DESCRIPTOR,					\
	       RELATIVE_PATH,						\
	       OPEN_FLAG,						\
	       MODE)

/* read a file */
#	define read_imp(FILE_DESCRIPTOR,				\
			BUFFER,						\
			SIZE)						\
	read(FILE_DESCRIPTOR,						\
	     BUFFER,							\
	     SIZE)

/* write to a file */
#	define write_imp(FILE_DESCRIPTOR,				\
			 BUFFER,					\
			 SIZE)						\
	write(FILE_DESCRIPTOR,						\
	      BUFFER,							\
	      SIZE)

/* close a file */
#	define close_imp(FILE_DESCRIPTOR)				\
	close(FILE_DESCRIPTOR)

/* delete a file */
#	define unlink_imp(PATH)						\
	unlink(PATH)
#	define unlink_relative_imp(DIRECTORY_DESCRIPTOR,		\
				   RELATIVE_PATH,			\
				   UNLINK_FLAG)				\
	unlinkat(DIRECTORY_DESCRIPTOR,					\
		 RELATIVE_PATH,						\
		 UNLINK_FLAG)

/* fetch info on a file */
#	define stat_imp(PATH,						\
			BUFFER)						\
	stat(PATH,							\
	     BUFFER)
#	define StatBuffer stat

/* make a directory */
#	define mkdir_imp(PATH,						\
			 MODE)						\
	mkdir(PATH,							\
	      MODE)
#	define mkdir_relative_imp(DIRECTORY_DESCRIPTOR,			\
				  RELATIVE_PATH,			\
				  MODE)					\
	mkdirat(DIRECTORY_DESCRIPTOR,					\
		RELATIVE_PATH,						\
		MODE)

/* change working directory */
#	define chdir_imp(PATH)						\
	chdir(PATH)

/* delete a directory */
#	define rmdir_imp(PATH)						\
	rmdir(PATH)
#endif /* ifdef WIN32 */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * FUNCTION-LIKE MACROS
 *
 *
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* same for all file system calls called below */
#define FAIL_SWITCH_ERRNO_FAILURE	-1
#define FAIL_SWITCH_FAILURE_POINTER	failure

/* access (absolute or relative path) */
inline bool
access_status(const char *const restrict path,
	      const int mode)
{
	return access_imp(path,
			  mode) == 0;
}

inline void
access_muffle(const char *const restrict path,
	      const int mode)
{
	(void) access_imp(path,
			  mode);
}

#define FAIL_SWITCH_ROUTINE access_imp
inline bool
access_report(const char *const restrict path,
	      const int mode,
	      const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(path,
			       mode)
	FAIL_SWITCH_ERRNO_CASE_2(EACCES,
				 "Permission bits of the file mode do not "
				 "permit the requested access, or search "
				 "permission is denied on a component of the "
				 "path prefix.",
				 "The owner of a file has permission checked "
				 "with respect to the 'owner' read, write, and "
				 "execute mode bits, members of the file's "
				 "group other than the owner have permission "
				 "checked with respect to the 'group' mode bits"
				 ", and all others have permissions checked "
				 "with respect to the 'other' mode bits.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'path' points outside the process's allocated"
				 " address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "An invalid value was specified for 'mode'.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "An I/O error occurred while reading from or "
				 "writing to the file system.")
	FAIL_SWITCH_ERRNO_CASE_1(ELOOP,
				 "Too many symbolic links were encountered in "
				 "translating the pathname.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of a pathname exceeded {NAME_MAX}"
				 " characters, or an entire path name exceeded "
				 "{PATH_MAX} characters.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOENT,
				 "The named file does not exist.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOTDIR,
				 "A component of the path prefix is not a "
				 "directory.")
	FAIL_SWITCH_ERRNO_CASE_1(EROFS,
				 "Write access is requested for a file on a "
				 "read-only file system.")
	FAIL_SWITCH_ERRNO_CASE_1(ETXTBSY,
				 "Write access is requested for a pure "
				 "procedure (shared text) file that is "
				 "presently being executed.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
access_handle(const char *const restrict path,
	      const int mode,
	      Handler *const handle,
	      void *arg)
{
	const char *restrict failure;

	if (access_report(path,
			  mode,
			  &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
access_handle_cl(const char *const restrict path,
		 const int mode,
		 const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (access_report(path,
			  mode,
			  &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* open (absolute or relative path, no mode) */
inline bool
open_status(int *const restrict file_descriptor,
	    const char *const path,
	    const int open_flag)
{
	*file_descriptor = open_imp(path,
				    open_flag);

	return *file_descriptor >= 0;
}

inline void
open_muffle(int *const restrict file_descriptor,
	    const char *const path,
	    const int open_flag)
{
	*file_descriptor = open_imp(path,
				    open_flag);
}

#undef	FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE open_imp
inline bool
open_report(int *const restrict file_descriptor,
	    const char *const path,
	    const int open_flag,
	    const char *restrict *const restrict failure)
{
	*file_descriptor = open_imp(path,
				    open_flag);

	if (*file_descriptor >= 0)
		return true;

	switch (errno) {
	FAIL_SWITCH_ERRNO_CASE_4(EACCES,
				 "Search permission is denied for a component "
				 "of the path prefix.",
				 "The required permissions (for reading and/or "
				 "writing) are denied for the given flags.",
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the directory in which it is to be"
				 " created does not permit writing.",
				 "'O_TRUNC' is specified and write permission "
				 "is denied.")
	FAIL_SWITCH_ERRNO_CASE_1(EAGAIN,
				 "path specifies the slave side of a locked "
				 "pseudo-terminal device.")
	FAIL_SWITCH_ERRNO_CASE_2(EDQUOT,
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the directory in which the entry "
				 "for the new file is being placed cannot be "
				 "extended because the user's quota of disk "
				 "blocks on the file system containing the "
				 "directory has been exhausted.",
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the user's quota of inodes on the "
				 "file system on which the file is being "
				 "created has been exhausted.")
	FAIL_SWITCH_ERRNO_CASE_1(EEXIST,
				 "'O_CREAT' and 'O_EXCL' are specified and the "
				 "file exists.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'path' points outside the process's allocated"
				 " address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "The open() operation is interrupted by a "
				 "signal.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "The value of 'open_flag' is not valid.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "An I/O error occurs while making the "
				 "directory entry or allocating the inode for '"
				 "O_CREAT'.")
	FAIL_SWITCH_ERRNO_CASE_1(EISDIR,
				 "The named file is a directory, and the "
				 "arguments specify that it is to be opened for"
				 " writing.")
	FAIL_SWITCH_ERRNO_CASE_2(ELOOP,
				 "Too many symbolic links are encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.",
				 "'O_NOFOLLOW' was specified and the target is "
				 "a symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(EMFILE,
				 "The process has already reached its limit for"
				 " open file descriptors.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of a pathname exceeds {NAME_MAX} "
				 "characters, or an entire path name exceeded "
				 "{PATH_MAX} characters.")
	FAIL_SWITCH_ERRNO_CASE_1(ENFILE,
				 "The system file table is full.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOENT,
				 "'O_CREAT' is not set and the named file does "
				 "not exist.",
				 "A component of the path name that must exist "
				 "does not exist.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOSPC,
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the directory in which the entry "
				 "for the new file is being placed cannot be "
				 "extended because there is no space left on "
				 "the file system containing the direc- tory.",
				 "'O_CREAT' is specified, the file does not "
				 "exist, and there are no free inodes on the "
				 "file system on which the file is being "
				 "created.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTDIR,
				 "A component of the path prefix is not a "
				 "directory.",
				 "The path argument is not an absolute path")
	FAIL_SWITCH_ERRNO_CASE_2(ENXIO,
				 "The named file is a character-special or "
				 "block-special file and the device associated "
				 "with this special file does not exist.",
				 "'O_NONBLOCK' and 'O_WRONLY' are set, the file"
				 " is a FIFO, and no process has it open for "
				 "reading.")
	FAIL_SWITCH_ERRNO_CASE_2(EOPNOTSUPP,
				 "'O_SHLOCK' or 'O_EXLOCK' is specified, but "
				 "the underlying filesystem does not support "
				 "locking.",
				 "An attempt is made to open a socket (not "
				 "currently implemented).")
	FAIL_SWITCH_ERRNO_CASE_1(EOVERFLOW,
				 "The named file is a regular file and its size"
				 " does not fit in an object of type 'off_t'.")
	FAIL_SWITCH_ERRNO_CASE_1(EROFS,
				 "The named file resides on a read-only file "
				 "system, and the file is to be modified.")
	FAIL_SWITCH_ERRNO_CASE_1(ETXTBSY,
				 "The file is a pure procedure (shared text) "
				 "file that is being executed and the open() "
				 "call requests write access.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "The path argument does not specify an "
				 "absolute path.")
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

inline void
open_handle(int *const restrict file_descriptor,
	    const char *const path,
	    const int open_flag,
	    Handler *const handle,
	    void *arg)
{
	const char *restrict failure;

	if (open_report(file_descriptor,
			path,
			open_flag,
			&failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
open_handle_cl(int *const restrict file_descriptor,
	       const char *const path,
	       const int open_flag,
	       const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (open_report(file_descriptor,
			path,
			open_flag,
			&failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* open (absolute or relative path, provide mode) */
inline bool
open_mode_status(int *const restrict file_descriptor,
		 const char *const path,
		 const int open_flag,
		 const mode_t mode)
{
	*file_descriptor = open_mode_imp(path,
					 open_flag,
					 mode);

	return *file_descriptor >= 0;
}

inline void
open_mode_muffle(int *const restrict file_descriptor,
		 const char *const path,
		 const int open_flag,
		 const mode_t mode)
{
	*file_descriptor = open_mode_imp(path,
					 open_flag,
					 mode);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE open_mode_imp
inline bool
open_mode_report(int *const restrict file_descriptor,
		 const char *const path,
		 const int open_flag,
		 const mode_t mode,
		 const char *restrict *const restrict failure)
{
	*file_descriptor = open_mode_imp(path,
					 open_flag,
					 mode);

	if (*file_descriptor >= 0)
		return true;

	switch(errno) {
	FAIL_SWITCH_ERRNO_CASE_4(EACCES,
				 "Search permission is denied for a component "
				 "of the path prefix.",
				 "The required permissions (for reading and/or "
				 "writing) are denied for the given flags.",
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the directory in which it is to be"
				 " created does not permit writing.",
				 "'O_TRUNC' is specified and write permission "
				 "is denied.")
	FAIL_SWITCH_ERRNO_CASE_1(EAGAIN,
				 "path specifies the slave side of a locked "
				 "pseudo-terminal device.")
	FAIL_SWITCH_ERRNO_CASE_2(EDQUOT,
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the directory in which the entry "
				 "for the new file is being placed cannot be "
				 "extended because the user's quota of disk "
				 "blocks on the file system containing the "
				 "directory has been exhausted.",
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the user's quota of inodes on the "
				 "file system on which the file is being "
				 "created has been exhausted.")
	FAIL_SWITCH_ERRNO_CASE_1(EEXIST,
				 "'O_CREAT' and 'O_EXCL' are specified and the "
				 "file exists.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'path' points outside the process's allocated"
				 " address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "The open_mode() operation is "
				 "interrupted by a signal.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "The value of 'open_flag' is not valid.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "An I/O error occurs while making the "
				 "directory entry or allocating the inode for '"
				 "O_CREAT'.")
	FAIL_SWITCH_ERRNO_CASE_1(EISDIR,
				 "The named file is a directory, and the "
				 "arguments specify that it is to be opened for"
				 " writing.")
	FAIL_SWITCH_ERRNO_CASE_2(ELOOP,
				 "Too many symbolic links are encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.",
				 "'O_NOFOLLOW' was specified and the target is "
				 "a symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(EMFILE,
				 "The process has already reached its limit for"
				 " open file descriptors.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of a pathname exceeds {NAME_MAX} "
				 "characters, or an entire path name exceeded "
				 "{PATH_MAX} characters.")
	FAIL_SWITCH_ERRNO_CASE_1(ENFILE,
				 "The system file table is full.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOENT,
				 "'O_CREAT' is not set and the named file does "
				 "not exist.",
				 "A component of the path name that must exist "
				 "does not exist.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOSPC,
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the directory in which the entry "
				 "for the new file is being placed cannot be "
				 "extended because there is no space left on "
				 "the file system containing the direc- tory.",
				 "'O_CREAT' is specified, the file does not "
				 "exist, and there are no free inodes on the "
				 "file system on which the file is being "
				 "created.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTDIR,
				 "A component of the path prefix is not a "
				 "directory.",
				 "The path argument is not an absolute path")
	FAIL_SWITCH_ERRNO_CASE_2(ENXIO,
				 "The named file is a character-special or "
				 "block-special file and the device associated "
				 "with this special file does not exist.",
				 "'O_NONBLOCK' and 'O_WRONLY' are set, the file"
				 " is a FIFO, and no process has it open for "
				 "reading.")
	FAIL_SWITCH_ERRNO_CASE_2(EOPNOTSUPP,
				 "'O_SHLOCK' or 'O_EXLOCK' is specified, but "
				 "the underlying filesystem does not support "
				 "locking.",
				 "An attempt is made to open a socket (not "
				 "currently implemented).")
	FAIL_SWITCH_ERRNO_CASE_1(EOVERFLOW,
				 "The named file is a regular file and its size"
				 " does not fit in an object of type 'off_t'.")
	FAIL_SWITCH_ERRNO_CASE_1(EROFS,
				 "The named file resides on a read-only file "
				 "system, and the file is to be modified.")
	FAIL_SWITCH_ERRNO_CASE_1(ETXTBSY,
				 "The file is a pure procedure (shared text) "
				 "file that is being executed and the "
				 "open_mode() call requests write "
				 "access.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "The path argument does not specify an "
				 "absolute path.")
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

inline void
open_mode_handle(int *const restrict file_descriptor,
		 const char *const path,
		 const int open_flag,
		 const mode_t mode,
		 Handler *const handle,
		 void *arg)
{
	const char *restrict failure;

	if (open_mode_report(file_descriptor,
			     path,
			     open_flag,
			     mode,
			     &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
open_mode_handle_cl(int *const restrict file_descriptor,
		    const char *const path,
		    const int open_flag,
		    const mode_t mode,
		    const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (open_mode_report(file_descriptor,
			     path,
			     open_flag,
			     mode,
			     &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}

#ifndef WIN32
/* open (relative path, no mode) */
inline bool
open_relative_status(int *const restrict file_descriptor,
		     const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag)
{
	*file_descriptor = open_relative_imp(directory_descriptor,
					     relative_path,
					     open_flag);

	return *file_descriptor >= 0;
}

inline void
open_relative_muffle(int *const restrict file_descriptor,
		     const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag)
{
	*file_descriptor = open_relative_imp(directory_descriptor,
					     relative_path,
					     open_flag);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE open_relative_imp
inline bool
open_relative_report(int *const restrict file_descriptor,
		     const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag,
		     const char *restrict *const restrict failure)
{
	*file_descriptor = open_relative_imp(directory_descriptor,
					     relative_path,
					     open_flag);

	if (*file_descriptor >= 0)
		return true;

	switch(errno) {
	FAIL_SWITCH_ERRNO_CASE_4(EACCES,
				 "Search permission is denied for a component "
				 "of the path prefix.",
				 "The required permissions (for reading and/or "
				 "writing) are denied for the given flags.",
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the directory in which it is to be"
				 " created does not permit writing.",
				 "'O_TRUNC' is specified and write permission "
				 "is denied.")
	FAIL_SWITCH_ERRNO_CASE_1(EAGAIN,
				 "path specifies the slave side of a locked "
				 "pseudo-terminal device.")
	FAIL_SWITCH_ERRNO_CASE_2(EDQUOT,
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the directory in which the entry "
				 "for the new file is being placed cannot be "
				 "extended because the user's quota of disk "
				 "blocks on the file system containing the "
				 "directory has been exhausted.",
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the user's quota of inodes on the "
				 "file system on which the file is being "
				 "created has been exhausted.")
	FAIL_SWITCH_ERRNO_CASE_1(EEXIST,
				 "'O_CREAT' and 'O_EXCL' are specified and the "
				 "file exists.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'path' points outside the process's allocated"
				 " address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "The open_relative() operation is interrupted "
				 "by a signal.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "The value of 'open_flag' is not valid.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "An I/O error occurs while making the "
				 "directory entry or allocating the inode for '"
				 "O_CREAT'.")
	FAIL_SWITCH_ERRNO_CASE_1(EISDIR,
				 "The named file is a directory, and the "
				 "arguments specify that it is to be opened for"
				 " writing.")
	FAIL_SWITCH_ERRNO_CASE_2(ELOOP,
				 "Too many symbolic links are encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.",
				 "'O_NOFOLLOW' was specified and the target is "
				 "a symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(EMFILE,
				 "The process has already reached its limit for"
				 " open file descriptors.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of a pathname exceeds {NAME_MAX} "
				 "characters, or an entire path name exceeded "
				 "{PATH_MAX} characters.")
	FAIL_SWITCH_ERRNO_CASE_1(ENFILE,
				 "The system file table is full.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOENT,
				 "'O_CREAT' is not set and the named file does "
				 "not exist.",
				 "A component of the path name that must exist "
				 "does not exist.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOSPC,
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the directory in which the entry "
				 "for the new file is being placed cannot be "
				 "extended because there is no space left on "
				 "the file system containing the direc- tory.",
				 "'O_CREAT' is specified, the file does not "
				 "exist, and there are no free inodes on the "
				 "file system on which the file is being "
				 "created.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTDIR,
				 "A component of the path prefix is not a "
				 "directory.",
				 "'directory_descriptor' is neither 'AT_FDCWD' "
				 "nor a file descriptor associated with a "
				 "directory.")
	FAIL_SWITCH_ERRNO_CASE_2(ENXIO,
				 "The named file is a character-special or "
				 "block-special file and the device associated "
				 "with this special file does not exist.",
				 "'O_NONBLOCK' and 'O_WRONLY' are set, the file"
				 " is a FIFO, and no process has it open for "
				 "reading.")
	FAIL_SWITCH_ERRNO_CASE_2(EOPNOTSUPP,
				 "'O_SHLOCK' or 'O_EXLOCK' is specified, but "
				 "the underlying filesystem does not support "
				 "locking.",
				 "An attempt is made to open a socket (not "
				 "currently implemented).")
	FAIL_SWITCH_ERRNO_CASE_1(EOVERFLOW,
				 "The named file is a regular file and its size"
				 " does not fit in an object of type 'off_t'.")
	FAIL_SWITCH_ERRNO_CASE_1(EROFS,
				 "The named file resides on a read-only file "
				 "system, and the file is to be modified.")
	FAIL_SWITCH_ERRNO_CASE_1(ETXTBSY,
				 "The file is a pure procedure (shared text) "
				 "file that is being executed and the "
				 "open_relative() call requests write access.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'directory_descriptor' is neither 'AT_FDCWD' "
				 "nor a valid file descriptor open for "
				 "searching.")
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

inline void
open_relative_handle(int *const restrict file_descriptor,
		     const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag,
		     Handler *const handle,
		     void *arg)
{
	const char *restrict failure;

	if (open_relative_report(file_descriptor,
				 directory_descriptor,
				 relative_path,
				 open_flag,
				 &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
open_relative_handle_cl(int *const restrict file_descriptor,
			const int directory_descriptor,
			const char *const relative_path,
			const int open_flag,
			const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (open_relative_report(file_descriptor,
				 directory_descriptor,
				 relative_path,
				 open_flag,
				 &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* open (relative path, provide mode) */
inline bool
open_relative_mode_status(int *const restrict file_descriptor,
			  const int directory_descriptor,
			  const char *const relative_path,
			  const int open_flag,
			  const mode_t mode)
{
	*file_descriptor = open_relative_mode_imp(directory_descriptor,
						  relative_path,
						  open_flag,
						  mode);

	return *file_descriptor >= 0;
}

inline void
open_relative_mode_muffle(int *const restrict file_descriptor,
			  const int directory_descriptor,
			  const char *const relative_path,
			  const int open_flag,
			  const mode_t mode)
{
	*file_descriptor = open_relative_mode_imp(directory_descriptor,
						  relative_path,
						  open_flag,
						  mode);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE open_relative_mode_imp
inline bool
open_relative_mode_report(int *const restrict file_descriptor,
			  const int directory_descriptor,
			  const char *const relative_path,
			  const int open_flag,
			  const mode_t mode,
			  const char *restrict *const restrict failure)
{
	*file_descriptor = open_relative_mode_imp(directory_descriptor,
						  relative_path,
						  open_flag,
						  mode);

	if (*file_descriptor >= 0)
		return true;

	switch(errno) {
	FAIL_SWITCH_ERRNO_CASE_4(EACCES,
				 "Search permission is denied for a component "
				 "of the path prefix.",
				 "The required permissions (for reading and/or "
				 "writing) are denied for the given flags.",
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the directory in which it is to be"
				 " created does not permit writing.",
				 "'O_TRUNC' is specified and write permission "
				 "is denied.")
	FAIL_SWITCH_ERRNO_CASE_1(EAGAIN,
				 "'path' specifies the slave side of a locked "
				 "pseudo-terminal device.")
	FAIL_SWITCH_ERRNO_CASE_2(EDQUOT,
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the directory in which the entry "
				 "for the new file is being placed cannot be "
				 "extended because the user's quota of disk "
				 "blocks on the file system containing the "
				 "directory has been exhausted.",
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the user's quota of inodes on the "
				 "file system on which the file is being "
				 "created has been exhausted.")
	FAIL_SWITCH_ERRNO_CASE_1(EEXIST,
				 "'O_CREAT' and 'O_EXCL' are specified and the "
				 "file exists.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'path' points outside the process's allocated"
				 " address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "The open_relative_mode() operation is "
				 "interrupted by a signal.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "The value of 'open_flag' is not valid.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "An I/O error occurs while making the "
				 "directory entry or allocating the inode for '"
				 "O_CREAT'.")
	FAIL_SWITCH_ERRNO_CASE_1(EISDIR,
				 "The named file is a directory, and the "
				 "arguments specify that it is to be opened for"
				 " writing.")
	FAIL_SWITCH_ERRNO_CASE_2(ELOOP,
				 "Too many symbolic links are encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.",
				 "'O_NOFOLLOW' was specified and the target is "
				 "a symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(EMFILE,
				 "The process has already reached its limit for"
				 " open file descriptors.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of a pathname exceeds {NAME_MAX} "
				 "characters, or an entire path name exceeded "
				 "{PATH_MAX} characters.")
	FAIL_SWITCH_ERRNO_CASE_1(ENFILE,
				 "The system file table is full.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOENT,
				 "'O_CREAT' is not set and the named file does "
				 "not exist.",
				 "A component of the path name that must exist "
				 "does not exist.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOSPC,
				 "'O_CREAT' is specified, the file does not "
				 "exist, and the directory in which the entry "
				 "for the new file is being placed cannot be "
				 "extended because there is no space left on "
				 "the file system containing the direc- tory.",
				 "'O_CREAT' is specified, the file does not "
				 "exist, and there are no free inodes on the "
				 "file system on which the file is being "
				 "created.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTDIR,
				 "A component of the path prefix is not a "
				 "directory.",
				 "'directory_descriptor' is neither 'AT_FDCWD' "
				 "nor a file descriptor associated with a "
				 "directory.")
	FAIL_SWITCH_ERRNO_CASE_2(ENXIO,
				 "The named file is a character-special or "
				 "block-special file and the device associated "
				 "with this special file does not exist.",
				 "'O_NONBLOCK' and 'O_WRONLY' are set, the file"
				 " is a FIFO, and no process has it open for "
				 "reading.")
	FAIL_SWITCH_ERRNO_CASE_2(EOPNOTSUPP,
				 "'O_SHLOCK' or 'O_EXLOCK' is specified, but "
				 "the underlying filesystem does not support "
				 "locking.",
				 "An attempt is made to open a socket (not "
				 "currently implemented).")
	FAIL_SWITCH_ERRNO_CASE_1(EOVERFLOW,
				 "The named file is a regular file and its size"
				 " does not fit in an object of type 'off_t'.")
	FAIL_SWITCH_ERRNO_CASE_1(EROFS,
				 "The named file resides on a read-only file "
				 "system, and the file is to be modified.")
	FAIL_SWITCH_ERRNO_CASE_1(ETXTBSY,
				 "The file is a pure procedure (shared text) "
				 "file that is being executed and the "
				 "open_relative_mode() call requests write "
				 "access.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'directory_descriptor' is neither 'AT_FDCWD' "
				 "nor a valid file descriptor open for "
				 "searching.")
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

inline void
open_relative_mode_handle(int *const restrict file_descriptor,
			  const int directory_descriptor,
			  const char *const relative_path,
			  const int open_flag,
			  const mode_t mode,
			  Handler *const handle,
			  void *arg)
{
	const char *restrict failure;

	if (open_relative_mode_report(file_descriptor,
				      directory_descriptor,
				      relative_path,
				      open_flag,
				      mode,
				      &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
open_relative_mode_handle_cl(int *const restrict file_descriptor,
			     const int directory_descriptor,
			     const char *const relative_path,
			     const int open_flag,
			     const mode_t mode,
			     const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (open_relative_mode_report(file_descriptor,
				      directory_descriptor,
				      relative_path,
				      open_flag,
				      mode,
				      &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}
#endif /* ifndef WIN32 */


/* read */
inline bool
read_status(const int file_descriptor,
	    void *const restrict buffer,
	    const size_t size)
{
	return read_imp(file_descriptor,
			buffer,
			size) == 0;
}

inline void
read_muffle(const int file_descriptor,
	    void *const restrict buffer,
	    const size_t size)
{
	(void) read_imp(file_descriptor,
			buffer,
			size);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE read_imp
inline bool
read_report(const int file_descriptor,
	    void *const restrict buffer,
	    const size_t size,
	    const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(file_descriptor,
			       buffer,
			       size)
	FAIL_SWITCH_ERRNO_CASE_1(EAGAIN,
				 "The file was marked for non-blocking I/O, and"
				 " no data were ready to be read.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'file_descriptor' is not a valid file or "
				 "socket descriptor open for reading.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'buffer' points outside the allocated address"
				 " space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "A read from a slow device was interrupted "
				 "before any data arrived by the delivery of a "
				 "signal.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "The pointer associated with 'file_descriptor'"
				 " was negative.")
	FAIL_SWITCH_ERRNO_CASE_3(EIO,
				 "An I/O error occurred while reading from the "
				 "file system.",
				 "The process group is orphaned.",
				 "The file is a regular file, 'size' is greater"
				 " than 0, the starting position is before the "
				 "end-of-file, and the starting position is "
				 "greater than or equal to the offset maximum "
				 "established for the open file descriptor "
				 "associated with 'file_descriptor'.")
	FAIL_SWITCH_ERRNO_CASE_1(EISDIR,
				 "An attempt was made to read a directory.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOBUFS,
				 "An attempt to allocate a memory buffer failed"
				 ".")
	FAIL_SWITCH_ERRNO_CASE_1(ENOMEM,
				 "Insufficient memory is available.")
	FAIL_SWITCH_ERRNO_CASE_2(ENXIO,
				 "An action was requested of a device that does"
				 " not exist.",
				 "A requested action cannot be performed by the"
				 " device.")
	FAIL_SWITCH_ERRNO_CASE_1(ECONNRESET,
				 "The connection was closed by the peer during "
				 "a read attempt on a socket.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOTCONN,
				 "A read was attempted on an unconnected socket"
				 ".")
	FAIL_SWITCH_ERRNO_CASE_1(ETIMEDOUT,
				 "A transmission timeout occurs during a read "
				 "attempt on a socket.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
read_handle(const int file_descriptor,
	    void *const restrict buffer,
	    const size_t size,
	    Handler *const handle,
	    void *arg)
{
	const char *restrict failure;

	if (read_report(file_descriptor,
			buffer,
			size,
			&failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
read_handle_cl(const int file_descriptor,
	       void *const restrict buffer,
	       const size_t size,
	       const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (read_report(file_descriptor,
			buffer,
			size,
			&failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* write */
inline bool
write_status(const int file_descriptor,
	     const void *const restrict buffer,
	     const size_t size)
{
	return write_imp(file_descriptor,
			 buffer,
			 size) != -1;
}

inline void
write_muffle(const int file_descriptor,
	     const void *const restrict buffer,
	     const size_t size)
{
	(void) write_imp(file_descriptor,
			 buffer,
			 size);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE write_imp
inline bool
write_report(const int file_descriptor,
	     const void *const restrict buffer,
	     const size_t size,
	     const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(file_descriptor,
			       buffer,
			       size)
	FAIL_SWITCH_ERRNO_CASE_1(EDQUOT,
				 "The user's quota of disk blocks on the file "
				 "system containing the file was exhausted.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "Part of 'iov' or data to be written to the "
				 "file points outside the process's allocated "
				 "address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "The pointer associated with 'file_descriptor'"
				 " is negative.")
	FAIL_SWITCH_ERRNO_CASE_1(ESPIPE,
				 "The file descriptor is associated with a pipe"
				 ", socket, or FIFO.")
	FAIL_SWITCH_ERRNO_CASE_3(EAGAIN,
				 "The file is marked for non-blocking I/O, and "
				 "no data could be written immediately.",
				 "The file descriptor is for a socket, is "
				 "marked 'O_NONBLOCK', and write would block.",
				 "The file descriptor is for a socket, is "
				 "marked 'O_NONBLOCK', and write would block.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'file_descriptor' is not a valid file "
				 "descriptor open for writing.")
	FAIL_SWITCH_ERRNO_CASE_1(ECONNRESET,
				 "A write was attempted on a socket that is not"
				 " connected.")
	FAIL_SWITCH_ERRNO_CASE_2(EFBIG,
				 "An attempt was made to write a file that "
				 "exceeds the process's file size, limit, or "
				 "the maximum file size.",
				 "The file is a regular file, 'size' is "
				 "greater than 0, and the starting position is "
				 "greater than or equal to the offset maximum "
				 "established in the open file description "
				 "associated with 'file_descriptor'.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "A signal interruptted the write before it could"
				 " be completed.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "An I/O error occurred while reading from or "
				 "writing to the file system.")
	FAIL_SWITCH_ERRNO_CASE_1(ENETDOWN,
				 "A write is attempted on a socket and the "
				 "local network interface used to reach the "
				 "destination is down.")
	FAIL_SWITCH_ERRNO_CASE_1(ENETUNREACH,
				 "A write was attempted on a socket and no "
				 "route to the network is present.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOSPC,
				 "There was no free space remaining on the file"
				 " system containing the file.")
	FAIL_SWITCH_ERRNO_CASE_1(ENXIO,
				 "A request was made of a nonexistent device, "
				 "or the request was outside the capabilities "
				 "of the device.")
	FAIL_SWITCH_ERRNO_CASE_2(EPIPE,
				 "An attempt was made to write to a pipe that "
				 "is not open for reading by any process.",
				 "An attempt was made to write to a socket of "
				 "type 'SOCK_STREAM' that is not connected to a"
				 " peer socket.")
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

inline void
write_handle(const int file_descriptor,
	     const void *const restrict buffer,
	     const size_t size,
	     Handler *const handle,
	     void *arg)
{
	const char *restrict failure;

	if (write_report(file_descriptor,
			 buffer,
			 size,
			 &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
write_handle_cl(const int file_descriptor,
		const void *const restrict buffer,
		const size_t size,
		const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (write_report(file_descriptor,
			 buffer,
			 size,
			 &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* close */
inline bool
close_status(const int file_descriptor)
{
	return close_imp(file_descriptor) == 0;
}

inline void
close_muffle(const int file_descriptor)
{
	(void) close_imp(file_descriptor);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE close_imp
inline bool
close_report(const int file_descriptor,
	     const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(file_descriptor)
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'file_descriptor' is not a valid, active file"
				 " descriptor.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "Execution was interrupted by a signal.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "A previously-uncommitted write(2) encountered"
				 " an input/output error.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
close_handle(const int file_descriptor,
	     Handler *const handle,
	     void *arg)
{
	const char *restrict failure;

	if (close_report(file_descriptor,
			 &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
close_handle_cl(const int file_descriptor,
		const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (close_report(file_descriptor,
			 &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* unlink (absolute or relative path) */
inline bool
unlink_status(const char *const restrict path)
{
	return unlink_imp(path) == 0;
}

inline void
unlink_muffle(const char *const restrict path)
{
	(void) unlink_imp(path);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE unlink_imp
inline bool
unlink_report(const char *const restrict path,
	      const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(path)
	FAIL_SWITCH_ERRNO_CASE_2(EACCES,
				 "Search permission is denied for a component "
				 "of the path prefix.",
				 "Write permission is denied on the directory "
				 "containing the link to be removed.")
	FAIL_SWITCH_ERRNO_CASE_2(EBUSY,
				 "The entry to be unlinked is the mount point "
				 "for a mounted file system.",
				 "The file named by 'path' cannot be unlinked "
				 "because it is being used by the system or by "
				 "another process.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'path' points outside the process's allocated"
				 " address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "An I/O error occurred while deleting the "
				 "directory entry or deallocating the inode.")
	FAIL_SWITCH_ERRNO_CASE_1(ELOOP,
				 "Too many symbolic links are encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of 'path' exceeds {NAME_MAX} "
				 "characters, or the entire path name exceeds "
				 "{PATH_MAX} characters (possibly as a result "
				 "of expanding a symlink).")
	FAIL_SWITCH_ERRNO_CASE_1(ENOENT,
				 "The named file does not exist.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOTDIR,
				 "A component of the path prefix is not a "
				 "directory.")
	FAIL_SWITCH_ERRNO_CASE_2(EPERM,
				 "The named file is a directory and the "
				 "effective user ID of the process is not the "
				 "super-user.",
				 "The directory containing the file is marked "
				 "sticky, and neither the containing directory "
				 "nor the file to be removed are owned by the "
				 "effective user ID.")
	FAIL_SWITCH_ERRNO_CASE_1(EROFS,
				 "The named file resides on a read-only file "
				 "system.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
unlink_handle(const char *const restrict path,
	      Handler *const handle,
	      void *arg)
{
	const char *restrict failure;

	if (unlink_report(path,
			  &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
unlink_handle_cl(const char *const restrict path,
		 const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (unlink_report(path,
			  &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


#ifndef WIN32
/* unlink (relative path) */
inline bool
unlink_relative_status(const int directory_descriptor,
		       const char *const restrict relative_path,
		       const int unlink_flag)
{
	return unlink_relative_imp(directory_descriptor,
				   relative_path,
				   unlink_flag) == 0;
}

inline void
unlink_relative_muffle(const int directory_descriptor,
		       const char *const restrict relative_path,
		       const int unlink_flag)
{
	(void) unlink_relative_imp(directory_descriptor,
				   relative_path,
				   unlink_flag);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE unlink_relative_imp
inline bool
unlink_relative_report(const int directory_descriptor,
		       const char *const restrict relative_path,
		       const int unlink_flag,
		       const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(directory_descriptor,
			       relative_path,
			       unlink_flag)
	FAIL_SWITCH_ERRNO_CASE_2(EACCES,
				 "Search permission is denied for a component "
				 "of the path prefix.",
				 "Write permission is denied on the directory "
				 "containing the link to be removed.")
	FAIL_SWITCH_ERRNO_CASE_2(EBUSY,
				 "The entry to be unlinked is the mount point "
				 "for a mounted file system.",
				 "The file named by 'relative_path' cannot be "
				 "unlinked because it is being used by the "
				 "system or by another process.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'relative_path' points outside the process's "
				 "allocated address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "An I/O error occurred while deleting the "
				 "directory entry or deallocating the inode.")
	FAIL_SWITCH_ERRNO_CASE_1(ELOOP,
				 "Too many symbolic links are encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of 'relative_path' exceeds "
				 "{NAME_MAX} characters, or an entire path name"
				 " exceeds {PATH_MAX} characters (possibly as a"
				 " result of expanding a symlink).")
	FAIL_SWITCH_ERRNO_CASE_1(ENOENT,
				 "The named file does not exist.")
	FAIL_SWITCH_ERRNO_CASE_3(ENOTDIR,
				 "A component of the path prefix is not a "
				 "directory.",
				 "The 'unlink_flag' parameter has the '"
				 "AT_REMOVEDIR' bit set and 'relative_path' "
				 "does not name a directory.",
				 "'relative_path' is not an absolute path and '"
				 "directory_descriptor' is neither 'AT_FDCWD' "
				 "nor a file descriptor associated with a "
				 "directory.")
	FAIL_SWITCH_ERRNO_CASE_2(EPERM,
				 "The named file is a directory and the "
				 "effective user ID of the process is not the "
				 "super-user.",
				 "The directory containing the file is marked "
				 "sticky, and neither the containing directory "
				 "nor the file to be removed are owned by the "
				 "effective user ID.")
	FAIL_SWITCH_ERRNO_CASE_1(EROFS,
				 "The named file resides on a read-only file "
				 "system.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'relative_path' does not specify an "
				 "absolute path and the 'directory_descriptor' "
				 "argument is neither 'AT_FDCWD' nor a valid "
				 "file descriptor open for searching.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTEMPTY,
				 "The 'unlink_flag' parameter has the '"
				 "AT_REMOVEDIR' bit set and the path argument "
				 "names a directory that is not an empty "
				 "directory.",
				 "There are hard links to the directory other "
				 "than 'dot' or a single entry in 'dot-dot'.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "The value of 'unlink_flag' is not valid.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
unlink_relative_handle(const int directory_descriptor,
		       const char *const restrict relative_path,
		       const int unlink_flag,
		       Handler *const handle,
		       void *arg)
{
	const char *restrict failure;

	if (unlink_relative_report(directory_descriptor,
				   relative_path,
				   unlink_flag,
				   &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
unlink_relative_handle_cl(const int directory_descriptor,
			  const char *const restrict relative_path,
			  const int unlink_flag,
			  const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (unlink_relative_report(directory_descriptor,
				   relative_path,
				   unlink_flag,
				   &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}
#endif /* ifndef WIN32 */

/* fetch info on a file */
inline bool
stat_status(const char *const restrict path,
	    struct StatBuffer *const restrict buffer)
{
	return stat_imp(path,
			buffer) == 0;
}

inline void
stat_muffle(const char *const restrict path,
	    struct StatBuffer *const restrict buffer)
{
	(void) stat_imp(path,
			buffer);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE stat_imp
inline bool
stat_report(const char *const restrict path,
	    struct StatBuffer *const restrict buffer,
	    const char *restrict *const restrict failure)
{

	FAIL_SWITCH_ERRNO_OPEN(path,
			       buffer)
	FAIL_SWITCH_ERRNO_CASE_1(EACCES,
				 "Search permission is denied for a component "
				 "of the path prefix.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'path' points to an invalid address.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "An I/O error occurs while reading from or "
				 "writing to the file system.")
	FAIL_SWITCH_ERRNO_CASE_1(ELOOP,
				 "Too many symbolic links are encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of a pathname exceeds {NAME_MAX} "
				 "characters, or an entire path name exceeds "
				 "{PATH_MAX} characters.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOENT,
				 "The named file does not exist.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOTDIR,
				 "A component of the path prefix is not a "
				 "directory.")
	FAIL_SWITCH_ERRNO_CASE_1(EOVERFLOW,
				 "The file size in bytes or the number of "
				 "blocks allocated to the file or the file "
				 "serial number cannot be represented correctly"
				 " in the structure pointed to by 'buffer'.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
stat_handle(const char *const restrict path,
	    struct StatBuffer *const restrict buffer,
	    Handler *const handle,
	    void *arg)
{
	const char *restrict failure;

	if (stat_report(path,
			buffer,
			&failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
stat_handle_cl(const char *const restrict path,
	       struct StatBuffer *const restrict buffer,
	       const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (stat_report(path,
			buffer,
			&failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* mkdir (absolute or relative path) */
inline bool
mkdir_status(const char *const restrict path,
	     const mode_t mode)
{
	return mkdir_imp(path,
			 mode) == 0;
}

inline void
mkdir_muffle(const char *const restrict path,
	     const mode_t mode)
{
	(void) mkdir_imp(path,
			 mode);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE mkdir_imp
inline bool
mkdir_report(const char *const restrict path,
	     const mode_t mode,
	     const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(path,
			       mode)
	FAIL_SWITCH_ERRNO_CASE_2(EACCES,
				 "Search permission is denied for a component "
				 "of the path prefix.",
				 "Write permission is denied for the parent "
				 "directory.")
	FAIL_SWITCH_ERRNO_CASE_2(EDQUOT,
				 "The new directory cannot be created because "
				 "the user's quota of disk blocks on the file "
				 "system that will contain the directory has "
				 "been exhausted.",
				 "The user's quota of inodes on the file system"
				 " on which the directory is being created has "
				 "been exhausted.")
	FAIL_SWITCH_ERRNO_CASE_1(EEXIST,
				 "The named file exists.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'path' points outside the process's allocated"
				 " address space.")
	FAIL_SWITCH_ERRNO_CASE_2(EIO,
				 "An I/O error occurred while making the "
				 "directory entry or allocating the inode.",
				 "An I/O error occurred while reading from or "
				 "writing to the file system.")
	FAIL_SWITCH_ERRNO_CASE_1(ELOOP,
				 "Too many symbolic links were encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(EMLINK,
				 "The parent directory already has {LINK_MAX} "
				 "links.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of a pathname exceeded {NAME_MAX}"
				 " characters, or an entire path name exceeded "
				 "{PATH_MAX} characters.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOENT,
				 "A component of the path prefix does not exist"
				 " or path is an empty string.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOSPC,
				 "The new directory cannot be created because "
				 "there is no space left on the file system "
				 "that would contain it.",
				 "There are no free inodes on the file system "
				 "on which the directory is being created.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOTDIR,
				 "A component of the path prefix is not a "
				 "directory.")
	FAIL_SWITCH_ERRNO_CASE_1(EROFS,
				 "The parent directory resides on a read-only "
				 "file system.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
mkdir_handle(const char *const restrict path,
	     const mode_t mode,
	     Handler *const handle,
	     void *arg)
{
	const char *restrict failure;

	if (mkdir_report(path,
			 mode,
			 &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
mkdir_handle_cl(const char *const restrict path,
		const mode_t mode,
		const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (mkdir_report(path,
			 mode,
			 &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}

#ifndef WIN32
/* mkdir (relative path) */
inline bool
mkdir_relative_status(const int directory_descriptor,
		      const char *const restrict relative_path,
		      const mode_t mode)
{
	return mkdir_relative_imp(directory_descriptor,
				  relative_path,
				  mode) == 0;
}

inline void
mkdir_relative_muffle(const int directory_descriptor,
		      const char *const restrict relative_path,
		      const mode_t mode)
{
	(void) mkdir_relative_imp(directory_descriptor,
				  relative_path,
				  mode);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE mkdir_relative_imp
inline bool
mkdir_relative_report(const int directory_descriptor,
		      const char *const restrict relative_path,
		      const mode_t mode,
		      const char *restrict *const restrict failure)

{
	FAIL_SWITCH_ERRNO_OPEN(directory_descriptor,
			       relative_path,
			       mode)
	FAIL_SWITCH_ERRNO_CASE_2(EACCES,
				 "Search permission is denied for a component "
				 "of the path prefix.",
				 "Write permission is denied for the parent "
				 "directory.")
	FAIL_SWITCH_ERRNO_CASE_2(EDQUOT,
				 "The new directory cannot be created because "
				 "the user's quota of disk blocks on the file "
				 "system that will contain the directory has "
				 "been exhausted.",
				 "The user's quota of inodes on the file system"
				 " on which the directory is being created has "
				 "been exhausted.")
	FAIL_SWITCH_ERRNO_CASE_1(EEXIST,
				 "The named directory exists.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'path' points outside the process's allocated"
				 " address space.")
	FAIL_SWITCH_ERRNO_CASE_2(EIO,
				 "An I/O error occurred while making the "
				 "directory entry or allocating the inode.",
				 "An I/O error occurred while reading from or "
				 "writing to the file system.")
	FAIL_SWITCH_ERRNO_CASE_1(ELOOP,
				 "Too many symbolic links were encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(EMLINK,
				 "The parent directory already has {LINK_MAX} "
				 "links.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of a pathname exceeded {NAME_MAX}"
				 " characters, or an entire path name exceeded "
				 "{PATH_MAX} characters.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOENT,
				 "A component of the path prefix does not exist"
				 " or path is an empty string.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOSPC,
				 "The new directory cannot be created because "
				 "there is no space left on the file system "
				 "that would contain it.",
				 "There are no free inodes on the file system "
				 "on which the directory is being created.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTDIR,
				 "A component of the path prefix is not a "
				 "directory.",
				 "'directory_descriptor' is neither 'AT_FDCWD' "
				 "nor a file descriptor associated with a "
				 "directory.")
	FAIL_SWITCH_ERRNO_CASE_1(EROFS,
				 "The parent directory resides on a read-only "
				 "file system.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'directory_descriptor' is neither 'AT_FDCWD' "
				 "nor a valid file descriptor open for "
				 "searching.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
mkdir_relative_handle(const int directory_descriptor,
		      const char *const restrict relative_path,
		      const mode_t mode,
		      Handler *const handle,
		      void *arg)
{
	const char *restrict failure;

	if (mkdir_relative_report(directory_descriptor,
				  relative_path,
				  mode,
				  &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
mkdir_relative_handle_cl(const int directory_descriptor,
			 const char *const restrict relative_path,
			 const mode_t mode,
			 const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (mkdir_relative_report(directory_descriptor,
				  relative_path,
				  mode,
				  &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}
#endif /* ifndef WIN32 */


/* chdir (absolute or relative path) */
inline bool
chdir_status(const char *const restrict path)
{
	return chdir_imp(path) == 0;
}

inline void
chdir_muffle(const char *const restrict path)
{
	(void) chdir_imp(path);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE chdir_imp
inline bool
chdir_report(const char *const restrict path,
	     const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(path)
	FAIL_SWITCH_ERRNO_CASE_1(EACCES,
				 "Search permission is denied for any component"
				 " of the path name.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'path' points outside the process's allocated"
				 " address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "An I/O error occurred while reading from or "
				 "writing to the file system.")
	FAIL_SWITCH_ERRNO_CASE_1(ELOOP,
				 "Too many symbolic links were encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of a pathname exceeded {NAME_MAX}"
				 " characters, or an entire path name exceeded "
				 "{PATH_MAX} characters.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOENT,
				 "The named directory does not exist.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOTDIR,
				 "A component of the path prefix is not a "
				 "directory.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
chdir_handle(const char *const restrict path,
	     Handler *const handle,
	     void *arg)
{
	const char *restrict failure;

	if (chdir_report(path,
			 &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
chdir_handle_cl(const char *const restrict path,
		const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (chdir_report(path,
			 &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* rmdir (absolute or relative path) */
inline bool
rmdir_status(const char *const restrict path)
{
	return rmdir_imp(path) == 0;
}

inline void
rmdir_muffle(const char *const restrict path)
{
	(void) rmdir_imp(path);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE rmdir_imp
inline bool
rmdir_report(const char *const restrict path,
	     const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(path)
	FAIL_SWITCH_ERRNO_CASE_2(EACCES,
				 "Search permission is denied for a component "
				 "of the path prefix.",
				 "Write permission is denied for the parent "
				 "directory.")
	FAIL_SWITCH_ERRNO_CASE_1(EBUSY,
				 "The directory to be removed is the mount "
				 "point for a mounted file system.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'path' points outside the process's allocated"
				 " address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "An I/O error occurred while making the "
				 "directory entry or deallocating the inode.")
	FAIL_SWITCH_ERRNO_CASE_1(ELOOP,
				 "Too many symbolic links were encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of a pathname exceeded {NAME_MAX}"
				 " characters, or an entire path name exceeded "
				 "{PATH_MAX} characters.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOENT,
				 "The named directory does not exists.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOTDIR,
				 "A component of the path is not a directory.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOTEMPTY,
				 "The named directory contains files other than"
				 " '.' and '..' in it.")
	FAIL_SWITCH_ERRNO_CASE_1(EPERM,
				 "The directory containing the directory to be "
				 "removed is marked sticky, and neither the "
				 "containing directory nor the directory to be "
				 "removed are owned by the effective user ID.")
	FAIL_SWITCH_ERRNO_CASE_1(EROFS,
				 "The directory entry to be removed resides on "
				 "a read-only file system.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
rmdir_handle(const char *const restrict path,
	     Handler *const handle,
	     void *arg)
{
	const char *restrict failure;

	if (rmdir_report(path,
			 &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
rmdir_handle_cl(const char *const restrict path,
		const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (rmdir_report(path,
			 &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}

#ifdef WIN32

/* TODO */
/* find first file in directory other than "." and ".."  */
inline enum BoolStatus
find_first_contents_status(HANDLE *const restrict file,
			   const char *const restrict path,
			   WIN32_FIND_DATA *const restrict info)
{
	HANDLE handle;

	handle = FindFirstFile(path,
			       info);

	if (handle == INVALID_HANDLE_VALUE)
		return BOOL_STATUS_ERROR;

	handle

}

#else
/* open a directory */
inline bool
opendir_status(DIR *restrict *const restrict dir,
	       const char *const restrict path)
{
	*dir = opendir(path);

	return *dir != NULL;
}

inline void
opendir_muffle(DIR *restrict *const restrict dir,
	       const char *const restrict path)
{
	*dir = opendir(path);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE opendir
inline bool
opendir_report(DIR *restrict *const restrict dir,
	       const char *const restrict path,
	       const char *restrict *const restrict failure)
{
	*dir = opendir(path);

	if (*dir != NULL)
		return true;

	switch (errno) {
	FAIL_SWITCH_ERRNO_CASE_1(EACCES,
				 "Search permission is denied for a component "
				 "of the path prefix.")
	FAIL_SWITCH_ERRNO_CASE_1(EAGAIN,
				 "'path' specifies the slave side of a locked "
				 "pseudo-terminal device.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'path' points outside the process's allocated"
				 " address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "The open() operation is interrupted by a "
				 "signal.")
	FAIL_SWITCH_ERRNO_CASE_2(ELOOP,
				 "Too many symbolic links are encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.",
				 "'O_NOFOLLOW' was specified and the target is "
				 "a symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(EMFILE,
				 "The process has already reached its limit for"
				 " open file descriptors.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of a pathname exceeds {NAME_MAX} "
				 "characters, or an entire path name exceeded "
				 "{PATH_MAX} characters.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOENT,
				 "The named directory does not exist.",
				 "A component of the path name that must exist "
				 "does not exist.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTDIR,
				 "A component of the path prefix is not a "
				 "directory.",
				 "The path argument is not an absolute path")
	FAIL_SWITCH_ERRNO_CASE_2(EOPNOTSUPP,
				 "'O_SHLOCK' or 'O_EXLOCK' is specified, but "
				 "the underlying filesystem does not support "
				 "locking.",
				 "An attempt is made to open a socket (not "
				 "currently implemented).")
	FAIL_SWITCH_ERRNO_CASE_1(EOVERFLOW,
				 "The named file is a regular file and its size"
				 " does not fit in an object of type 'off_t'.")
	FAIL_SWITCH_ERRNO_CASE_1(EROFS,
				 "The named file resides on a read-only file "
				 "system, and the file is to be modified.")
	FAIL_SWITCH_ERRNO_CASE_1(ETXTBSY,
				 "The file is a pure procedure (shared text) "
				 "file that is being executed and the open() "
				 "call requests write access.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "The path argument does not specify an "
				 "absolute path.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOMEM,
				 MALLOC_FAILURE_REASON)
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

inline void
opendir_handle(DIR *restrict *const restrict dir,
	       const char *const restrict path,
	       Handler *const handle,
	       void *arg)
{
	const char *restrict failure;

	if (opendir_report(dir,
			   path,
			   &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
opendir_handle_cl(DIR *restrict *const restrict dir,
		  const char *const restrict path,
		  const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (opendir_report(dir,
			   path,
			   &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* read next entry of a directory */
inline bool
readdir_status(DIR *const restrict dir,
	       struct dirent *restrict *const restrict entry)
{
	*entry = readdir(dir);

	return errno == 0;
}

inline void
readdir_muffle(DIR *const restrict dir,
	       struct dirent *restrict *const restrict entry)
{
	*entry = readdir(dir);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE readdir
inline bool
readdir_report(DIR *const restrict dir,
	       struct dirent *restrict *const restrict entry,
	       const char *restrict *const restrict failure)
{

	*entry = readdir(dir);

	if (errno == 0)
		return true;

	switch (errno) {
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "getdirentries failure - 'file_descriptor' is "
				 "not a valid file descriptor open for reading"
				 ".")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "getdirentries failure - Either 'buffer' or '"
				 "base_ptr' point outside the allocated address"
				 " space.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "getdirentries failure - An I/O error occurred"
				 " while reading from or writing to the file "
				 "system.")
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

inline void
readdir_handle(DIR *const restrict dir,
	       struct dirent *restrict *const restrict entry,
	       Handler *const handle,
	       void *arg)
{
	const char *restrict failure;

	if (readdir_report(dir,
			   entry,
			   &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
readdir_handle_cl(DIR *const restrict dir,
		  struct dirent *restrict *const restrict entry,
		  const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (readdir_report(dir,
			   entry,
			   &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}

/* close a directory */
inline bool
closedir_status(DIR *const restrict dir)
{
	return closedir(dir) == 0;
}

inline void
closedir_muffle(DIR *const restrict dir)
{
	(void) closedir(dir);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE closedir
inline bool
closedir_report(DIR *const restrict dir,
		const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(dir)
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'directory_descriptor' is not a valid, active"
				 " directory descriptor.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "Execution was interrupted by a signal.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "A previously-uncommitted write(2) encountered"
				 " an input/output error.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
closedir_handle(DIR *const restrict dir,
	       Handler *const handle,
	       void *arg)
{
	const char *restrict failure;

	if (closedir_report(dir,
			    &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();

}

inline void
closedir_handle_cl(DIR *const restrict dir,
		   const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (closedir_report(dir,
			    &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();

}

/* UNIX file tree traversal - open */
inline bool
fts_open_status(FTS *restrict *const restrict tree,
		char *const *path_argv,
		int options,
		int (*compare)(const FTSENT **,
			       const FTSENT **))
{
	*tree = fts_open(path_argv,
			 options,
			 compare);

	return *tree != NULL;
}

inline void
fts_open_muffle(FTS *restrict *const restrict tree,
		char *const *path_argv,
		const int options,
		int (*compare)(const FTSENT **,
			       const FTSENT **))
{
	*tree = fts_open(path_argv,
			 options,
			 compare);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE fts_open
inline bool
fts_open_report(FTS *restrict *const restrict tree,
		char *const *path_argv,
		const int options,
		int (*compare)(const FTSENT **,
			       const FTSENT **),
		const char *restrict *const restrict failure)
{
	*tree = fts_open(path_argv,
			 options,
			 compare);

	if (*tree != NULL)
		return true;

	switch (errno) {
	FAIL_SWITCH_ERRNO_CASE_1(EACCES,
				 "open failure - Search permission is denied "
				 "for a component of the path prefix.")
	FAIL_SWITCH_ERRNO_CASE_1(EAGAIN,
				 "open failure - 'path' specifies the slave "
				 "side of a locked pseudo-terminal device.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "open failure - 'path' points outside the "
				 "process's allocated address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "open failure - The open() operation is "
				 "interrupted by a signal.")
	FAIL_SWITCH_ERRNO_CASE_2(ELOOP,
				 "open failure - Too many symbolic links are "
				 "encountered in translating the pathname. This"
				 " is taken to be indicative of a looping "
				 "symbolic link.",
				 "'O_NOFOLLOW' was specified and the target is "
				 "a symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(EMFILE,
				 "open failure - The process has already "
				 "reached its limit for open file descriptors.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "open failure - A component of a pathname "
				 "exceeds {NAME_MAX} characters, or an entire "
				 "path name exceeded {PATH_MAX} characters.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOENT,
				 "open failure - The named directory does not "
				 "exist.",
				 "open failure - A component of the path name "
				 "that must exist does not exist.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTDIR,
				 "open failure - A component of the path prefix"
				 " is not a directory.",
				 "The path argument is not an absolute path")
	FAIL_SWITCH_ERRNO_CASE_2(EOPNOTSUPP,
				 "open failure - 'O_SHLOCK' or 'O_EXLOCK' is "
				 "specified, but the underlying filesystem does"
				 " not support locking.",
				 "An attempt is made to open a socket (not "
				 "currently implemented).")
	FAIL_SWITCH_ERRNO_CASE_1(EOVERFLOW,
				 "open failure - The named file is a regular "
				 "file and its size does not fit in an object "
				 "of type 'off_t'.")
	FAIL_SWITCH_ERRNO_CASE_1(EROFS,
				 "open failure - The named file resides on a "
				 "read-only file system, and the file is to be "
				 "modified.")
	FAIL_SWITCH_ERRNO_CASE_1(ETXTBSY,
				 "open failure - The file is a pure procedure ("
				 "shared text) file that is being executed and "
				 "the open() call requests write access.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "open failure - The path argument does not "
				 "specify an absolute path.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "'options' are invalid.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOMEM,
				 MALLOC_FAILURE_REASON)
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

inline void
fts_open_handle(FTS *restrict *const restrict tree,
		char *const *path_argv,
		const int options,
		int (*compare)(const FTSENT **,
			       const FTSENT **),
		Handler *const handle,
		void *arg)
{
	const char *restrict failure;

	if (fts_open_report(tree,
			    path_argv,
			    options,
			    compare,
			    &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
fts_open_handle_cl(FTS *restrict *const restrict tree,
		   char *const *path_argv,
		   const int options,
		   int (*compare)(const FTSENT **,
				  const FTSENT **),
		   const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (fts_open_report(tree,
			    path_argv,
			    options,
			    compare,
			    &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* close FTS */
inline bool
fts_close_status(FTS *const restrict tree)
{
	return fts_close(tree) == 0;
}

inline void
fts_close_muffle(FTS *const restrict tree)
{
	(void) fts_close(tree);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE fts_close
inline bool
fts_close_report(FTS *const restrict tree,
		 const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(tree)
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "close failure - 'directory_descriptor' is not"
				 " a valid, active directory descriptor.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "close failure - Execution was interrupted by "
				 "a signal.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "close failure - A previously-uncommitted "
				 "write(2) encountered an input/output error.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
fts_close_handle(FTS *const restrict tree,
		 Handler *const handle,
		 void *arg)
{
	const char *restrict failure;

	if (fts_close_report(tree,
			     &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
fts_close_handle_cl(FTS *const restrict tree,
		    const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (fts_close_report(tree,
			     &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* read next entry in FTS */
inline bool
fts_read_status(FTSENT *restrict *const restrict entry,
		FTS *const restrict tree)
{
	*entry = fts_read(tree);

	if (*entry == NULL)
		return errno == 0;

	switch ((*entry)->fts_info) {
	case FTS_DNR:
	case FTS_ERR:
	case FTS_NS:
		return false;
	default:
		return true;
	}
}

inline void
fts_read_muffle(FTSENT *restrict *const restrict entry,
		FTS *const restrict tree)
{
	*entry = fts_read(tree);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE fts_read
inline bool
fts_read_report(FTSENT *restrict *const restrict entry,
		FTS *const restrict tree,
		const char *restrict *const restrict failure)
{
	*entry = fts_read(tree);

	if (*entry == NULL) {
		if (errno == 0)
			return true;

		*failure = strerror(errno);
		return false;
	}

	switch ((*entry)->fts_info) {
	case FTS_DNR:
		switch ((*entry)->fts_errno) {
		FAIL_SWITCH_ERRNO_CASE_1(EBADF,
					 "readdir failure - 'file_descriptor' "
					 "is not a valid file descriptor open "
					 "for reading.")
		FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
					 "readdir failure - Either 'buffer' or "
					 "'base_ptr' point outside the "
					 "allocated address space.")
		FAIL_SWITCH_ERRNO_CASE_1(EIO,
					 "readdir failure - An I/O error "
					 "occurred while reading from or "
					 "writing to the file system.")
		FAIL_SWITCH_ERRNO_DEFAULT_CASE()
		}
	case FTS_ERR:
		switch ((*entry)->fts_errno) {
		FAIL_SWITCH_ERRNO_CASE_1(EACCES,
					 "ch|opendir failure - Search "
					 "permission is denied for any "
					 "component of the path name.")
		FAIL_SWITCH_ERRNO_CASE_1(EAGAIN,
					 "opendir failure - 'path' specifies "
					 "the slave side of a locked "
					 "pseudo-terminal device.")
		FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
					 "ch|opendir failure - 'path' points "
					 "outside the process's allocated "
					 "address space.")
		FAIL_SWITCH_ERRNO_CASE_1(EINTR,
					 "opendir failure - The open() "
					 "operation is interrupted by a signal"
					 ".")
		FAIL_SWITCH_ERRNO_CASE_2(ELOOP,
					 "ch|opendir failure - Too many "
					 "symbolic links are encountered in "
					 "translating the pathname. This is "
					 "taken to be indicative of a looping "
					 "symbolic link.",
					 "opendir failure - 'O_NOFOLLOW' was "
					 "specified and the target is a "
					 "symbolic link.")
		FAIL_SWITCH_ERRNO_CASE_1(EMFILE,
					 "opendir failure - The process has "
					 "already reached its limit for open "
					 "file descriptors.")
		FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
					 "ch|opendir failure - A component of a"
					 " pathname exceeds {NAME_MAX} "
					 "characters, or an entire path name "
					 "exceeded {PATH_MAX} characters.")
		FAIL_SWITCH_ERRNO_CASE_2(ENOENT,
					 "ch|opendir failure - The named "
					 "directory does not exist.",
					 "opendir failure - A component of the "
					 "path name that must exist does not "
					 "exist.")
		FAIL_SWITCH_ERRNO_CASE_2(ENOTDIR,
					 "ch|opendir failure - A component of "
					 "the path prefix is not a directory.",
					 "opendir failure - The path argument "
					 "is not an absolute path")
		FAIL_SWITCH_ERRNO_CASE_2(EOPNOTSUPP,
					 "opendir failure - 'O_SHLOCK' or "
					 "'O_EXLOCK' is specified, but the "
					 "underlying filesystem does not "
					 "support locking.",
					 "opendir failure - An attempt is made "
					 "to open a socket (not currently "
					 "implemented).")
		FAIL_SWITCH_ERRNO_CASE_1(EOVERFLOW,
					 "opendir failure - The named file is a"
					 " regular file and its size does not "
					 "fit in an object of type 'off_t'.")
		FAIL_SWITCH_ERRNO_CASE_1(EROFS,
					 "opendir failure - The named file "
					 "resides on a read-only file system, "
					 "and the file is to be modified.")
		FAIL_SWITCH_ERRNO_CASE_1(ETXTBSY,
					 "opendir failure - The file is a pure "
					 "procedure (shared text) file that is "
					 "being executed and the open() call "
					 "requests write access.")
		FAIL_SWITCH_ERRNO_CASE_1(EBADF,
					 "opendir failure - The path argument "
					 "does not specify an absolute path.")
		FAIL_SWITCH_ERRNO_CASE_1(EIO,
					 "chdir failure - An I/O error occurred"
					 " while reading from or writing to the"
					 " file system.")
		FAIL_SWITCH_ERRNO_CASE_1(ENOMEM,
					 MALLOC_FAILURE_REASON)
		FAIL_SWITCH_ERRNO_DEFAULT_CASE()
		}
	case FTS_NS:
		switch ((*entry)->fts_errno) {
		FAIL_SWITCH_ERRNO_CASE_1(EACCES,
					 "stat failure - Search permission is "
					 "denied for a component of the path "
					 "prefix.")
		FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
					 "stat failure - 'path' points to an "
					 "invalid address.")
		FAIL_SWITCH_ERRNO_CASE_1(EIO,
					 "stat failure - An I/O error occurs "
					 "while reading from or writing to the "
					 "file system.")
		FAIL_SWITCH_ERRNO_CASE_1(ELOOP,
					 "stat failure - Too many symbolic "
					 "links are encountered in translating "
					 "the pathname. This is taken to be "
					 "indicative of a looping symbolic link"
					 ".")
		FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
					 "stat failure - A component of a "
					 "pathname exceeds {NAME_MAX} "
					 "characters, or an entire path name "
					 "exceeds {PATH_MAX} characters.")
		FAIL_SWITCH_ERRNO_CASE_1(ENOENT,
					 "stat failure - The named file does "
					 "not exist.")
		FAIL_SWITCH_ERRNO_CASE_1(ENOTDIR,
					 "stat failure - A component of the "
					 "path prefix is not a directory.")
		FAIL_SWITCH_ERRNO_CASE_1(EOVERFLOW,
					 "stat failure - The file size in bytes"
					 " or the number of blocks allocated to"
					 " the file or the file serial number "
					 "cannot be represented correctly in "
					 "the structure pointed to by 'buffer'"
					 ".")
		FAIL_SWITCH_ERRNO_DEFAULT_CASE()
		}
	default:
		return true;
	}
}

inline void
fts_read_handle(FTSENT *restrict *const restrict entry,
		FTS *const restrict tree,
		Handler *const handle,
		void *arg)
{
	const char *restrict failure;

	if (fts_read_report(entry,
			    tree,
			    &failure))
		return;

	fts_close_muffle(tree);

	handle(arg,
	       failure);
	__builtin_unreachable();
}


inline void
fts_read_handle_cl(FTSENT *restrict *const restrict entry,
		   FTS *const restrict tree,
		   const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (fts_read_report(entry,
			    tree,
			    &failure))
		return;

	fts_close_muffle(tree);

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* set entry in FTS */
inline bool
fts_set_status(FTS *const restrict tree,
	       FTSENT *const restrict entry,
	       const int options)
{
	return fts_set(tree,
		       entry,
		       options) == 0;
}

inline void
fts_set_muffle(FTS *const restrict tree,
	       FTSENT *const restrict entry,
	       const int options)
{
	(void) fts_set(tree,
		       entry,
		       options);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE fts_set
inline bool
fts_set_report(FTS *const restrict tree,
	       FTSENT *const restrict entry,
	       const int options,
	       const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(tree,
			       entry,
			       options)
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "invalid 'options' (i.e. not one of 'FTS_AGAIN"
				 "', 'FTS_FOLLOW', or 'FTS_SKIP')")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
fts_set_handle(FTS *const restrict tree,
	       FTSENT *const restrict entry,
	       const int options,
	       Handler *const handle,
	       void *arg)
{
	const char *restrict failure;

	if (fts_set_report(tree,
			   entry,
			   options,
			   &failure))
		return;

	fts_close_muffle(tree);

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
fts_set_handle_cl(FTS *const restrict tree,
		  FTSENT *const restrict entry,
		  const int options,
		  const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (fts_set_report(tree,
			   entry,
			   options,
			   &failure))
		return;

	fts_close_muffle(tree);

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* compare FTS entries by name */
inline int
ftsent_compare_names(const FTSENT **x,
		     const FTSENT **y)
{
	return string_compare((*x)->fts_name,
			      (*y)->fts_name);
}
#endif /* ifdef WIN32 */


/* inspect file permissions (10 chars long) */
inline char *
put_file_permissions_string(char *restrict buffer,
			    const int mode)
{
	PUT_CHAR(buffer, (S_ISDIR(mode))  ? 'd' : '-');
	PUT_CHAR(buffer, (mode & S_IRUSR) ? 'r' : '-');
	PUT_CHAR(buffer, (mode & S_IWUSR) ? 'w' : '-');
	PUT_CHAR(buffer, (mode & S_IXUSR) ? 'x' : '-');
	PUT_CHAR(buffer, (mode & S_IRGRP) ? 'r' : '-');
	PUT_CHAR(buffer, (mode & S_IWGRP) ? 'w' : '-');
	PUT_CHAR(buffer, (mode & S_IXGRP) ? 'x' : '-');
	PUT_CHAR(buffer, (mode & S_IROTH) ? 'r' : '-');
	PUT_CHAR(buffer, (mode & S_IWOTH) ? 'w' : '-');
	PUT_CHAR(buffer, (mode & S_IXOTH) ? 'x' : '-');

	return buffer;
}

/* buffer must have space for 11 chars */
inline void
file_permissions_string(char *restrict buffer,
			const int mode)
{
	buffer  = put_file_permissions_string(buffer,
					      mode);
	*buffer = '\0';
}

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS
 *
 *
 * HELPER FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER FUNCTIONS */

/* clear FAIL_SWITCH constant macros */
#undef FAIL_SWITCH_ROUTINE
#undef FAIL_SWITCH_ERRNO_FAILURE
#undef FAIL_SWITCH_FAILURE_POINTER

#endif /* ifndef MYSQL_SEED_SYSTEM_FILE_UTILS_H_ */
