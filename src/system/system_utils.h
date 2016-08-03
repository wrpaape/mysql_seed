#ifndef MYSQL_SEED_SYSTEM_SYSTEM_UTILS_H_
#define MYSQL_SEED_SYSTEM_SYSTEM_UTILS_H_


/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#ifdef WIN32
#	include <windows.h>	/* DeviceIoControl */
#	include <winsock2.h>	/* socket */
#	include <ws2tcpip.h>	/* getaddrinfo */
#else
#	include <sys/ioctl.h>	/* iotcl */
#	include <sys/socket.h>	/* socket */
#	include <net/if.h>	/* ifreq, ifconf */
#	include <netdb.h>	/* getaddrinfo */
#endif /* ifdef WIN32 */

#include <sys/uio.h>		/* read, write */
#include <sys/types.h>		/* ssize_t, chmod API */
#include <sys/stat.h>		/* mkdir */
#include <sys/param.h>		/* MAXPATHLEN */
#include "utils/fail_switch.h"	/* stdbool, errno, FAIL_SWITCH */
#include "utils/closure.h"	/* HandlerClosure */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* included from <sys/ioctl.h>
 *
 * struct winsize {
 *	unsigned short ws_row;		rows, in characters
 *	unsigned short ws_col;		columns, in characters
 *	unsigned short ws_xpixel;	horizontal size, pixels
 *	unsigned short ws_ypixel;	vertical size, pixels
 * }; */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS
 *
 *
 * FUNCTION-LIKE MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* ioctl wrappers */
#ifndef WIN32
#	define get_interface_addresses_imp(CONFIG, DEVICE_DESCRIPTOR)	\
	ioctl(DEVICE_DESCRIPTOR, SIOCGIFCONF, CONFIG)

#	define get_device_active_flags_imp(REQUEST, DEVICE_DESCRIPTOR)	\
	ioctl(DEVICE_DESCRIPTOR, SIOCGIFFLAGS, REQUEST)

#	define get_hardware_address_imp(REQUEST, DEVICE_DESCRIPTOR)	\
	ioctl(DEVICE_DESCRIPTOR, SIOCGIFHWADDR, REQUEST)

#	define get_winsize_imp(WINDOW, FILE_DESCRIPTOR)			\
	ioctl(FILE_DESCRIPTOR, TIOCGWINSZ, WINDOW)
#endif /* ifndef WIN32 */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * FUNCTION-LIKE MACROS
 *
 *
 * HELPER FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER FUNCTIONS
 *
 *
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define FAIL_SWITCH_ERRNO_FAILURE	-1
#define FAIL_SWITCH_FAILURE_POINTER	failure

/* socket */
inline bool
socket_status(const int domain,
	      const int type,
	      const int protocol)
{
	return socket(domain,
		      type,
		      protocol) != -1;
}

inline void
socket_muffle(const int domain,
	      const int type,
	      const int protocol)
{
	(void) socket(domain,
		      type,
		      protocol);
}

#define FAIL_SWITCH_ROUTINE socket
inline bool
socket_report(const int domain,
	      const int type,
	      const int protocol,
	      const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(domain,
			       type,
			       protocol)
	FAIL_SWITCH_ERRNO_CASE_1(EACCES,
				 "Permission to create a socket of the "
				 "specified type and/or protocol is denied.")
	FAIL_SWITCH_ERRNO_CASE_1(EAFNOSUPPORT,
				 "The specified address family is not supported"
				 ".")
	FAIL_SWITCH_ERRNO_CASE_1(EMFILE,
				 "The per-process descriptor table is full.")
	FAIL_SWITCH_ERRNO_CASE_1(ENFILE,
				 "The system file table is full.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOBUFS,
				 "Insufficient buffer space is available. The "
				 "socket cannot be created until sufficient "
				 "resources are freed.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOMEM,
				 "Insufficient memory was available to fulfill "
				 "the request.")

	FAIL_SWITCH_ERRNO_CASE_1(EPROTONOSUPPORT,
				 "The protocol type or the specified protocol "
				 "is not supported within this domain.")
	FAIL_SWITCH_ERRNO_CASE_1(EPROTOTYPE,
				 "The socket type is not supported by the "
				 "protocol.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
socket_handle(const int domain,
	      const int type,
	      const int protocol,
	      Handler *const handle,
	      void *arg)
{
	const char *restrict failure;

	if (socket_report(domain,
			  type,
			  protocol,
			  &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
socket_handle_cl(const int domain,
		 const int type,
		 const int protocol,
		 const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (socket_report(domain,
			  type,
			  protocol,
			  &failure))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}


#ifdef LINUX
/* get_interface_addresses */
inline bool
get_interface_addresses_status(struct ifconf *const restrict configuration,
			       const int device_descriptor)
{
	return get_interface_addresses_imp(configuration,
					   device_descriptor) != -1;
}

inline void
get_interface_addresses_muffle(struct ifconf *const restrict configuration,
			       const int device_descriptor)
{
	(void) get_interface_addresses_imp(configuration,
					   device_descriptor);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE get_interface_addresses_imp
inline bool
get_interface_addresses_report(struct ifconf *const restrict configuration,
			       const int device_descriptor,
			       const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(configuration,
			       device_descriptor)
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'device_descriptor', is not a valid "
				 "descriptor.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "'configuration' or ioctl request 'SIOCGIFCONF' is"
				 " not valid.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTTY,
				 "'device_descriptor' is not associated with a "
				 "character special device.",
				 "The specified iotcl configuration 'SIOCGIFCONF' "
				 "does not apply to the kind of object that the"
				 " descriptor 'device_descriptor' references.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
get_interface_addresses_handle(struct ifconf *const restrict configuration,
			       const int device_descriptor,
			       Handler *const handle,
			       void *arg)
{
	const char *restrict failure;

	if (get_interface_addresses_report(configuration,
					   device_descriptor,
					   &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
get_interface_addresses_handle_cl(struct ifconf *const restrict configuration,
				  const int device_descriptor,
				  const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (get_interface_addresses_report(configuration,
					   device_descriptor,
					   &failure))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}


/* get_device_active_flags */
inline bool
get_device_active_flags_status(struct ifreq *const restrict request,
			       const int device_descriptor)
{
	return get_device_active_flags_imp(request,
					   device_descriptor) != -1;
}

inline void
get_device_active_flags_muffle(struct ifreq *const restrict request,
			       const int device_descriptor)
{
	(void) get_device_active_flags_imp(request,
					   device_descriptor);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE get_device_active_flags_imp
inline bool
get_device_active_flags_report(struct ifreq *const restrict request,
			       const int device_descriptor,
			       const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(request,
			       device_descriptor)
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'device_descriptor', is not a valid "
				 "descriptor.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "'request' or ioctl request 'SIOCGIFFLAGS' is"
				 " not valid.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTTY,
				 "'device_descriptor' is not associated with a "
				 "character special device.",
				 "The specified iotcl request 'SIOCGIFFLAGS' "
				 "does not apply to the kind of object that the"
				 " descriptor 'device_descriptor' references.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
get_device_active_flags_handle(struct ifreq *const restrict request,
			       const int device_descriptor,
			       Handler *const handle,
			       void *arg)
{
	const char *restrict failure;

	if (get_device_active_flags_report(request,
					   device_descriptor,
					   &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
get_device_active_flags_handle_cl(struct ifreq *const restrict request,
				  const int device_descriptor,
				  const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (get_device_active_flags_report(request,
					   device_descriptor,
					   &failure))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}


/* get_hardware_address */
inline void
get_hardware_address_status(struct ifreq *const restrict request,
			    const int device_descriptor)
{
	return get_hardware_address_imp(request,
					device_descriptor) != -1;
}

inline bool
get_hardware_address_muffle(struct ifreq *const restrict request,
			    const int device_descriptor)
{
	(void) get_hardware_address_imp(request,
					device_descriptor);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE get_hardware_address_imp
inline bool
get_hardware_address_report(struct ifreq *const restrict request,
			    const int device_descriptor,
			    const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(request,
			       device_descriptor)
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'device_descriptor', is not a valid "
				 "descriptor.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "'request' or ioctl request 'SIOCGIFHWADDR' is"
				 " not valid.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTTY,
				 "'device_descriptor' is not associated with a "
				 "character special device.",
				 "The specified iotcl request 'SIOCGIFHWADDR' "
				 "does not apply to the kind of object that the"
				 " descriptor 'device_descriptor' references.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
get_hardware_address_handle(struct ifreq *const restrict request,
			    const int device_descriptor,
			    Handler *const handle,
			    void *arg)
{
	const char *restrict failure;

	if (get_hardware_address_report(request,
					device_descriptor,
					&failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
get_hardware_address_handle_cl(struct ifreq *const restrict request,
			       const int device_descriptor,
			       const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (get_hardware_address_report(request,
					device_descriptor,
					&failure))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}


/* get_winsize */
inline bool
get_winsize_status(struct winsize *const restrict window,
		   const int file_descriptor)
{
	return get_winsize_imp(window,
			       file_descriptor) != -1;
}

inline void
get_winsize_muffle(struct winsize *const restrict window,
		   const int file_descriptor)
{
	(void) get_winsize_imp(window,
			       file_descriptor);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE get_winsize_imp
inline bool
get_winsize_report(struct winsize *const restrict window,
		   const int file_descriptor,
		   const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(window,
			       file_descriptor)
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'file_descriptor', is not a valid descriptor"
				 ".")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "'window' or ioctl request 'TIOCGWINSZ' is not"
				 " valid.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTTY,
				 "'file_descriptor' is not associated with a "
				 "character special device.",
				 "The specified iotcl request 'TIOCGWINSZ' does"
				 "not apply to the kind of object that the"
				 " descriptor 'file_descriptor' references.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
get_winsize_handle(struct winsize *const restrict window,
		   const int file_descriptor,
		   Handler *const handle,
		   void *arg)
{
	const char *restrict failure;

	if (get_winsize_report(window,
			       file_descriptor,
			       &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
get_winsize_handle_cl(struct winsize *const restrict window,
		      const int file_descriptor,
		      const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (get_winsize_report(window,
			       file_descriptor,
			       &failure))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}
#endif /* ifdef LINUX */


inline bool
getaddrinfo_status(const char *const node,
		   const char *const service,
		   const struct addrinfo *const hints,
		   struct addrinfo **const result)
{
	return getaddrinfo(node,
			   service,
			   hints,
			   result) == 0;
}

inline void
getaddrinfo_muffle(const char *const node,
		   const char *const service,
		   const struct addrinfo *const hints,
		   struct addrinfo **const result)
{
	(void) getaddrinfo(node,
			   service,
			   hints,
			   result);
}

#undef	FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE getaddrinfo
#define FAIL_SWITCH_STATUS_SUCCESS 0

inline bool
getaddrinfo_report(const char *const node,
		   const char *const service,
		   const struct addrinfo *const hints,
		   struct addrinfo **const result,
		   const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(node,
				service,
				hints,
				result)
	FAIL_SWITCH_STATUS_CASE_1(EAI_ADDRFAMILY,
				  "The specified network host does not have any"
				  " network addresses in the requested address "
				  "family.")
	FAIL_SWITCH_STATUS_CASE_1(EAI_AGAIN,
				  "temporary failure in name resolution")
	FAIL_SWITCH_STATUS_CASE_1(EAI_BADFLAGS,
				  "invalid value for 'hints->ai_flags'")
	FAIL_SWITCH_STATUS_CASE_1(EAI_FAIL,
				  "non-recoverable failure in name resolution")
	FAIL_SWITCH_STATUS_CASE_1(EAI_FAMILY,
				  "ai_family not supported")
	FAIL_SWITCH_STATUS_CASE_1(EAI_MEMORY,
				  "memory allocation failure")
	FAIL_SWITCH_STATUS_CASE_1(EAI_NODATA,
				  "The specified network host exists, but it "
				  "does not have any network addresses defined"
				  ".")
	FAIL_SWITCH_STATUS_CASE_3(EAI_NONAME,
				  "The node or service is not known",
				  "both 'node' and 'service' are NULL",
				  "'AI_NUMERICSERV' was specified in "
				  "'hints->ai_flags' and 'service' was not a "
				  "numeric port-number string")
	FAIL_SWITCH_STATUS_CASE_1(EAI_SERVICE,
				  "'service' not supported for "
				  "'hints->ai_socktype'")
	FAIL_SWITCH_STATUS_CASE_1(EAI_SOCKTYPE,
				  "'hints->ai_socktype' not supported")
	FAIL_SWITCH_STATUS_CASE_1(EAI_SYSTEM,
				  "system error")
	FAIL_SWITCH_STATUS_CASE_1(EAI_BADHINTS,
				  "invalid value for 'hints'")
	FAIL_SWITCH_STATUS_CASE_1(EAI_PROTOCOL,
				  "resolved protocol is unknown")
	FAIL_SWITCH_STATUS_CASE_1(EAI_OVERFLOW,
				  "argument buffer overflow")
	FAIL_SWITCH_STATUS_CLOSE()

}

inline void
getaddrinfo_handle(const char *const node,
		   const char *const service,
		   const struct addrinfo *const hints,
		   struct addrinfo **const result,
		   Handler *const handle,
		   void *arg)
{
	const char *restrict failure;

	if (getaddrinfo_report(node,
			       service,
			       hints,
			       result,
			       &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
getaddrinfo_handle_cl(const char *const node,
		      const char *const service,
		      const struct addrinfo *const hints,
		      struct addrinfo **const result,
		      const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (getaddrinfo_report(node,
			       service,
			       hints,
			       result,
			       &failure))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS */

/* undefine FAIL_SWITCH macro constants */
#undef FAIL_SWITCH_ROUTINE
#undef FAIL_SWITCH_ERRNO_FAILURE
#undef FAIL_SWITCH_FAILURE_POINTER

#endif /* ifndef MYSQL_SEED_SYSTEM_SYSTEM_UTILS_H_ */
