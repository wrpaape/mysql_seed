#ifndef MYSQL_SEED_SYSTEM_SYSTEM_UTILS_H_
#define MYSQL_SEED_SYSTEM_SYSTEM_UTILS_H_


/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#ifdef WIN32
#	include <windows.h>	/* DeviceIoControl */
#	include <winsock2.h>	/* socket */
#	include <iphlpapi.h>	/* GetAdaptersAddress */
#	include <ws2tcpip.h>	/* getaddrinfo */
#else
#	include <sys/ioctl.h>	/* iotcl */
#	include <sys/types.h>	/* LINUX compatibility */
#	include <sys/socket.h>	/* socket */
#	include <net/if.h>	/* ifreq, ifconf */
#	include <netdb.h>	/* getaddrinfo */
#endif /* ifdef WIN32 */

#ifdef OSX
#	include <sys/sysctl.h>	/* sysctl */
#endif /* ifdef OSX */

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

#ifdef WIN32
#	define get_adapters_addresses_imp(FAMILY,			\
					  FLAGS,			\
					  RESERVED,			\
					  ADAPTER_ADDRESSES,		\
					  SIZE_POINTER)			\
	GetAdaptersAddresses(FAMILY,					\
			     FLAGS,					\
			     RESERVED,					\
			     ADAPTER_ADDRESSES,				\
			     SIZE_POINTER)
#	define size_adapters_addresses_imp(FAMILY,			\
					   FLAGS,			\
					   RESERVED,			\
					   SIZE_POINTER)		\
	GetAdaptersAddresses(FAMILY,					\
			     FLAGS,					\
			     RESERVED,					\
			     NULL,					\
			     SIZE_POINTER)
#else
/* ioctl wrappers */
#	define interface_name_to_index_imp(NAME)			\
	if_nametoindex(NAME)

#	define get_interface_networks_imp(CONFIG, DEVICE_DESCRIPTOR)	\
	ioctl(DEVICE_DESCRIPTOR, SIOCGIFCONF, CONFIG)

#	define get_device_active_flags_imp(REQUEST, DEVICE_DESCRIPTOR)	\
	ioctl(DEVICE_DESCRIPTOR, SIOCGIFFLAGS, REQUEST)

#	define get_winsize_imp(WINDOW, FILE_DESCRIPTOR)			\
	ioctl(FILE_DESCRIPTOR, TIOCGWINSZ, WINDOW)
#endif /* ifdef WIN32 */

#ifdef LINUX
#	define get_interface_index_imp(REQUEST, DEVICE_DESCRIPTOR)	\
	ioctl(DEVICE_DESCRIPTOR, SIOCGIFINDEX, REQUEST)

#	define get_hardware_address_imp(REQUEST, DEVICE_DESCRIPTOR)	\
	ioctl(DEVICE_DESCRIPTOR, SIOCGIFHWADDR, REQUEST)
#endif /* ifdef LINUX */


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
socket_status(int *const restrict socket_descriptor,
	      const int domain,
	      const int type,
	      const int protocol)
{
	*socket_descriptor = socket(domain,
				    type,
				    protocol);

	return *socket_descriptor >= 0;
}

inline void
socket_muffle(int *const restrict socket_descriptor,
	      const int domain,
	      const int type,
	      const int protocol)
{
	*socket_descriptor = socket(domain,
				    type,
				    protocol);
}

#define FAIL_SWITCH_ROUTINE socket
inline bool
socket_report(int *const restrict socket_descriptor,
	      const int domain,
	      const int type,
	      const int protocol,
	      const char *restrict *const restrict failure)
{

	*socket_descriptor = socket(domain,
				    type,
				    protocol);

	if (LIKELY(*socket_descriptor >= 0))
		return true;

	switch (errno) {
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
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

inline void
socket_handle(int *const restrict socket_descriptor,
	      const int domain,
	      const int type,
	      const int protocol,
	      Handler *const handle,
	      void *arg)
{
	const char *restrict failure;

	if (LIKELY(socket_report(socket_descriptor,
				 domain,
				 type,
				 protocol,
				 &failure)))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
socket_handle_cl(int *const restrict socket_descriptor,
		 const int domain,
		 const int type,
		 const int protocol,
		 const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (LIKELY(socket_report(socket_descriptor,
				 domain,
				 type,
				 protocol,
				 &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}


#ifdef WIN32
/* size_adapters_addresses */
inline bool
size_adapters_addresses_status(ULONG family,
			       ULONG flags,
			       PVOID reserved,
			       PULONG size_pointer)
{
	return size_adapters_addresses_imp(family,
					   flags,
					   reserved,
					   size_pointer) == ERROR_BUFFER_OVERFLOW;
}

inline void
size_adapters_addresses_muffle(ULONG family,
			       ULONG flags,
			       PVOID reserved,
			       PULONG size_pointer)
{
	(void) size_adapters_addresses_imp(family,
					   flags,
					   reserved,
					   size_pointer);
}

#undef	FAIL_SWITCH_ROUTINE
#define	FAIL_SWITCH_ROUTINE size_adapters_addresses_imp
#define FAIL_SWITCH_STATUS_SUCCESS ERROR_BUFFER_OVERFLOW
inline bool
size_adapters_addresses_report(ULONG family,
			       ULONG flags,
			       PVOID reserved,
			       PULONG size_pointer,
			       const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(family,
				flags,
				reserved,
				size_pointer)
	FAIL_SWITCH_STATUS_CASE_1(ERROR_ADDRESS_NOT_ASSOCIATED,
				  "an address has not yet been associated with "
				  "the network endpoint  (DHCP lease "
				  "information was available)")
	FAIL_SWITCH_STATUS_CASE_3(ERROR_INVALID_PARAMETER,
				  "The 'size_pointer' parameter is NULL.",
				  "The 'address' paramter is not 'AF_INET', '"
				  "AF_INET6', or 'AF_UNSPEC'",
				  "The address information for the parameters "
				  "requested is greater than 'ULONG_MAX'.")
	FAIL_SWITCH_STATUS_CASE_1(ERROR_NOT_ENOUGH_MEMORY,
				  "Insufficient memory resources are available "
				  "to complete the operation.")
	FAIL_SWITCH_STATUS_CASE_1(ERROR_NO_DATA,
				  "No addresses were found for the requested "
				  "parameters")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
size_adapters_addresses_handle(ULONG family,
			       ULONG flags,
			       PVOID reserved,
			       PULONG size_pointer,
			       Handler *const handle,
			       void *arg)
{
	const char *restrict failure;

	if (LIKELY(size_adapters_addresses_report(family,
						  flags,
						  reserved,
						  size_pointer,
						  &failure)))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
size_adapters_addresses_handle_cl(ULONG family,
				  ULONG flags,
				  PVOID reserved,
				  PULONG size_pointer,
				  const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (LIKELY(size_adapters_addresses_report(family,
						  flags,
						  reserved,
						  size_pointer,
						  &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}


/* get_adapters_addresses */
inline bool
get_adapters_addresses_status(ULONG family,
			      ULONG flags,
			      PVOID reserved,
			      PIP_ADAPTER_ADDRESSES adapter_addresses,
			      PULONG size_pointer)
{
	return get_hardware_address_imp(family,
					flags,
					reserved,
					adapter_addresses,
					size_pointer) == ERROR_SUCCESS;
}

inline void
get_adapters_addresses_muffle(ULONG family,
			      ULONG flags,
			      PVOID reserved,
			      PIP_ADAPTER_ADDRESSES adapter_addresses,
			      PULONG size_pointer)
{
	(void) get_hardware_address_imp(family,
					flags,
					reserved,
					adapter_addresses,
					size_pointer);
}

#undef	FAIL_SWITCH_ROUTINE
#define	FAIL_SWITCH_ROUTINE get_adapters_addresses_imp
#undef	FAIL_SWITCH_STATUS_SUCCESS
#define FAIL_SWITCH_STATUS_SUCCESS ERROR_SUCCESS
inline bool
get_adapters_addresses_report(ULONG family,
			      ULONG flags,
			      PVOID reserved,
			      PIP_ADAPTER_ADDRESSES adapter_addresses,
			      PULONG size_pointer,
			      const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(family,
				flags,
				reserved,
				adapter_addresses,
				size_pointer)
	FAIL_SWITCH_STATUS_CASE_1(ERROR_ADDRESS_NOT_ASSOCIATED,
				  "an address has not yet been associated with "
				  "the network endpoint  (DHCP lease "
				  "information was available)")
	FAIL_SWITCH_STATUS_CASE_2(ERROR_BUFFER_OVERFLOW,
				 "The buffer size indicated by the '"
				 "size_pointer' parameter is too small to hold "
				 "the adapter information.",
				 "The 'adapter_addresses' parameter is 'NULL'.")
	FAIL_SWITCH_STATUS_CASE_3(ERROR_INVALID_PARAMETER,
				  "The 'size_pointer' parameter is NULL.",
				  "The 'address' paramter is not 'AF_INET', '"
				  "AF_INET6', or 'AF_UNSPEC'",
				  "The address information for the parameters "
				  "requested is greater than 'ULONG_MAX'.")
	FAIL_SWITCH_STATUS_CASE_1(ERROR_NOT_ENOUGH_MEMORY,
				  "Insufficient memory resources are available "
				  "to complete the operation.")
	FAIL_SWITCH_STATUS_CASE_1(ERROR_NO_DATA,
				  "No addresses were found for the requested "
				  "parameters")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
get_adapters_addresses_handle(ULONG family,
			      ULONG flags,
			      PVOID reserved,
			      PIP_ADAPTER_ADDRESSES adapter_addresses,
			      PULONG size_pointer,
			      Handler *const handle,
			      void *arg)
{
	const char *restrict failure;

	if (LIKELY(get_adapters_addresses_report(family,
						 flags,
						 reserved,
						 adapter_addresses,
						 size_pointer,
						 &failure)))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
get_adapters_addresses_handle_cl(ULONG family,
				 ULONG flags,
				 PVOID reserved,
				 PIP_ADAPTER_ADDRESSES adapter_addresses,
				 PULONG size_pointer,
				 const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (LIKELY(get_adapters_addresses_report(family,
						 flags,
						 reserved,
						 adapter_addresses,
						 size_pointer,
						 &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}
#else


/* interface_name_to_index */
inline bool
interface_name_to_index_status(int *const restrict index,
			       const char *const restrict name)
{
	*index = interface_name_to_index_imp(name);
	return *index != 0;
}

inline void
interface_name_to_index_muffle(int *const restrict index,
			       const char *const restrict name)
{
	*index = interface_name_to_index_imp(name);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE interface_name_to_index_imp
inline bool
interface_name_to_index_report(int *const restrict index,
			       const char *const restrict name,
			       const char *restrict *const restrict failure)
{
	*index = interface_name_to_index_imp(name);

	if (LIKELY(*index != 0))
		return true;

	switch (errno) {
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "sysctl failure - "
				 "The buffer 'mib_name', 'old_data', 'new_data'"
				 ", or length pointer 'size_old_data' contains "
				 "an invalid address.")
	FAIL_SWITCH_ERRNO_CASE_3(EINVAL,
				 "sysctl failure - "
				 "The 'mib_name' array is less than two or "
				 "greater than 'CTL_MAXNAME'.",
				 "sysctl failure - "
				 "A non-null 'new_data' is given and its "
				 "specified length in 'size_new_data' is too "
				 "large or too small.",
				 "ioctl failure - "
				 "'configuration' or ioctl request is not valid"
				 ".")
	FAIL_SWITCH_ERRNO_CASE_4(ENOMEM,
				 "sysctl failure - "
				 "The length pointed to by 'size_old_data' is "
				 "too short to hold the requested value.",
				 "sysctl failure - "
				 "The smaller of either the length pointed to "
				 "by 'size_old_data' or the estimated size of "
				 "the returned data exceeds the system limit on"
				 " locked memory.",
				 "sysctl failure - "
				 "Locking the buffer 'old_data', or a portion "
				 "of the buffer if the estimated size of the "
				 "data to be returned is smaller, would cause "
				 "the process to exceed its per-process locked "
				 "memory limit.",
				 "socket failure - "
				 "Insufficient memory was available to fulfill "
				 "the request.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOTDIR,
				 "sysctl failure - "
				 "The 'mib_name' array specifies an "
				 "intermediate rather than terminal name.")
	FAIL_SWITCH_ERRNO_CASE_1(EISDIR,
				 "sysctl failure - "
				 "The 'mib_name' array specifies a terminal "
				 "name, but the actual name is not terminal.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOENT,
				 "sysctl failure - "
				 "The 'mib_name' array specifies a value that "
				 "is unknown.")
	FAIL_SWITCH_ERRNO_CASE_2(EPERM,
				 "sysctl failure - "
				 "An attempt is made to set a read-only value.",
				 "sysctl failure - "
				 "A process without appropriate privilege "
				 "attempts to set a value.")
	FAIL_SWITCH_ERRNO_CASE_1(EACCES,
				 "socket failure - "
				 "Permission to create a socket of the "
				 "specified type and/or protocol is denied.")
	FAIL_SWITCH_ERRNO_CASE_1(EAFNOSUPPORT,
				 "socket failure - "
				 "The specified address family is not supported"
				 ".")
	FAIL_SWITCH_ERRNO_CASE_1(EMFILE,
				 "socket failure - "
				 "The per-process descriptor table is full.")
	FAIL_SWITCH_ERRNO_CASE_1(ENFILE,
				 "socket failure - "
				 "The system file table is full.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOBUFS,
				 "socket failure - "
				 "Insufficient buffer space is available. The "
				 "socket cannot be created until sufficient "
				 "resources are freed.")
	FAIL_SWITCH_ERRNO_CASE_1(EPROTONOSUPPORT,
				 "socket failure - "
				 "The protocol type or the specified protocol "
				 "is not supported within this domain.")
	FAIL_SWITCH_ERRNO_CASE_1(EPROTOTYPE,
				 "socket failure - "
				 "The socket type is not supported by the "
				 "protocol.")
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "ioctl failure - "
				 "'device_descriptor', is not a valid "
				 "descriptor.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTTY,
				 "ioctl failure - "
				 "'device_descriptor' is not associated with a "
				 "character special device.",
				 "The specified iotcl configuration 'SIOCGIFCONF' "
				 "does not apply to the kind of object that the"
				 " descriptor 'device_descriptor' references.")
	FAIL_SWITCH_ERRNO_CASE_1(ENXIO,
				 "no interface found for 'name'")
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

inline void
interface_name_to_index_handle(int *const restrict index,
			       const char *const restrict name,
			       Handler *const handle,
			       void *arg)
{
	const char *restrict failure;

	if (LIKELY(interface_name_to_index_report(index,
						  name,
						  &failure)))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
interface_name_to_index_handle_cl(int *const restrict index,
				  const char *const restrict name,
				  const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (LIKELY(interface_name_to_index_report(index,
						  name,
						  &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}



/* get_interface_networks */
inline bool
get_interface_networks_status(struct ifconf *const restrict configuration,
			      const int device_descriptor)
{
	return get_interface_networks_imp(configuration,
					  device_descriptor) != -1;
}

inline void
get_interface_networks_muffle(struct ifconf *const restrict configuration,
			      const int device_descriptor)
{
	(void) get_interface_networks_imp(configuration,
					  device_descriptor);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE get_interface_networks_imp
inline bool
get_interface_networks_report(struct ifconf *const restrict configuration,
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
get_interface_networks_handle(struct ifconf *const restrict configuration,
			      const int device_descriptor,
			      Handler *const handle,
			      void *arg)
{
	const char *restrict failure;

	if (LIKELY(get_interface_networks_report(configuration,
						 device_descriptor,
						 &failure)))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
get_interface_networks_handle_cl(struct ifconf *const restrict configuration,
				 const int device_descriptor,
				 const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (LIKELY(get_interface_networks_report(configuration,
						 device_descriptor,
						 &failure)))
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

	if (LIKELY(get_device_active_flags_report(request,
						  device_descriptor,
						  &failure)))
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

	if (LIKELY(get_device_active_flags_report(request,
						  device_descriptor,
						  &failure)))
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

	if (LIKELY(get_winsize_report(window,
				      file_descriptor,
				      &failure)))
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

	if (LIKELY(get_winsize_report(window,
				      file_descriptor,
				      &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}
#endif /* ifdef WIN32 */


#ifdef LINUX
/* get_interface_index */
inline bool
get_interface_index_status(struct ifreq *const restrict request,
			   const int device_descriptor)
{
	return get_interface_index_imp(request,
				       device_descriptor) != -1;
}

inline void
get_interface_index_muffle(struct ifreq *const restrict request,
			   const int device_descriptor)
{
	(void) get_interface_index_imp(request,
				       device_descriptor);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE get_interface_index_imp
inline bool
get_interface_index_report(struct ifreq *const restrict request,
			   const int device_descriptor,
			   const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(request,
			       device_descriptor)
	FAIL_SWITCH_ERRNO_CASE_1(EBADF,
				 "'device_descriptor', is not a valid "
				 "descriptor.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "'request' or ioctl request 'SIOCGIFINDEX' is"
				 " not valid.")
	FAIL_SWITCH_ERRNO_CASE_2(ENOTTY,
				 "'device_descriptor' is not associated with a "
				 "character special device.",
				 "The specified iotcl request 'SIOCGIFINDEX' "
				 "does not apply to the kind of object that the"
				 " descriptor 'device_descriptor' references.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
get_interface_index_handle(struct ifreq *const restrict request,
			   const int device_descriptor,
			   Handler *const handle,
			   void *arg)
{
	const char *restrict failure;

	if (LIKELY(get_interface_index_report(request,
					      device_descriptor,
					      &failure)))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
get_interface_index_handle_cl(struct ifreq *const restrict request,
			      const int device_descriptor,
			      const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (LIKELY(get_interface_index_report(request,
					      device_descriptor,
					      &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}


/* get_hardware_address */
inline bool
get_hardware_address_status(struct ifreq *const restrict request,
			    const int device_descriptor)
{
	return get_hardware_address_imp(request,
					device_descriptor) != -1;
}

inline void
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

	if (LIKELY(get_hardware_address_report(request,
					       device_descriptor,
					       &failure)))
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

	if (LIKELY(get_hardware_address_report(request,
					       device_descriptor,
					       &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}
#endif /* ifdef LINUX */

#ifdef OSX
/* sysctl */
inline bool
sysctl_status(int *const restrict mib_name,
	      u_int length_name,
	      void *const restrict old_data,
	      size_t *const restrict size_old_data,
	      void *const restrict new_data,
	      const size_t size_new_data)
{
	return sysctl(mib_name,
		      length_name,
		      old_data,
		      size_old_data,
		      new_data,
		      size_new_data) == 0;
}

inline void
sysctl_muffle(int *const restrict mib_name,
	      u_int length_name,
	      void *const restrict old_data,
	      size_t *const restrict size_old_data,
	      void *const restrict new_data,
	      const size_t size_new_data)
{
	(void) sysctl(mib_name,
		      length_name,
		      old_data,
		      size_old_data,
		      new_data,
		      size_new_data);
}


#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE sysctl
inline bool
sysctl_report(int *const restrict mib_name,
	      u_int length_name,
	      void *const restrict old_data,
	      size_t *const restrict size_old_data,
	      void *const restrict new_data,
	      const size_t size_new_data,
	      const char *restrict *const restrict failure)
{
	FAIL_SWITCH_ERRNO_OPEN(mib_name,
			       length_name,
			       old_data,
			       size_old_data,
			       new_data,
			       size_new_data)
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "The buffer 'mib_name', 'old_data', 'new_data'"
				 ", or length pointer 'size_old_data' contains "
				 "an invalid address.")
	FAIL_SWITCH_ERRNO_CASE_2(EINVAL,
				 "The 'mib_name' array is less than two or "
				 "greater than 'CTL_MAXNAME'.",
				 "A non-null 'new_data' is given and its "
				 "specified length in 'size_new_data' is too "
				 "large or too small.")
	FAIL_SWITCH_ERRNO_CASE_3(ENOMEM,
				 "The length pointed to by 'size_old_data' is "
				 "too short to hold the requested value.",
				 "The smaller of either the length pointed to "
				 "by 'size_old_data' or the estimated size of "
				 "the returned data exceeds the system limit on"
				 " locked memory.",
				 "Locking the buffer 'old_data', or a portion "
				 "of the buffer if the estimated size of the "
				 "data to be returned is smaller, would cause "
				 "the process to exceed its per-process locked "
				 "memory limit.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOTDIR,
				 "The 'mib_name' array specifies an "
				 "intermediate rather than terminal name.")
	FAIL_SWITCH_ERRNO_CASE_1(EISDIR,
				 "The 'mib_name' array specifies a terminal "
				 "name, but the actual name is not terminal.")
	FAIL_SWITCH_ERRNO_CASE_1(ENOENT,
				 "The 'mib_name' array specifies a value that "
				 "is unknown.")
	FAIL_SWITCH_ERRNO_CASE_2(EPERM,
				 "An attempt is made to set a read-only value.",
				 "A process without appropriate privilege "
				 "attempts to set a value.")
	FAIL_SWITCH_ERRNO_CLOSE()
}

inline void
sysctl_handle(int *const restrict mib_name,
	      u_int length_name,
	      void *const restrict old_data,
	      size_t *const restrict size_old_data,
	      void *const restrict new_data,
	      const size_t size_new_data,
	      Handler *const handle,
	      void *arg)
{
	const char *restrict failure;

	if (LIKELY(sysctl_report(mib_name,
				 length_name,
				 old_data,
				 size_old_data,
				 new_data,
				 size_new_data,
				 &failure)))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
sysctl_handle_cl(int *const restrict mib_name,
		 u_int length_name,
		 void *const restrict old_data,
		 size_t *const restrict size_old_data,
		 void *const restrict new_data,
		 const size_t size_new_data,
		 const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (LIKELY(sysctl_report(mib_name,
				 length_name,
				 old_data,
				 size_old_data,
				 new_data,
				 size_new_data,
				 &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}
#endif /* ifdef OSX */

#ifndef WIN32
/* getaddrinfo */
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
#undef	FAIL_SWITCH_STATUS_SUCCESS
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
#ifdef EAI_BADHINTS
	FAIL_SWITCH_STATUS_CASE_1(EAI_BADHINTS,
				  "invalid value for 'hints'")
#endif /* ifdef EAI_BADHINTS */
#ifdef EAI_PROTOCOL
	FAIL_SWITCH_STATUS_CASE_1(EAI_PROTOCOL,
				  "resolved protocol is unknown")
#endif /* ifdef EAI_PROTOCOL */
#ifdef EAI_OVERFLOW
	FAIL_SWITCH_STATUS_CASE_1(EAI_OVERFLOW,
				  "argument buffer overflow")
#endif /* ifdef EAI_OVERFLOW */
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

	if (LIKELY(getaddrinfo_report(node,
				      service,
				      hints,
				      result,
				      &failure)))
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

	if (LIKELY(getaddrinfo_report(node,
				      service,
				      hints,
				      result,
				      &failure)))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}
#endif /* ifndef WIN32 */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS */

/* undefine FAIL_SWITCH macro constants */
#undef FAIL_SWITCH_ROUTINE
#undef FAIL_SWITCH_ERRNO_FAILURE
#undef FAIL_SWITCH_FAILURE_POINTER

#endif /* ifndef MYSQL_SEED_SYSTEM_SYSTEM_UTILS_H_ */
