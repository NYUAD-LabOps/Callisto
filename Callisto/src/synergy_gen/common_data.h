/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "nx_api.h"
#include "sf_el_nx_cfg.h"
#include "../src/framework/sf_el_nx/nx_renesas_synergy.h"
#include "nx_api.h"

#include "r_elc.h"
#include "r_elc_api.h"
#include "r_ioport.h"
#include "r_ioport_api.h"
#include "r_cgc.h"
#include "r_cgc_api.h"
#include "r_fmi.h"
#include "r_fmi_api.h"
#ifdef __cplusplus
extern "C"
{
#endif
#ifndef NULL
void NULL(nx_mac_address_t *p_mac_config);
#endif
#ifndef NULL
void NULL(NX_PACKET *packet_ptr, USHORT packet_type);
#endif
VOID nx_ether_driver_eth1(NX_IP_DRIVER *driver_req_ptr);
extern VOID (*g_sf_el_nx)(NX_IP_DRIVER *driver_req_ptr);
void nx_common_init0(void);
extern NX_PACKET_POOL g_packet_pool0;
void g_packet_pool0_err_callback(void *p_instance, void *p_data);
void packet_pool_init0(void);
extern NX_IP g_ip0;
void g_ip0_err_callback(void *p_instance, void *p_data);
void ip_init0(void);
/** ELC Instance */
extern const elc_instance_t g_elc;
/** IOPORT Instance */
extern const ioport_instance_t g_ioport;
/** CGC Instance */
extern const cgc_instance_t g_cgc;
/** FMI on FMI Instance. */
extern const fmi_instance_t g_fmi;
void g_common_init(void);
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* COMMON_DATA_H_ */
