#ifndef MYSQL_SEED_SYSTEM_FILE_UTILS_H_
#define MYSQL_SEED_SYSTEM_FILE_UTILS_H_

/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <fcntl.h>		    /* open */
#include <unistd.h>		    /* close, getcwd, STDOUT/IN/ERR_FILENO */
#include "utils/utils.h"	    /* FILE/stream API */
#include "system/system_utils.h"    /* sys headers, FAIL_SWITCH, misc macros */

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

/* CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS
 *
 *
 * FUNCTION-LIKE MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#ifdef WIN32
/* open a file */
#	define open_absolute_imp(ABSOLUTE_PATH,				\
				 OPEN_FLAG)				\
	_open(ABSOLUTE_PATH, OPEN_FLAG)
#	define open_absolute_mode_imp(ABSOLUTE_PATH,			\
				      OPEN_FLAG,			\
				      MODE)				\
	_open(ABSOLUTE_PATH, OPEN_FLAG, MODE)
#	undef open_relative_imp
#	warning "open_relative undefined"
#	undef open_relative_mode_imp
#	warning "open_relative_mode undefined"

/* close a file */
#	define close_imp(FILE_DESCRIPTOR)				\
	_close(FILE_DESCRIPTOR)
#	define close_imp(FILE_DESCRIPTOR)				\

/* make a directory */
#	define mkdir_absolute_imp(ABSOLUTE_PATH,			\
				  MODE)					\
	_mkdir(ABSOLUTE_PATH)
#	undef mkdir_relative_imp
#	warning "mkdir_relative undefined"

/* delete a file */
#	define unlink_absolute_imp(ABSOLUTE_PATH)			\
	_unlink(ABSOLUTE_PATH)
#	undef unlink_relative_imp
#	warning "unlink_relative undefined"

/* delete a directory */
#	define rmdir_absolute_imp(ABSOLUTE_PATH)
	_rmdir(ABSOLUTE_PATH)

#else
/* open a file */
#	define open_absolute_imp(ABSOLUTE_PATH,				\
				 OPEN_FLAG)				\
	open(ABSOLUTE_PATH, OPEN_FLAG)
#	define open_absolute_mode_imp(ABSOLUTE_PATH,			\
				      OPEN_FLAG,			\
				      MODE)				\
	open(ABSOLUTE_PATH, OPEN_FLAG, MODE)
#	define open_relative_imp(DIRECTORY_DESCRIPTOR,			\
				      RELATIVE_PATH,			\
				      OPEN_FLAG)			\
	openat(DIRECTORY_DESCRIPTOR, RELATIVE_PATH, OPEN_FLAG)
#	define open_relative_mode_imp(DIRECTORY_DESCRIPTOR,		\
				      RELATIVE_PATH,			\
				      OPEN_FLAG,			\
				      MODE)				\
	openat(DIRECTORY_DESCRIPTOR, RELATIVE_PATH, OPEN_FLAG, MODE)

/* close a file */
#	define close_imp(FILE_DESCRIPTOR)				\
	close(FILE_DESCRIPTOR)

/* make a directory */
#	define mkdir_absolute_imp(ABSOLUTE_PATH,			\
				  MODE)					\
	mkdir(ABSOLUTE_PATH, MODE)
#	define mkdir_relative_imp(DIRECTORY_DESCRIPTOR,			\
				  RELATIVE_PATH				\
				  MODE)					\
	mkdirat(DIRECTORY_DESCRIPTOR, RELATIVE_PATH, MODE)

/* delete a file */
#	define unlink_absolute_imp(ABSOLUTE_PATH)			\
	unlink(ABSOLUTE_PATH)
#	define unlink_relative_imp(DIRECTORY_DESCRIPTOR,		\
				   RELATIVE_PATH			\
				   UNLINK_FLAG)				\
	unlinkat(DIRECTORY_DESCRIPTOR, RELATIVE_PATH, UNLINK_FLAG)
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

/* write */
inline bool
write_status(const int file_descriptor,
	     const void *const restrict buffer,
	     const size_t size)
{
	return write(file_descriptor,
		     buffer,
		     size) != -1;
}

inline void
write_muffle(const int file_descriptor,
	     const void *const restrict buffer,
	     const size_t size)
{
	(void) write(file_descriptor,
		     buffer,
		     size);
}

#define FAIL_SWITCH_ROUTINE write
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
	FAIL_SWITCH_ERRNO_CLOSE()
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


/* open (absolute path, no mode) */
inline bool
open_absolute_status(const char *const absolute_path,
		     const int open_flag)
{
	return open_absolute_imp(absolute_path,
				 open_flag) >= 0;
}

inline void
open_absolute_muffle(const char *const absolute_path,
		     const int open_flag)
{
	(void) open_absolute_imp(absolute_path,
				 open_flag);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE open_absolute_imp
inline bool
open_absolute_report(const char *const absolute_path,
		     const int open_flag,
		     const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(absolute_path,
			       open_flag)
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
				 "Path points outside the process's allocated "
				 "address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "The open_absolute() operation is interrupted "
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
				 "open_absolute() call requests write access.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "The path argument does not specify an "
				 "absolute path.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
open_absolute_handle(const char *const absolute_path,
		     const int open_flag,
		     Handler *const handle,
		     void *arg)
{
	const char *restrict failure;

	if (open_absolute_report(absolute_path,
				 open_flag,
				 &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
open_absolute_handle_cl(const char *const absolute_path,
			const int open_flag,
			const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (open_absolute_report(absolute_path,
				 open_flag,
				 &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}


/* open (absolute path, provide mode) */
inline bool
open_absolute_mode_status(const char *const absolute_path,
			  const int open_flag,
			  const mode_t mode)
{
	return open_absolute_mode_imp(absolute_path,
				      open_flag,
				      mode) >= 0;
}

inline void
open_absolute_mode_muffle(const char *const absolute_path,
			  const int open_flag,
			  const mode_t mode)
{
	(void) open_absolute_mode_imp(absolute_path,
				      open_flag,
				      mode);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE open_absolute_mode_imp
inline bool
open_absolute_mode_report(const char *const absolute_path,
			  const int open_flag,
			  const mode_t mode,
			  const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(absolute_path,
			       open_flag,
			       mode)
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
				 "Path points outside the process's allocated "
				 "address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "The open_absolute_mode() operation is "
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
				 "open_absolute_mode() call requests write "
				 "access.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "The path argument does not specify an "
				 "absolute path.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
open_absolute_mode_handle(const char *const absolute_path,
			  const int open_flag,
			  const mode_t mode,
			  Handler *const handle,
			  void *arg)
{
	const char *restrict failure;

	if (open_absolute_mode_report(absolute_path,
				      open_flag,
				      mode,
				      &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
open_absolute_mode_handle_cl(const char *const absolute_path,
			     const int open_flag,
			     const mode_t mode,
			     const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (open_absolute_mode_report(absolute_path,
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
open_relative_status(const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag)
{
	return open_relative_imp(directory_descriptor,
		      relative_path,
		      open_flag) >= 0;
}

inline void
open_relative_muffle(const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag)
{
	(void) open_relative_imp(directory_descriptor,
		      relative_path,
		      open_flag);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE open_relative_imp
inline bool
open_relative_report(const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag,
		     const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(directory_descriptor,
			       relative_path,
			       open_flag)
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
				 "Path points outside the process's allocated "
				 "address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINTR,
				 "The open_relative() operation is interrupted by a "
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
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
open_relative_handle(const int directory_descriptor,
		     const char *const relative_path,
		     const int open_flag,
		     Handler *const handle,
		     void *arg)
{
	const char *restrict failure;

	if (open_relative_report(directory_descriptor,
				 relative_path,
				 open_flag,
				 &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
open_relative_handle_cl(const int directory_descriptor,
			const char *const relative_path,
			const int open_flag,
			const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (open_relative_report(directory_descriptor,
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
open_relative_mode_status(const int directory_descriptor,
			  const char *const relative_path,
			  const int open_flag,
			  const mode_t mode)
{
	return open_relative_mode_imp(directory_descriptor,
				      relative_path,
				      open_flag,
				      mode) >= 0;
}

inline void
open_relative_mode_muffle(const int directory_descriptor,
			  const char *const relative_path,
			  const int open_flag,
			  const mode_t mode)
{
	(void) open_relative_mode_imp(directory_descriptor,
				      relative_path,
				      open_flag,
				      mode);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE open_relative_mode_imp
inline bool
open_relative_mode_report(const int directory_descriptor,
			  const char *const relative_path,
			  const int open_flag,
			  const mode_t mode,
			  const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(directory_descriptor,
			       relative_path,
			       open_flag,
			       mode)
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
				 "Path points outside the process's allocated "
				 "address space.")
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
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
open_relative_mode_handle(const int directory_descriptor,
			  const char *const relative_path,
			  const int open_flag,
			  const mode_t mode,
			  Handler *const handle,
			  void *arg)
{
	const char *restrict failure;

	if (open_relative_mode_report(directory_descriptor,
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
open_relative_mode_handle_cl(const int directory_descriptor,
			     const char *const relative_path,
			     const int open_flag,
			     const mode_t mode,
			     const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (open_relative_mode_report(directory_descriptor,
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


/* mkdir (absolute path) */
inline bool
mkdir_absolute_status(const char *const restrict absolute_path,
		      const mode_t mode)
{
	return mkdir_absolute_imp(absolute_path,
				  mode) == 0;
}

inline void
mkdir_absolute_muffle(const char *const restrict absolute_path,
		      const mode_t mode)
{
	(void) mkdir_absolute_imp(absolute_path,
				  mode);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE mkdir_absolute_imp
inline bool
mkdir_absolute_report(const char *const restrict absolute_path,
		      const mode_t mode,
		      const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(absolute_path,
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
				 "Path points outside the process's allocated "
				 "address space.")
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
mkdir_absolute_handle(const char *const restrict absolute_path,
		      const mode_t mode,
		      Handler *const handle,
		      void *arg)
{
	const char *restrict failure;

	if (mkdir_absolute_report(absolute_path,
				  mode,
				  &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
mkdir_absolute_handle_cl(const char *const restrict absolute_path,
			 const mode_t mode,
			 const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (mkdir_absolute_report(absolute_path,
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
				 "The named file exists.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "Path points outside the process's allocated "
				 "address space.")
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


/* unlink (absolute path) */
inline bool
unlink_absolute_status(const char *const restrict absolute_path)
{
	return unlink_absolute_imp(absolute_path) == 0;
}

inline void
unlink_absolute_muffle(const char *const restrict absolute_path)
{
	(void) unlink_absolute_imp(absolute_path);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE unlink_absolute_imp
inline void
unlink_absolute_report(const char *const restrict absolute_path,
		       const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(absolute_path)
	FAIL_SWITCH_ERRNO_CASE_2(EACCES,
				 "Search permission is denied for a component "
				 "of the path prefix.",
				 "Write permission is denied on the directory "
				 "containing the link to be removed.")
	FAIL_SWITCH_ERRNO_CASE_2(EBUSY,
				 "The entry to be unlinked is the mount point "
				 "for a mounted file system.",
				 "The file named by 'absolute_path' cannot be "
				 "unlinked because it is being used by the "
				 "system or by another process.")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'absolute_path' points outside the process's "
				 "allocated address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EIO,
				 "An I/O error occurred while deleting the "
				 "directory entry or deallocating the inode.")
	FAIL_SWITCH_ERRNO_CASE_1(ELOOP,
				 "Too many symbolic links are encountered in "
				 "translating the pathname. This is taken to be"
				 " indicative of a looping symbolic link.")
	FAIL_SWITCH_ERRNO_CASE_1(ENAMETOOLONG,
				 "A component of 'absolute_path' exceeds "
				 "{NAME_MAX} characters, or an entire path name"
				 " exceeds {PATH_MAX} characters (possibly as a"
				 " result of expanding a symlink).")
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
unlink_absolute_handle(const char *const restrict absolute_path,
		       Handler *const handle,
		       void *arg)
{
	const char *restrict failure;

	if (unlink_absolute_report(absolute_path,
				   &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
unlink_absolute_handle_cl(const char *const restrict absolute_path,
			  const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (unlink_absolute_report(absolute_path,
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
	return unlink_relative_imp(relative_path) == 0;
}

inline void
unlink_relative_muffle(const int directory_descriptor,
		       const char *const restrict relative_path,
		       const int unlink_flag)
{
	(void) unlink_relative_imp(relative_path);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE unlink_relative_imp
inline void
unlink_relative_report(const int directory_descriptor,
		       const char *const restrict relative_path,
		       const int unlink_flag,
		       const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(relative_path)
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
	FAIL_SWITCH_ERRNO_CASE_2(ENOTDIR,
				 "The 'unlink_flag' parameter has the '"
				 "AT_REMOVEDIR' bit set and 'relative_path' "
				 "does not name a directory.",
				 "'relative_path' is not an absolute path and '"
				 "directory_descriptor' is neither 'AT_FDCWD' "
				 "nor a file descriptor associated with a "
				 "directory.")
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

	if (unlink_relative_report(relative_path,
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

	if (unlink_relative_report(relative_path,
				   &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}
#endif /* ifndef WIN32 */



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
