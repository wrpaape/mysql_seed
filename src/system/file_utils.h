#ifndef MYSQL_SEED_SYSTEM_FILE_UTILS_H_
#define MYSQL_SEED_SYSTEM_FILE_UTILS_H_

/* EXTERNAL DEPENDENCIES ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <utils/utils.h>	/* EXIT_ON_FAILURE, FILE/stream API */
#include <fcntl.h>		/* open */
#include <unistd.h>		/* close, getcwd, STDOUT/IN/ERR_FILENO */
#include "system/system_utils"	/* <sys/uio|types|stat|param.h> */

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

/* CONSTANTS ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲ */

/* FUNCTION-LIKE MACROS ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#undef PUT_CHAR
#define PUT_CHAR(PTR, CHAR)	\
do {				\
	*PTR = CHAR;		\
	++PTR;			\
} while (0)

#ifdef _WIN32	/* use backslashes for windows enviroment */
#	define PUT_FILE_DELIM(PTR) PUT_CHAR(PTR, '\\')
#else
#	define PUT_FILE_DELIM(PTR) PUT_CHAR(PTR, '/')
#endif

/* error handlers
 * ========================================================================== */

/* HANDLE_OPEN, HANDLE_OPENAT ───────────────────────────────────────────────
 * open */
#define HANDLE_OPEN(FILDES, PATH, OFLAG, ...)				\
do {									\
	FILDES = open(PATH, OFLAG, ##__VA_ARGS__);			\
	if (FILDES == -1)						\
		EXIT_ON_FAILURE("failed to open file"			\
				"\e24m]\n\n{\n"				\
				"\tfildes: '" #FILDES "' (%d),\n"	\
				"\tpath:   '" #PATH   "' (%s),\n"	\
				"\toflag:  '" #OFLAG  "' (%o) %s\n"	\
				"}\n\n"					\
				"reason: %s",				\
				FILDES,					\
				PATH,					\
				OFLAG,					\
				CLASSIFY_FILE_OFLAG(OFLAG),		\
				OPEN_FAILURE(errno));			\
} while (0)
#define OPEN_FAILURE(ERRNO)						\
  ((ERRNO == EACCES)							\
? "(one of the following)\n"						\
  "\t- Search permission is denied for a component of the path \n"	\
  "prefix."								\
  "\t- The required permissions (for reading and/or writing) are "	\
  "denied for the given flags.\n"					\
  "\t- 'O_CREAT' is specified, the file does not exist, and the "	\
  "directory in which it is to be created does not permit writing.\n"	\
  "\t- 'O_TRUNC' is specified and write permission is denied."		\
: ((ERRNO == EAGAIN)							\
? "'path' specifies the slave side of a locked pseudo-terminal device."	\
: ((ERRNO == EDQUOT)							\
? "(one of the following)\n"						\
  "\t- 'O_CREAT' is specified, the file does not exist, and the "	\
  "directory in which the entry for the new file is being placed "	\
  "cannot be extended because the user's quota of disk blocks on the "	\
  "file system containing the directory has been exhausted.\n"		\
  "\t- 'O_CREAT' is specified, the file does not exist, and the user's"	\
  " quota of inodes on the file system on which the file is being "	\
  "created has been exhausted."						\
: ((ERRNO == EEXIST)							\
? "'O_CREAT' and 'O_EXCL' are specified and the file exists."		\
: ((ERRNO == EFAULT)							\
? "'path' points outside the process's allocated address space."	\
: ((ERRNO == EINTR)							\
? "The 'open' operation is interrupted by a signal."			\
: ((ERRNO == EINVAL)							\
? "The value of 'oflag' is not valid."					\
: ((ERRNO == EIO)							\
? "An I/O error occured while making the directory entry or allocating"	\
  " the inode for 'O_CREAT'."						\
: ((ERRNO == EISDIR)							\
? "The named file is a directory, and the arguments specify that it is"	\
  " to be opened for writing."						\
: ((ERRNO == ELOOP)							\
? "(one of the following)\n"						\
  "\t- Too many symbolic links are encountered in translating the "	\
  "pathname.  This is taken to be indicative of a looping symbolic "	\
  "link.\n"								\
  "\t- 'O_NOFOLLOW' was specified and the target is a symbolic link."	\
: ((ERRNO == EMFILE)							\
? "The process has already reached its limit for open file "		\
  "descriptors."							\
: ((ERRNO == ENAMETOOLONG)						\
? "A component of a pathname exceeds {NAME_MAX} characters, or an "	\
  "entire path name exceeded {PATH_MAX} characters."			\
: ((ERRNO == ENFILE)							\
? "The system file table is full."					\
: ((ERRNO == ENOENT)							\
? "(one of the following)\n"						\
  "\t- 'O_CREAT' is not set and the named file does not exist.\n"	\
  "\t- A component of the path name that must exist does not exist."	\
: ((ERRNO == ENOSPC)							\
? "(one of the following)\n"						\
  "\t- 'O_CREAT' is specified, the file does not exist, and the "	\
  "directory in which the entry for the new file is being placed "	\
  "cannot be extended because there is no space left on the file "	\
  "system containing the directory.\n"					\
  "\t- 'O_CREAT' is specified, the file does not exist, and there are "	\
  "no free inodes on the file system on which the file is being "	\
  "created."								\
: ((ERRNO == ENOTDIR)							\
? "A component of the path prefix is not a directory."			\
: ((ERRNO == ENXIO)							\
? "(one of the following)\n"						\
  "\t- The named file is a character-special or block-special file and"	\
  " the device associated with this special file does not exist.\n"	\
  "\t- 'O_NONBLOCK' and 'O_WRONLY' are set, the file is a FIFO, and no"	\
  " process has it open for reading."					\
: ((ERRNO == EOPNOTSUPP)						\
? "(one of the following)\n"						\
  "\t- 'O_SHLOCK' or 'O_EXLOCK' is specified, but the underlying "	\
  "filesystem does not support locking.\n"				\
  "\t- An attempt is made to open a socket (not currently "		\
  "implemented)."							\
: ((ERRNO == EOVERFLOW)							\
? "The named file is a regular file and its size does not fit in an "	\
  "object of type off_t."						\
: ((ERRNO == EROFS)							\
? "The named file resides on a read-only file system, and the file is "	\
  "to be modified."							\
: ((ERRNO == ETXTBSY)							\
? "The file is a pure procedure (shared text) file that is being "	\
  "executed and the open() call requests write access."			\
: ((ERRNO == EBADF)							\
? "The 'path' argument does not specify an absolute path and the 'fd' "	\
  "argument is neither 'AT_FDCWD' nor a valid file descriptor open for"	\
  " searching."								\
: ((ERRNO == ENOTDIR)							\
? "The 'path' argument is not an absolute path and 'fd' is neither "	\
  "'AT_FDCWD' nor a file descriptor associated with a directory."	\
: "unknown")))))))))))))))))))))))

/* openat */
#define HANDLE_OPENAT(FILDES, FD, PATH, OFLAG, ...)			\
do {									\
	FILDES = openat(FD, PATH, OFLAG, ##__VA_ARGS__);		\
	if (FILDES == -1)						\
		EXIT_ON_FAILURE("failed to open file"			\
				"\e24m]\n\n{\n"				\
				"\tfd:     '" #FD     "' (%d),\n"	\
				"\tpath:   '" #PATH   "' (%s),\n"	\
				"\toflag:  '" #OFLAG  "' (%o) %s\n"	\
				"}\n\n"					\
				"reason: %s",				\
				FD,					\
				PATH,					\
				OFLAG,					\
				CLASSIFY_FILE_OFLAG(OFLAG),		\
				OPENAT_FAILURE(errno));			\
} while (0)
#define OPENAT_FAILURE(ERRNO) OPEN_FAILURE(ERRNO)

/* HANDLE_READ, HANDLE_PREAD, HANDLE_READV ──────────────────────────────────
 * read */
#define HANDLE_READ(NREAD, FILDES, BUF, NBYTE)				\
do {									\
	NREAD = read(FILDES, BUF, NBYTE);				\
	if (NREAD == -1l)						\
		EXIT_ON_FAILURE("failed to read from file"		\
				"\e24m]\n\n{\n"				\
				"\tnread:  '" #NREAD  "' (-1),\n"	\
				"\tfildes: '" #FILDES "' (%d),\n"	\
				"\tbuf:    '" #BUF    "' (%p),\n"	\
				"\tnbyte:  '" #NBYTE  "' (%zu)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				FILDES,					\
				BUF,					\
				NBYTE,					\
				READ_FAILURE(errno));			\
} while (0)
#define READ_FAILURE(ERRNO)						\
READ_PREAD_READV_FAILURE(ERRNO,						\
			 READ_EINVAL_REASON,				\
   ((ERRNO == ECONNRESET)						\
? "The connection is closed by the peer during a read attempt on a "	\
  "socket."								\
:  ((ERRNO == ENOTCONN)							\
? "A read is attempted on an unconnected socket."			\
:  ((ERRNO == ETIMEDOUT)						\
? "A transmission timeout occurs during a read attempt on a socket."	\
: "unknown"))))

/* pread */
#define HANDLE_PREAD(NREAD, D, BUF, NBYTE, OFFSET)			\
do {									\
	NREAD = pread(D, BUF, NBYTE, OFFSET);				\
	if (NREAD == -1l)						\
		EXIT_ON_FAILURE("failed to read from file"		\
				"\e24m]\n\n{\n"				\
				"\tnread:   '" #NREAD  "' (-1),\n"	\
				"\td:       '" #D      "' (%d),\n"	\
				"\tbuf:     '" #BUF    "' (%p),\n"	\
				"\tnbyte:   '" #NBYTE  "' (%zu),\n"	\
				"\tnoffset: '" #OFFSET "' (%jd)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				FILDES,					\
				BUF,					\
				NBYTE,					\
				OFFSET,					\
				PREAD_FAILURE(errno));			\
} while (0)
#define PREAD_FAILURE(ERRNO)						\
READ_PREAD_READV_FAILURE(ERRNO,						\
			 PREAD_EINVAL_REASON,				\
  ((ERRNO == ESPIPE)							\
? "The file descriptor is associated with a pipe, socket, or FIFO."	\
: "unkown"))

/* read */
#define HANDLE_READV(NREAD, D, IOV, IOVCNT)				\
do {									\
	NREAD = readv(D, IOV, IOVCNT);					\
	if (NREAD == -1l)						\
		EXIT_ON_FAILURE("failed to read from file"		\
				"\e24m]\n\n{\n"				\
				"\tnread:   '" #NREAD  "' (-1),\n"	\
				"\td:       '" #D      "' (%d),\n"	\
				"\tiov:     '" #IOV    "' (%p),\n"	\
				"\tniovcnt: '" #IOVCNT "' (%d)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				D,					\
				IOV,					\
				IOVCNT,					\
				READV_FAILURE(errno));			\
} while (0)
#define READV_FAILURE(ERRNO)						\
READ_PREAD_READV_FAILURE(ERRNO,						\
			 READV_EINVAL_REASON,				\
   ((ERRNO == EFAULT)							\
? "Part of the 'iov' points outside the process's allocated address"	\
  " space."								\
: "unknown"))

/* read, pread, and readv failure reasons ───────────────────────────────────
 * reaad, pread, and readv */
#define READ_PREAD_READV_FAILURE(ERRNO, EINVAL_REASON, REM_REASON)	\
  ((ERRNO == EAGAIN)							\
? "The file was marked for non-blocking I/O, and no data were ready to"	\
  " be read."								\
:  ((ERRNO == EBADF)							\
? "'fildes' is not a valid file or socket descriptor open for reading."	\
:  ((ERRNO == EFAULT)							\
? "'buf' points outside the allocated address space."			\
:  ((ERRNO == EINTR)							\
? "A read from a slow device was interrupted before any data arrived "	\
  "by the delivery of a signal."					\
: ((ERRNO == EINVAL)							\
? EINVAL_REASON								\
: ((ERRNO == EIO)							\
? "(one of the following)\n"						\
  "\t- An I/O error occurred while reading from the file system."	\
  "\t- The process group is orphaned."					\
  "\t- The file is a regular file, 'nbyte' is greater than 0, the "	\
  "starting position is before the end-of-file, and the starting "	\
  "position is greater than or equal to the offset maximum established"	\
  " for the open file descriptor associated with 'fildes'."		\
: ((ERRNO == EISDIR)							\
? "An attempt is made to read a directory."				\
: ((ERRNO == ENOBUFS)							\
? "An attempt to allocate a memory buffer fails."			\
: ((ERRNO == ENOMEM)							\
? "Insufficient memory is available."					\
: ((ERRNO == ENXIO)							\
? "(one of the following)\n"						\
  "\t- An action is requested of a device that does not exist."		\
  "\t- A requested action cannot be performed by the device."		\
: REM_REASON))))))))))

/* read, pread, and readv EINVAL failure reasons ─────────────────────────────
 * read */
#define READ_EINVAL_REASON						\
"The pointer associated with fildes was negative."

/* pread */
#define PREAD_EINVAL_REASON						\
"(one of the following)\n"						\
"\t- " READ_EINVAL_REASON						\
"\t- The specified file offset is invalid."

/* readv */
#define READV_EINVAL_REASON						\
"(one of the following)\n"						\
"\t- " READ_EINVAL_REASON						\
"\t- 'iovcnt' was less than or equal to 0, or greater than 16."		\
"\t- One of the 'iov_len' values in the 'iov' array was negative."	\
"\t- The sum of the 'iov_len' values in the 'iov' array overflowed a "	\
"32-bit integer."

/* HANDLE_WRITE, HANDLE_WRITEV, HANDLE_PWRITE ───────────────────────────────
 * write */
#define HANDLE_WRITE(NWRITE, FILDES, BUF, NBYTE)			\
do {									\
	NWRITE = write(FILDES, BUF, NBYTE);				\
	if (NWRITE == -1l)						\
		EXIT_ON_FAILURE("failed to write to file"		\
				"\e24m]\n\n{\n"				\
				"\tnwrite: '" #NWRITE "' (-1),\n"	\
				"\tfildes: '" #FILDES "' (%d),\n"	\
				"\tbuf:    '" #BUF    "' (%s),\n"	\
				"\tnbyte:  '" #NBYTE  "' (%zu)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				FILDES,					\
				BUF,					\
				NBYTE,					\
				WRITE_FAILURE(errno));			\
} while (0)
#define WRITE_FAILURE(ERRNO)						\
WRITE_WRITEV_PWRITE_FAILURE(ERRNO,					\
			    WRITE_EINVAL_REASON,			\
	WRITE_PWRITE_FAILURE(ERRNO,					\
			     WRITE_EAGAIN_REASON,			\
			     WRITE_WRITEV_FAILURE(ERRNO)))

/* writev */
#define HANDLE_WRITEV(NWRITE, FILDES, IOV, IOVCNT)			\
do {									\
	NWRITE = writev(FILDES, IOV, IOVCNT);				\
	if (NWRITE == -1l)						\
		EXIT_ON_FAILURE("failed to write to file"		\
				"\e24m]\n\n{\n"				\
				"\tnwrite: '" #NWRITE "' (-1),\n"	\
				"\tfildes: '" #FILDES "' (%d),\n"	\
				"\tiov:    '" #IOV    "' (%p),\n"	\
				"\tiovcnt: '" #IOVCNT "' (%d)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				FILDES,					\
				IOV,					\
				IOVCNT,					\
				WRITEV_FAILURE(errno));			\
} while (0)
#define WRITEV_FAILURE(ERRNO)						\
WRITE_WRITEV_PWRITE_FAILURE(ERRNO,					\
			    WRITEV_EINVAL_REASON,			\
  ((ERRNO == EDESTADDRREQ)						\
? "The destination is no longer available when writing to a UNIX "	\
  "domain datagram socket on which connect(2) or connectx(2) had been "	\
  "used to set a destination address."					\
: ((ERRNO == ENOBUFS)							\
? "The 'mbuf' pool has been completely exhausted when writing to a "	\
  "socket."								\
: WRITE_WRITEV_FAILURE(ERRNO))))

/* pwrite */
#define HANDLE_PWRITE(NWRITE, FILDES, BUF, NBYTE, OFFSET)		\
do {									\
	NWRITE = pwrite(FILDES, BUF, NBYTE, OFFSET);			\
	if (NWRITE == -1l)						\
		EXIT_ON_FAILURE("failed to write to file"		\
				"\e24m]\n\n{\n"				\
				"\tnwrite: '" #NWRITE "' (-1),\n"	\
				"\tfildes: '" #FILDES "' (%d),\n"	\
				"\tbuf:    '" #BUF    "' (%s),\n"	\
				"\tnbyte:  '" #NBYTE  "' (%zu),\n"	\
				"\toffset: '" #OFFSET "' (%jd),\n"	\
				"}\n\n"					\
				"reason: %s",				\
				FILDES,					\
				BUF,					\
				NBYTE,					\
				OFFSET,					\
				PWRITE_FAILURE(errno));			\
} while (0)
#define PWRITE_FAILURE(ERRNO)						\
WRITE_WRITEV_PWRITE_FAILURE(ERRNO,					\
			    PWRITE_EINVAL_REASON,			\
  WRITE_PWRITE_FAILURE(ERRNO,						\
		       PWRITE_EAGAIN_REASON,				\
  ((ERRNO == ESPIPE)							\
? "The file descriptor is associated with a pipe, socket, or FIFO."	\
: "unknown")))

/* write, writev, and pwrite failure reasons */
#define WRITE_WRITEV_PWRITE_FAILURE(ERRNO, EINVAL_REASON, REM_REASON)	\
  ((ERRNO == EDQUOT)							\
? "The user's quota of disk blocks on the file system containing the "	\
  "file is exhausted."							\
: ((ERRNO == EFAULT)							\
? "Part of 'iov' or data to be written to the file points outside the "	\
  "process's allocated address space."					\
: ((ERRNO == EINVAL)							\
? EINVAL_REASON								\
: REM_REASON)))

/* write and pwrite failure reasons */
#define WRITE_PWRITE_FAILURE(ERRNO,					\
			     EAGAIN_REASON,				\
			     REM_REASON)				\
  ((ERRNO == EAGAIN)							\
? EAGAIN_REASON								\
: ((ERRNO == EBADF)							\
? "'fildes' is not a valid file descriptor open for writing"		\
: ((ERRNO == ECONNRESET)						\
? "A write is attempted on a socket that is not connected."		\
: ((ERRNO == EFBIG)							\
? "(one of the following)\n"						\
  "\t- An attempt is made to write a file that exceeds the process's "	\
  "file size limit or the maximum file size."				\
  "\t- The file is a regular file, 'nbyte' is greater than 0, and the "	\
  "starting position is greater than or equal to the offset maximum"	\
  " established in the open file description associated with 'fildes'."	\
: ((ERRNO == EINTR)							\
? "A signal interrupts the write before it could be completed."		\
: ((ERRNO == EIO)							\
? "An I/O error occurs while reading from or writing to the file "	\
  "system."								\
: ((ERRNO == ENETDOWN)							\
? "A write is attempted on a socket and the local network interface "	\
  "used to reach the destination is down."				\
: ((ERRNO == ENETUNREACH)						\
? "A write is attempted on a socket and no route to the network is "	\
  "present."								\
: ((ERRNO == ENOSPC)							\
? "There is no free space remaining on the file system containing the "	\
  "file."								\
: ((ERRNO == ENXIO)							\
? "A request is made of a nonexistent device, or the request is "	\
  "outside the capabilities of the device."				\
: ((ERRNO == EPIPE)							\
? "(one of the following)\n"						\
  "\t- An attempt is made to write to a pipe that is not open for "	\
   "reading by any process."						\
  "\t- An attempt is made to write to a socket of type SOCK_STREAM "	\
   "that is not connected to a peer socket."				\
: REM_REASON)))))))))))

/* write and writev failure reasons */
#define WRITE_WRITEV_FAILURE(ERRNO)					\
  ((ERRNO == EWOULDBLOCK)						\
? WRITEV_EAGAIN_REASON							\
: "unknown")

/* write failure reasons for specific 'errno's
 *
 * EINVAL ───────────────────────────────────────────────────────────────────
 * write, writev, pwrite */
#define WRITE_WRITEV_PWRITE_EINVAL_REASON				\
"The pointer associated with 'fildes' is negative."
/* write */
#define WRITE_EINVAL_REASON WRITE_WRITEV_PWRITE_EINVAL_REASON
/* writev */
#define WRITEV_EINVAL_REASON						\
"(one of the following)\n"						\
"\t- " WRITE_WRITEV_PWRITE_EINVAL_REASON				\
"\t- 'iovcnt' is less than or equal to 0, or greater than "		\
"'UIO_MAXIOV'."								\
"\t- One of the 'iov_len' values in the iov array is negative."		\
"\t- The sum of the 'iov_len' values in the iov array overflows a "	\
"32-bit integer."
/* pwrite */
#define PWRITE_EINVAL_REASON						\
"(one of the following)\n"						\
"\t- " WRITE_WRITEV_PWRITE_EINVAL_REASON				\
"\t- The specified file offset is invalid."
/* EAGAIN ───────────────────────────────────────────────────────────────────
 * write, pwrite */
#define WRITE_PWRITE_EAGAIN_REASON					\
"The file is marked for non-blocking I/O, and no data could be "	\
"written immediately."
/* write, writev */
#define WRITE_WRITEV_EAGAIN_REASON					\
"The file descriptor is for a socket, is marked 'O_NONBLOCK', and "	\
"write would block."
/* write */
#define WRITE_EAGAIN_REASON						\
"(one of the following)\n"						\
"\t- " WRITE_PWRITE_EAGAIN_REASON					\
"\t- " WRITE_WRITEV_EAGAIN_REASON
/* writev */
#define WRITEV_EAGAIN_REASON WRITE_WRITEV_EAGAIN_REASON
/* pwrite */
#define PWRITE_EAGAIN_REASON WRITE_PWRITE_EAGAIN_REASON

/* HANDLE_CLOSE ─────────────────────────────────────────────────────────────
 * close */
#define HANDLE_CLOSE(FILDES)						\
do {									\
	if (close(FILDES) == -1)					\
		EXIT_ON_FAILURE("failed to close file"			\
				"\e24m]\n\n{\n"				\
				"\tfildes: '" #FILDES "' (%d)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				FILDES,					\
				CLOSE_FAILURE(errno));			\
} while (0)
#define CLOSE_FAILURE(ERRNO)						\
  ((ERRNO == EBADF)							\
? "'fildes' is not a valid, active file descriptor."			\
: ((ERRNO == EINTR)							\
? "Execution was interrupted by a signal."				\
: ((ERRNO == EIO)							\
? "A previously-uncommitted write(2) encountered an input/output "	\
  "error."								\
: "unknown")))


/* HANDLE_FOPEN, HANDLE_FDOPEN, HANDLE_FREOPEN ──────────────────────────────
 * fopen */
#define HANDLE_FOPEN(STREAM, FILENAME, MODE)				\
do {									\
	STREAM = fopen(FILENAME, MODE);					\
	if (STREAM == NULL_POINTER)					\
		EXIT_ON_FAILURE("failed to open file"			\
				"\e24m]\n\n{\n"				\
				"\tstream:   '" #STREAM   "' (%p),\n"	\
				"\tfilename: '" #FILENAME "' (%s),\n"	\
				"\tmode:     '" #MODE     "' (%s)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				STREAM,					\
				FILENAME,				\
				MODE,					\
				FOPEN_FAILURE(errno));			\
} while (0)
#define FOPEN_FAILURE(ERRNO)						\
  ((ERRNO == EINVAL)							\
? "invalid 'mode' argument"						\
: OPEN_FAILURE(ERRNO))

/* fdopen */
#define HANDLE_FDOPEN(STREAM, FILDES, MODE)				\
do {									\
	STREAM = fdopen(FILDES, MODE);					\
	if (STREAM == NULL_POINTER)					\
		EXIT_ON_FAILURE("failed to open file"			\
				"\e24m]\n\n{\n"				\
				"\tstream: '" #STREAM "' (%p),\n"	\
				"\tfildes: '" #FILDES "' (%d),\n"	\
				"\tmode:   '" #MODE   "' (%s)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				STREAM,					\
				FILDES,					\
				MODE,					\
				FDOPEN_FAILURE(errno));			\
} while (0)
#define FDOPEN_FAILURE(ERRNO) FOPEN_FAILURE(ERRNO)

/* freopen */
#define HANDLE_FREOPEN(STREAM, FILENAME, MODE)				\
do {									\
	STREAM = freopen(FILENAME, MODE, STREAM);			\
	if (STREAM == NULL_POINTER)					\
		EXIT_ON_FAILURE("failed to reopen file"			\
				"\e24m]\n\n{\n"				\
				"\tstream:   '" #STREAM   "' (%p),\n"	\
				"\tfilename: '" #FILENAME "' (%s),\n"	\
				"\tmode:     '" #MODE     "' (%s)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				STREAM,					\
				FILENAME,				\
				CLASSIFY_FILE_PERMISSION(MODE),		\
				FOPEN_FAILURE(errno));			\
} while (0)
#define FREOPEN_FAILURE(ERRNO) FOPEN_FAILURE(ERRNO)

/* HANDLE_FREAD ─────────────────────────────────────────────────────────────
 * fread */
#define HANDLE_FREAD(NREAD, PTR, SIZE, NITEMS, STREAM)			\
do {									\
	NREAD = fread(PTR, SIZE, NITEMS, STREAM);			\
	if (NREAD == 0lu) {						\
		if (ferror(STREAM))					\
			FREAD_EXIT("I/O",				\
				   NREAD,				\
				   PTR,					\
				   SIZE,				\
				   NITEMS,				\
				   STREAM);				\
		if (!feof(STREAM))					\
			FREAD_EXIT("format",				\
				   NREAD,				\
				   PTR,					\
				   SIZE,				\
				   NITEMS,				\
				   STREAM);				\
	}								\
} while (0)
#define FREAD_EXIT(FAIL_TYPE, NREAD, PTR, SIZE, NITEMS, STREAM)		\
EXIT_ON_FAILURE("failed to read file (" FAIL_TYPE " error)"		\
		"\e24m]\n\n{\n"						\
		"\tnread:  '" #NREAD  "', (0)\n"			\
		"\tptr:    '" #PTR    "', (%p)\n"			\
		"\tsize:   '" #SIZE   "', (%zu)\n"			\
		"\tnitems: '" #NITEMS "', (%zu)\n"			\
		"\tstream: '" #STREAM "' (%p)\n"			\
		"}\n\n"							\
		"reason: %s",						\
		PTR,							\
		SIZE,							\
		NITEMS,							\
		STREAM,							\
		FREAD_FAILURE(errno))
#define FREAD_FAILURE(ERRNO) READ_FAILURE(ERRNO)

/* HANDLE_FWRITE ────────────────────────────────────────────────────────────
 * fwrite */
#define HANDLE_FWRITE(NWRITE, PTR, SIZE, NITEMS, STREAM)		\
do {									\
	NWRITE = fwrite(PTR, SIZE, NITEMS, STREAM);			\
	if (NWRITE == 0lu) {						\
		if (ferror(STREAM))					\
			FWRITE_EXIT("I/O",				\
				    NWRITE,				\
				    PTR,				\
				    SIZE,				\
				    NITEMS,				\
				    STREAM);				\
		if (!feof(STREAM))					\
			FWRITE_EXIT("format",				\
				    NWRITE,				\
				    PTR,				\
				    SIZE,				\
				    NITEMS,				\
				    STREAM);				\
	}								\
} while (0)
#define FWRITE_EXIT(FAIL_TYPE, NWRITE, PTR, SIZE, NITEMS, STREAM)	\
EXIT_ON_FAILURE("failed to read file (" FAIL_TYPE " error)"		\
		"\e24m]\n\n{\n"						\
		"\tnwrite: '" #NWRITE "', (0)\n"			\
		"\tptr:    '" #PTR    "', (%p)\n"			\
		"\tsize:   '" #SIZE   "', (%zu)\n"			\
		"\tnitems: '" #NITEMS "', (%zu)\n"			\
		"\tstream: '" #STREAM "' (%p)\n"			\
		"}\n\n"							\
		"reason: %s",						\
		PTR,							\
		SIZE,							\
		NITEMS,							\
		STREAM,							\
		FWRITE_FAILURE(errno))
#define FWRITE_FAILURE(ERRNO) WRITE_FAILURE(ERRNO)

/* HANDLE_FCLOSE ────────────────────────────────────────────────────────────
 * fclose */
#define HANDLE_FCLOSE(STREAM)						\
do {									\
	if (fclose(STREAM) == EOF)					\
		EXIT_ON_FAILURE("failed to close file"			\
				"\e24m]\n\n{\n"				\
				"\tstream: '" #STREAM "' (%p),\n"	\
				"}\n\n"					\
				"reason: %s",				\
				STREAM,					\
				FCLOSE_FAILURE(errno));			\
} while (0)
#define FCLOSE_FAILURE(ERRNO) CLOSE_FAILURE(ERRNO)

/* HANDLE_FGETS, HANDLE_GETS, HANDLE_GETLINE, HANDLE_GETDELIM  ──────────────
 * fgets */
#define HANDLE_FGETS(STR, SIZE, STREAM)					\
do {									\
	const char *const restrict _str_ptr = fgets(STR,		\
						    (int) SIZE,		\
						    STREAM);		\
	 if ((_str_ptr == NULL_POINTER) && (ferror(STREAM) != 0))	\
		EXIT_ON_FAILURE("failed to read from file"		\
				"\e24m]\n\n{\n"				\
				"\tstr:    '" #STR    "' (%p),\n"	\
				"\tsize:   '" #SIZE   "' (%d),\n"	\
				"\tstream: '" #STREAM "' (%p)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				STR,					\
				(int) SIZE,				\
				STREAM,					\
				FGETS_FAILURE(errno));			\
} while (0)
#define FGETS_FAILURE(ERRNO) STREAM_GET_FAILURE(ERRNO)

/* gets */
#define HANDLE_GETS(STR)						\
do {									\
	const char *const restrict _str_ptr = gets(STR);		\
	 if ((_str_ptr == NULL_POINTER) && (ferror(stdin) != 0))	\
		EXIT_ON_FAILURE("failed to read from 'stdin'"		\
				"\e24m]\n\n{\n"				\
				"\tstr: '" #STR "' (%p)\n"		\
				"}\n\n"					\
				"reason: %s",				\
				STR,					\
				GETS_FAILURE(errno));			\
} while (0)
#define GETS_FAILURE(ERRNO) STREAM_GET_FAILURE(ERRNO)

ssize_t
getdelim(char ** restrict linep, size_t * restrict linecapp, int delimiter, FILE * restrict stream);
ssize_t
getline(char ** restrict linep, size_t * restrict linecapp, FILE * restrict stream);

/* getline */
#define HANDLE_GETLINE(LINEP, LINECAPP, STREAM)				\
do {									\
	 if (getline(LINEP, LINECAPP, STREAM) == -1l)			\
		EXIT_ON_FAILURE("failed to read line from file"		\
				"\e24m]\n\n{\n"				\
				"\tlinep:    '" #LINEP    "' (%p),\n"	\
				"\tlinecapp: '" #LINECAPP "' (%zu),\n"	\
				"\tstream:   '" #STREAM   "' (%p)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				LINEP,					\
				LINECAPP,				\
				STREAM,					\
				GETLINE_FAILURE(errno));		\
} while (0)
#define GETLINE_FAILURE(ERRNO) GETLINE_GETDELIM_FAILURE(ERRNO)

/* getdelim */
#define HANDLE_GETDELIM(LINEP, LINECAPP, DELIMITER, STREAM)		\
do {									\
	 if (getdelim(LINEP, LINECAPP, DELIMITER, STREAM) == -1l)	\
		EXIT_ON_FAILURE("failed to read line from file"		\
				"\e24m]\n\n{\n"				\
				"\tlinep:     '" #LINEP     "' (%p),\n"	\
				"\tlinecapp:  '" #LINECAPP  "' (%zu),\n"\
				"\tdelimiter: '" #DELIMITER "' (%d),\n"	\
				"\tstream:    '" #STREAM    "' (%p)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				LINEP,					\
				LINECAPP,				\
				DELIMITER,				\
				STREAM,					\
				GETDELIM_FAILURE(errno));		\
} while (0)
#define GETDELIM_FAILURE(ERRNO) GETLINE_GETDELIM_FAILURE(ERRNO)

/* getline and getdelim failure reasons */
#define GETLINE_GETDELIM_FAILURE(ERRNO)					\
((ERRNO == EINVAL)							\
? "Either 'linep' or 'linecapp' is NULL."				\
((ERRNO == EOVERFLOW)							\
? "No delimiter was found in the first 'SSIZE_MAX' characters."		\
: FGETS_FAILURE(ERRNO)))


/* HANDLE_FGETC, HANDLE_GETC, HANDLE_GET_CHAR, HANDLE_GETW, ─────────────────
 * HANDLE_GETC_UNLOCKED, HANDLE_GET_CHAR_UNLOCKED ───────────────────────────
 * fgetc, getc, getw */
#define HANDLE_FGETC(RES, STREAM) STREAM_GETV(fgetc, "char",	    RES, STREAM)
#define HANDLE_GETC(RES,  STREAM) STREAM_GETV(getc,  "char",	    RES, STREAM)
#define HANDLE_GETW(RES,  STREAM) STREAM_GETV(getw,  "wchar (int)", RES, STREAM)
/* getc_unlocked */
#define HANDLE_GETC_UNLOCKED(RES, STREAM) STREAM_GETV(getc_unlocked,	\
						      "char",		\
						      RES,		\
						      STREAM)
/* getchar, getchar_unlocked */
#define HANDLE_GETCHAR(RES)	     HANDLE_GETC(RES, stdin)
#define HANDLE_GETCHAR_UNLOCKED(RES) HANDLE_GETC_UNLOCKED(RES, stdin)

/* misc get/s handler implementation ────────────────────────────────────────
 * failure reasons for stream reading 'get/s' functions */
#define STREAM_GET_FAILURE(ERRNO)					\
  ((ERRNO == EBADF)							\
? "The given 'stream' is not a readable stream."			\
: READ_FAILURE(ERRNO))

/* exit for single value 'get' functions */
#define STREAM_GETV_EXIT(GET_TYPE, FAIL_TYPE, RES, STREAM)		\
EXIT_ON_FAILURE("failed to read next " GET_TYPE " from file ("		\
		FAIL_TYPE " error)"					\
		"\e24m]\n\n{\n"						\
		"\tres:    '" #RES    "',\n"				\
		"\tstream: '" #STREAM "'\n"				\
		"}\n\n"							\
		"reason: %s",						\
		STREAM_GET_FAILURE(errno))				\

/* routine for single value 'get' functions */
#define STREAM_GETV(GETV, GET_TYPE, RES, STREAM)			\
do {									\
	RES = (__typeof__(RES)) GETV(STREAM);				\
	if (RES == EOF) {						\
		if (ferror(STREAM))					\
			STREAM_GETV_EXIT(GET_TYPE,			\
					 "I/O",				\
					 RES,				\
					 STREAM);			\
		if (!feof(STREAM))					\
			STREAM_GETV_EXIT(GET_TYPE,			\
					 "format",			\
					 RES,				\
					 STREAM);			\
	}								\
} while (0)

/* HANDLE_FPUTS, HANDLE_PUTS ────────────────────────────────────────────────
 * fputs */
#define HANDLE_FPUTS(STR, STREAM)					\
do {									\
	 if (fputs(STR, STREAM) == EOF)					\
		EXIT_ON_FAILURE("failed to write to file"		\
				"\e24m]\n\n{\n"				\
				"\tstr:    '" #STR    "' (%p) %s,\n"	\
				"\tstream: '" #STREAM "' (%p)\n"	\
				"}\n\n"					\
				"reason: %s",				\
				STR,					\
				STR,					\
				STREAM,					\
				FPUTS_FAILURE(errno));			\
} while (0)
#define FPUTS_FAILURE(ERRNO) STREAM_PUT_FAILURE(ERRNO)

/* fputs */
#define HANDLE_PUTS(STR)						\
do {									\
	 if (puts(STR) == EOF)						\
		EXIT_ON_FAILURE("failed to write to 'stdout'"		\
				"\e24m]\n\n{\n"				\
				"\tstr: '" #STR "' (%p) %s\n"		\
				"}\n\n"					\
				"reason: %s",				\
				STR,					\
				STR,					\
				PUTS_FAILURE(errno));			\
} while (0)
#define PUTS_FAILURE(ERRNO) STREAM_PUT_FAILURE(ERRNO)

/* failure reasons for stream 'put' functions */
#define STREAM_PUT_FAILURE(ERRNO)					\
  ((ERRNO == EBADF)							\
? "The 'stream' argument is not a writable stream."			\
: WRITE_FAILURE(ERRNO))


/* HANDLE_GETCWD ────────────────────────────────────────────────────────────
 * getcwd */
#define HANDLE_GETCWD(BUF, SIZE)					\
do {									\
	if (getcwd(BUF, SIZE) == NULL_POINTER)				\
		EXIT_ON_FAILURE("failed to get current working"		\
				"directory"				\
				"\e24m]\n\n{\n"				\
				"\tbuf:  '" #BUF  "' (%s),\n"		\
				"\tsize: '" #SIZE "' (%zu)\n"		\
				"}\n\n"					\
				"reason: %s\n\n",			\
				BUF,					\
				SIZE,					\
				GETCWD_FAILURE(errno));			\
} while (0)
#define GETCWD_FAILURE(ERRNO)						\
  ((ERRNO == EACCES)							\
? "Read or search permission was denied for a component of the "	\
   "pathname."								\
: ((ERRNO == EINVAL)							\
? "The 'size' argument is zero."					\
: ((ERRNO == ENOENT)							\
? "A component of the pathname no longer exists."			\
: ((ERRNO == ENOMEM)							\
? "Insufficient memory is available."					\
: ((ERRNO == ERANGE)							\
? "The 'size' argument is greater than zero but smaller than the "	\
   "length of the pathname plus 1."					\
: "unknown")))))


/* HANDLE_MKDIR ─────────────────────────────────────────────────────────────
 * mkdir */
#define HANDLE_MKDIR(FILENAME, MODE)					\
do {									\
	if (mkdir(FILENAME, MODE) == -1) {				\
		char _perms_buffer[11];					\
		file_permissions_string(&_perms_buffer[0], MODE);	\
		EXIT_ON_FAILURE("failed to make directory"		\
				"\e24m]\n\n{\n"				\
				"\tfilename: '" #FILENAME "' (%s),\n"	\
				"\tmode:     '" #MODE     "' (%s) %s\n"	\
				"}\n\n"					\
				"reason: %s",				\
				FILENAME,				\
				&_perms_buffer[0],			\
				CLASSIFY_FILE_PERMISSION(MODE),		\
				MKDIR_FAILURE(errno));			\
	}								\
} while (0)
#define MKDIR_FAILURE(ERRNO)						\
  ((ERRNO == EACCES)							\
? "Write permission is denied for the parent directory in which the "	\
  "new directory is to be added."					\
: ((ERRNO == EEXIST)							\
? "A file named 'filename' already exists."				\
: ((ERRNO == EMLINK)							\
? "The parent directory has too many links (entries).\n\n "		\
  "Well-designed file systems never report this error, because they "	\
  "permit more links than your disk could possibly hold. However, you "	\
  "must still take account of the possibility of this error, as it "	\
  "could result from network access to a file system on another "	\
  "machine."								\
: ((ERRNO == ENOSPC)							\
? "The file system doesn’t have enough room to create the new "		\
  "directory."								\
: ((ERRNO == EROFS)							\
? "The parent directory of the directory being created is on a "	\
  "read-only file system and cannot be modified."			\
: "unknown")))))


/* HANDLE_CHMOD, HANDLE_FCHMOD, HANDLE_FCHMODAT ─────────────────────────────
 * chmod */
#define HANDLE_CHMOD(PATH, MODE)					\
do {									\
	if (chmod(PATH, MODE) == -1) {					\
		char _perms_buffer[11];					\
		file_permissions_string(&_perms_buffer[0], MODE);	\
		EXIT_ON_FAILURE("failed to change mode of file"		\
				"\e24m]\n\n{\n"				\
				"\tpath: '" #PATH "' (%s),\n"		\
				"\tmode: '" #MODE "' (%s) %s\n"		\
				"}\n\n"					\
				"reason: %s",				\
				PATH,					\
				&_perms_buffer[0],			\
				CLASSIFY_FILE_PERMISSION(MODE),		\
				CHMOD_FAILURE(errno));			\
	}								\
} while (0)
#define CHMOD_FAILURE(ERRNO) CMOD_FCHMODAT_FAILURE(ERRNO, "unknown")

/* fchmod */
#define HANDLE_FCHMOD(FILDES, MODE)					\
do {									\
	if (fchmod(FILDES, MODE) == -1) {				\
		char _perms_buffer[11];					\
		file_permissions_string(&_perms_buffer[0], MODE);	\
		EXIT_ON_FAILURE("failed to change mode of file"		\
				"\e24m]\n\n{\n"				\
				"\tfildes: '" #FILDES "' (%d) %s,\n"	\
				"\tmode:   '" #MODE   "' (%s) %s\n"	\
				"}\n\n"					\
				"reason: %s",				\
				FILDES,					\
				CLASSIFY_FILDES(FILDES)			\
				&_perms_buffer[0],			\
				CLASSIFY_FILE_PERMISSION(MODE),		\
				FCHMOD_FAILURE(errno));			\
	}								\
} while (0)
#define FCHMOD_FAILURE(ERRNO)						\
  ((ERRNO == EBADF)							\
? "'fildes' is not a valid file descriptor."				\
: ((ERRNO == EINVAL)							\
? "'fildes' refers to a socket, not to a file."				\
: ((ERRNO == EINVAL)							\
? "'mode' is not a valid file mode."					\
: ((ERRNO == EINTR)							\
? "Execution was interrupted by a signal."				\
: ((ERRNO == EIO)							\
? "An I/O error occurred while reading from or writing to the file "	\
   "system."								\
: ((ERRNO == EPERM)							\
? "The effective user ID does not match the owner of the file and the "	\
   "effective user ID is not the super-user."				\
: ((ERRNO == EROFS)							\
? "The file resides on a read-only file system."			\
: "unknown")))))))

/* fchmodat */
#define HANDLE_FCHMODAT(FD, PATH, MODE, FLAG)				\
do {									\
	if (fchmodat(FD, PATH, MODE, FLAG) == -1) {			\
		char _perms_buffer[11];					\
		file_permissions_string(&_perms_buffer[0], MODE);	\
		EXIT_ON_FAILURE("failed to change mode of file"		\
				"\e24m]\n\n{\n"				\
				"\tfd:   '" #FD   "' (%d) %s,\n"	\
				"\tpath: '" #PATH "' (%s),\n"		\
				"\tmode: '" #MODE "' (%s) %s,\n"	\
				"\tflag: '" #FLAG "' (%s)\n"		\
				"}\n\n"					\
				"reason: %s",				\
				FD,					\
				CLASSIFY_FILDES(FD)			\
				PATH,					\
				&_perms_buffer[0],			\
				CLASSIFY_FILE_PERMISSION(MODE),		\
				CLASSIFY_FILE_ATFLAG(FLAG),		\
				FCHMODAT_FAILURE(errno));		\
	}								\
} while (0)
#define FCHMODAT_FAILURE(ERRNO)						\
CMOD_FCHMODAT_FAILURE(ERRNO,						\
  ((ERRNO == EBADF)							\
? "The 'path' argument does not specify an absolute path and the 'fd' "	\
  "argument is neither 'AT_FDCWD' nor a valid file descriptor open "	\
  "for searching."							\
: ((ERRNO == EINVAL)							\
? "The value of the 'flag' argument is not valid."			\
: ((ERRNO == ENOTDIR)							\
? "The 'path' argument is not an absolute path and 'fd' is neither "	\
  "'AT_FDCWD' nor a file descriptor associated with a directory."	\
: "unknown"))))


/* chmod and fchmodat failure reasons */
#define CMOD_FCHMODAT_FAILURE(ERRNO, REM_REASON)			\
  ((ERRNO == EACCES)							\
? "Search permission is denied for a component of the path prefix."	\
: ((ERRNO == EFAULT)							\
? "path points outside the process's allocated address space."		\
: ((ERRNO == EINTR)							\
? "Its execution was interrupted by a signal."				\
: ((ERRNO == EIO)							\
? "An I/O error occurred while reading from or writing to the file "	\
   "system."								\
: ((ERRNO == ELOOP)							\
? "Too many symbolic links were encountered in translating the "	\
  "pathname.  This is taken to be indicative of a looping symbolic "	\
   "link."								\
: ((ERRNO == ENAMETOOLONG)						\
? "A component of a pathname exceeded {NAME_MAX} characters, or an "	\
   "entire path name exceeded {PATH_MAX} characters."			\
: ((ERRNO == ENOENT)							\
? "The named file does not exist."					\
: ((ERRNO == ENOTDIR)							\
? "A component of the path prefix is not a directory."			\
: ((ERRNO == EPERM)							\
? "The effective user ID does not match the owner of the file and the "	\
   "effective user ID is not the super-user."				\
: ((ERRNO == EROFS)							\
? "The named file resides on a read-only file system."			\
: REM_REASON))))))))))


/* misc inspection, debugging utils
 * ========================================================================== */
/* description for file open flag bits, 'OFLAG' */
#define CLASSIFY_FILE_OFLAG(OFLAG)					\
  ((OFLAG == O_RDONLY)							\
? "'O_RDONLY' - Open for reading only."					\
: ((OFLAG == O_WRONLY)							\
? "'O_WRONLY' - Open for writing only."					\
: ((OFLAG == O_RDWR)							\
? "'O_RDWR' - Open for reading and writing."				\
: ((OFLAG == O_NONBLOCK)						\
? "'O_NONBLOCK' - Do not block on open or for data to become "		\
  "available."								\
: ((OFLAG == O_APPEND)							\
? "'O_APPEND' - Append on each write."					\
: ((OFLAG == O_CREAT)							\
? "'O_CREAT' - Create file if it does not exist."			\
: ((OFLAG == O_TRUNC)							\
? "'O_TRUNC' - Truncate size to 0."					\
: ((OFLAG == (O_CREAT | O_EXCL))					\
? "'(O_CREAT | O_EXCL)' - Signal error if the file exists."		\
: ((OFLAG == O_SHLOCK)							\
? "'O_SHLOCK' - Atomically obtain a shared lock."			\
: ((OFLAG == O_EXLOCK)							\
? "'O_EXLOCK' - Atomically obtain an exclusive lock."			\
: ((OFLAG == O_NOFOLLOW)						\
? "'O_NOFOLLOW' - Do not follow symlinks."				\
: ((OFLAG == O_SYMLINK)							\
? "'O_SYMLINK' - Allow open of symlinks."				\
: ((OFLAG == O_EVTONLY)							\
? "'O_EVTONLY' - Descriptor requested for event notifications only."	\
: ((OFLAG == O_CLOEXEC)							\
? "'O_CLOEXEC' - Mark as close-on-exe."					\
: "compound 'oflag'"))))))))))))))


/* description for flag bits belonging to an "at" function, 'ATFLAG' */
#define CLASSIFY_FILE_ATFLAG(ATFLAG)					\
  ((ATFLAG == AT_EACCESS)						\
? "'AT_EACCESS' Use effective ids in access check."			\
: ((ATFLAG == AT_SYMLINK_NOFOLLOW)					\
? "'AT_SYMLINK_NOFOLLOW' - Act on the symlink itself not the target."	\
: ((ATFLAG == AT_SYMLINK_FOLLOW)					\
? "'AT_SYMLINK_FOLLOW' - Act on target of symlink."			\
: ((ATFLAG == AT_REMOVEDIR)						\
? "'AT_REMOVEDIR' - 'path' refers to directory."			\
: "compound 'at flag'"))))


/* description for file descriptor 'FILDES' */
#define CLASSIFY_FILDES(FILDES)						\
  ((FILDES == AT_FDCWD)							\
? "'AT_FDCWD' - Descriptor value for the current working directory."	\
: "unknown")


/* description for permission bits 'MODE' */
#define CLASSIFY_FILE_PERMISSION(MODE)					\
  ((MODE == S_IRUSR)							\
? "'S_ISRUSR' - Read permission bit for the owner of the file. On many"	\
  " systems this bit is 0400. 'S_IREAD' is an obsolete synonym "	\
  "provided for BSD compatibility."					\
: ((MODE == S_IWUSR)							\
? "'S_IWUSR' - Write permission bit for the owner of the file. Usually"	\
  " 0200. 'S_IWRITE' is an obsolete synonym provided for BSD "		\
  "compatibility."							\
: ((MODE == S_IXUSR)							\
? "'S_IXUSR' - Execute (for ordinary files) or search (for "		\
  "directories) permission bit for the owner of the file. Usually "	\
  "0100. 'S_IEXEC' is an obsolete synonym provided for BSD "		\
  "compatibility."							\
: ((MODE == S_IRWXU)							\
? "'S_IRWXU' - This is equivalent to ‘(S_IRUSR | S_IWUSR | S_IXUSR)’."	\
: ((MODE == S_IRGRP)							\
? "'S_IRGRP' - Read permission bit for the group owner of the file. "	\
  "Usually 040."							\
: ((MODE == S_IWGRP)							\
? "'S_IWGRP' - Write permission bit for the group owner of the file. "	\
  "Usually 020."							\
: ((MODE == S_IXGRP)							\
? "'S_IXGRP' - Execute or search permission bit for the group owner of"	\
" the file. Usually 010.)"						\
: ((MODE == S_IRWXG)							\
? "'S_IRWXG' - This is equivalent to ‘(S_IRGRP | S_IWGRP | S_IXGRP)’."	\
: ((MODE == S_IROTH)							\
? "'S_IROTH' - Read permission bit for other users. Usually 04."	\
: ((MODE == S_IWOTH)							\
? "'S_IWOTH' - Write permission bit for other users. Usually 02."	\
: ((MODE == S_IXOTH)							\
? "'S_IXOTH' - Execute or search permission bit for other users. "	\
  "Usually 01."								\
: ((MODE == S_IRWXO)							\
? "'S_IRWXO' - This is equivalent to ‘(S_IROTH | S_IWOTH | S_IXOTH)’."	\
: ((MODE == S_ISUID)							\
? "'S_ISUID' - This is the set-user-ID on execute bit, usually 04000."	\
: ((MODE == S_ISGID)							\
? "'S_ISGID' - This is the set-group-ID on execute bit, usually 02000."	\
: ((MODE == S_ISVTX)							\
? "'S_ISVTX' - This is the sticky bit, usually 01000."			\
: "compound permissions")))))))))))))))

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * FUNCTION-LIKE MACROS
 *
 *
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline void fildes_write_all(const int fildes,
			     const char *restrict contents)
{
	FILE *restrict file;
	HANDLE_FDOPEN(file, fildes, "w");
	HANDLE_FPUTS(contents, file);
	HANDLE_FCLOSE(file);
}

inline void filename_write_all(const char *restrict filename,
			       const char *restrict contents)
{
	FILE *restrict file;
	HANDLE_FOPEN(file, filename, "w");
	HANDLE_FPUTS(contents, file);
	HANDLE_FCLOSE(file);
}

/* 10 chars long */
inline char *file_permissions_string_put(char *restrict buffer,
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
inline void file_permissions_string(char *restrict buffer,
				    const int mode)
{
	buffer  = file_permissions_string_put(buffer, mode);
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

#endif /* ifndef MYSQL_SEED_SYSTEM_FILE_UTILS_H_ */
