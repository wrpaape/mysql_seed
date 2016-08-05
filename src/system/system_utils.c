#include "system/system_utils.h"

/* socket */
extern inline bool
socket_status(int *const restrict socket_descriptor,
	      const int domain,
	      const int type,
	      const int protocol);
extern inline void
socket_muffle(int *const restrict socket_descriptor,
	      const int domain,
	      const int type,
	      const int protocol);
extern inline bool
socket_report(int *const restrict socket_descriptor,
	      const int domain,
	      const int type,
	      const int protocol,
	      const char *restrict *const restrict failure);
extern inline void
socket_handle(int *const restrict socket_descriptor,
	      const int domain,
	      const int type,
	      const int protocol,
	      Handler *const handle,
	      void *arg);
extern inline void
socket_handle_cl(int *const restrict socket_descriptor,
		 const int domain,
		 const int type,
		 const int protocol,
		 const struct HandlerClosure *const restrict fail_cl);

#ifdef WIN32
/* size_adapters_addresses */
extern inline bool
size_adapters_addresses_status(ULONG family,
			       ULONG flags,
			       PVOID reserved,
			       PULONG size_pointer);
extern inline void
size_adapters_addresses_muffle(ULONG family,
			       ULONG flags,
			       PVOID reserved,
			       PULONG size_pointer);
extern inline bool
size_adapters_addresses_report(ULONG family,
			       ULONG flags,
			       PVOID reserved,
			       PULONG size_pointer);
extern inline void
size_adapters_addresses_handle(ULONG family,
			       ULONG flags,
			       PVOID reserved,
			       PULONG size_pointer,
			       Handler *const handle,
			       void *arg);
extern inline void
size_adapters_addresses_handle_cl(ULONG family,
				  ULONG flags,
				  PVOID reserved,
				  PULONG size_pointer,
				  const struct HandlerClosure *const restrict fail_cl);

/* get_adapters_addresses */
extern inline bool
get_adapters_addresses_status(ULONG family,
			      ULONG flags,
			      PVOID reserved,
			      PIP_ADAPTER_ADDRESSES adapter_addresses,
			      PULONG size_pointer);
extern inline void
get_adapters_addresses_muffle(ULONG family,
			      ULONG flags,
			      PVOID reserved,
			      PIP_ADAPTER_ADDRESSES adapter_addresses,
			      PULONG size_pointer);
extern inline bool
get_adapters_addresses_report(ULONG family,
			      ULONG flags,
			      PVOID reserved,
			      PIP_ADAPTER_ADDRESSES adapter_addresses,
			      PULONG size_pointer,
			      const char *restrict *const restrict failure);
extern inline void
get_adapters_addresses_handle(ULONG family,
			      ULONG flags,
			      PVOID reserved,
			      PIP_ADAPTER_ADDRESSES adapter_addresses,
			      PULONG size_pointer,
			      Handler *const handle,
			      void *arg);
extern inline void
get_adapters_addresses_handle_cl(ULONG family,
				 ULONG flags,
				 PVOID reserved,
				 PIP_ADAPTER_ADDRESSES adapter_addresses,
				 PULONG size_pointer,
				 const struct HandlerClosure *const restrict fail_cl);
#else
/* sysctl */
extern inline bool
sysctl_status(int *const restrict mib_name,
	      u_int length_name,
	      void *const restrict old_data,
	      size_t *const restrict size_old_data,
	      void *const restrict new_data,
	      const size_t size_new_data);
extern inline void
sysctl_muffle(int *const restrict mib_name,
	      u_int length_name,
	      void *const restrict old_data,
	      size_t *const restrict size_old_data,
	      void *const restrict new_data,
	      const size_t size_new_data);
extern inline bool
sysctl_report(int *const restrict mib_name,
	      u_int length_name,
	      void *const restrict old_data,
	      size_t *const restrict size_old_data,
	      void *const restrict new_data,
	      const size_t size_new_data,
	      const char *restrict *const restrict failure);
extern inline void
sysctl_handle(int *const restrict mib_name,
	      u_int length_name,
	      void *const restrict old_data,
	      size_t *const restrict size_old_data,
	      void *const restrict new_data,
	      const size_t size_new_data,
	      Handler *const handle,
	      void *arg);
extern inline void
sysctl_handle_cl(int *const restrict mib_name,
		 u_int length_name,
		 void *const restrict old_data,
		 size_t *const restrict size_old_data,
		 void *const restrict new_data,
		 const size_t size_new_data,
		 const struct HandlerClosure *const restrict fail_cl);

/* interface_name_to_index */
extern inline bool
interface_name_to_index_status(int *const restrict index,
			       const char *const restrict name);
extern inline void
interface_name_to_index_muffle(int *const restrict index,
			       const char *const restrict name);
extern inline bool
interface_name_to_index_report(int *const restrict index,
			       const char *const restrict name,
			       const char *restrict *const restrict failure);
extern inline void
interface_name_to_index_handle(int *const restrict index,
			       const char *const restrict name,
			       Handler *const handle,
			       void *arg);
extern inline void
interface_name_to_index_handle_cl(int *const restrict index,
				  const char *const restrict name,
				  const struct HandlerClosure *const restrict fail_cl);



/* get_interface_networks */
extern inline bool
get_interface_networks_status(struct ifconf *const restrict configuration,
			      const int device_descriptor);
extern inline void
get_interface_networks_muffle(struct ifconf *const restrict configuration,
			      const int device_descriptor);
extern inline bool
get_interface_networks_report(struct ifconf *const restrict configuration,
			      const int device_descriptor,
			      const char *restrict *const restrict failure);
extern inline void
get_interface_networks_handle(struct ifconf *const restrict configuration,
			      const int device_descriptor,
			      Handler *const handle,
			      void *arg);
extern inline void
get_interface_networks_handle_cl(struct ifconf *const restrict configuration,
				 const int device_descriptor,
				 const struct HandlerClosure *const restrict fail_cl);

/* get_device_active_flags */
extern inline bool
get_device_active_flags_status(struct ifreq *const restrict request,
			       const int device_descriptor);
extern inline void
get_device_active_flags_muffle(struct ifreq *const restrict request,
			       const int device_descriptor);
extern inline bool
get_device_active_flags_report(struct ifreq *const restrict request,
			       const int device_descriptor,
			       const char *restrict *const restrict failure);
extern inline void
get_device_active_flags_handle(struct ifreq *const restrict request,
			       const int device_descriptor,
			       Handler *const handle,
			       void *arg);
extern inline void
get_device_active_flags_handle_cl(struct ifreq *const restrict request,
				  const int device_descriptor,
				  const struct HandlerClosure *const restrict fail_cl);

/* get_winsize */
extern inline bool
get_winsize_status(struct winsize *const restrict window,
		   const int file_descriptor);
extern inline void
get_winsize_muffle(struct winsize *const restrict window,
		   const int file_descriptor);
extern inline bool
get_winsize_report(struct winsize *const restrict window,
		   const int file_descriptor,
		   const char *restrict *const restrict failure);
extern inline void
get_winsize_handle(struct winsize *const restrict window,
		   const int file_descriptor,
		   Handler *const handle,
		   void *arg);
extern inline void
get_winsize_handle_cl(struct winsize *const restrict window,
		      const int file_descriptor,
		      const struct HandlerClosure *const restrict fail_cl);
#endif /* ifdef WIN32 */

#ifdef LINUX
/* get_interface_index */
extern inline bool
get_interface_index_status(struct ifreq *const restrict request,
			   const int device_descriptor);
extern inline void
get_interface_index_muffle(struct ifreq *const restrict request,
			   const int device_descriptor);
extern inline bool
get_interface_index_report(struct ifreq *const restrict request,
			   const int device_descriptor,
			   const char *restrict *const restrict failure);
extern inline void
get_interface_index_handle(struct ifreq *const restrict request,
			   const int device_descriptor,
			   Handler *const handle,
			   void *arg);
extern inline void
get_interface_index_handle_cl(struct ifreq *const restrict request,
			      const int device_descriptor,
			      const struct HandlerClosure *const restrict fail_cl);

/* get_hardware_address */
extern inline bool
get_hardware_address_status(struct ifreq *const restrict request,
			    const int device_descriptor);
extern inline void
get_hardware_address_muffle(struct ifreq *const restrict request,
			    const int device_descriptor);
extern inline bool
get_hardware_address_report(struct ifreq *const restrict request,
			    const int device_descriptor,
			    const char *restrict *const restrict failure);
extern inline void
get_hardware_address_handle(struct ifreq *const restrict request,
			    const int device_descriptor,
			    Handler *const handle,
			    void *arg);
extern inline void
get_hardware_address_handle_cl(struct ifreq *const restrict request,
			       const int device_descriptor,
			       const struct HandlerClosure *const restrict fail_cl);
#endif /* ifdef LINUX */


/* getaddrinfo */
extern inline bool
getaddrinfo_status(const char *const node,
		   const char *const service,
		   const struct addrinfo *const hints,
		   struct addrinfo **const result);
extern inline void
getaddrinfo_muffle(const char *const node,
		   const char *const service,
		   const struct addrinfo *const hints,
		   struct addrinfo **const result);
extern inline bool
getaddrinfo_report(const char *const node,
		   const char *const service,
		   const struct addrinfo *const hints,
		   struct addrinfo **const result,
		   const char *restrict *const restrict failure);
extern inline void
getaddrinfo_handle(const char *const node,
		   const char *const service,
		   const struct addrinfo *const hints,
		   struct addrinfo **const result,
		   Handler *const handle,
		   void *arg);
extern inline void
getaddrinfo_handle_cl(const char *const node,
		      const char *const service,
		      const struct addrinfo *const hints,
		      struct addrinfo **const result,
		      const struct HandlerClosure *const restrict fail_cl);
