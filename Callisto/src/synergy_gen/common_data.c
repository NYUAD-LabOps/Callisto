/* generated common source file - do not edit */
#include "common_data.h"

#ifndef NX_DISABLE_IPV6
#ifndef FILL_NXD_IPV6_ADDRESS
#define FILL_NXD_IPV6_ADDRESS(ipv6,f0,f1,f2,f3,f4,f5,f6,f7) do { \
                                                                       ipv6.nxd_ip_address.v6[0] = (((uint32_t)f0 << 16) & 0xFFFF0000) | ((uint32_t)f1 & 0x0000FFFF);\
                                                                       ipv6.nxd_ip_address.v6[1] = (((uint32_t)f2 << 16) & 0xFFFF0000) | ((uint32_t)f3 & 0x0000FFFF);\
                                                                       ipv6.nxd_ip_address.v6[2] = (((uint32_t)f4 << 16) & 0xFFFF0000) | ((uint32_t)f5 & 0x0000FFFF);\
                                                                       ipv6.nxd_ip_address.v6[3] = (((uint32_t)f6 << 16) & 0xFFFF0000) | ((uint32_t)f7 & 0x0000FFFF);\
                                                                       ipv6.nxd_ip_version       = NX_IP_VERSION_V6;\
                                                                   } while(0);
#endif /* FILL_NXD_IPV6_ADDRESS */
#endif
NX_REC nx_record1;
static NX_CALLBACK_REC g_sf_el_nx_callbacks =
{ .nx_ether_unknown_packet_receive_callback = NULL, .nx_ether_mac_address_change_callback = NULL, };
static sf_el_nx_cfg_t sf_el_nx1_cfg =
{ .channel = 1, .nx_mac_address =
{ .nx_mac_address_h = SF_EL_NX_CFG_ENET1_MAC_H, .nx_mac_address_l = SF_EL_NX_CFG_ENET1_MAC_L },
  .p_callback_rec = &g_sf_el_nx_callbacks, .etherc_ptr = R_ETHERC1, .edmac_ptr = R_EDMAC1, };
#if SF_EL_NX_CFG_IRQ_IPL != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_sf_el_nx) && !defined(SSP_SUPPRESS_ISR_EDMAC1)
SSP_VECTOR_DEFINE_CHAN(edmac_eint_isr, EDMAC, EINT, 1);
#endif
#endif

void nx_ether_driver_eth1(NX_IP_DRIVER *driver_req_ptr)
{
    nx_ether_driver (driver_req_ptr, &nx_record1, &sf_el_nx1_cfg);
}

/** Make user given name point to correct driver entry point. */
VOID (*g_sf_el_nx)(NX_IP_DRIVER *driver_req_ptr) = nx_ether_driver_eth1;
/*******************************************************************************************************************//**
 * @brief     Initialization function that the user can choose to have called automatically during thread entry.
 *            The user can call this function at a later time if desired using the prototype below.
 *            - void nx_common_init0(void)
 **********************************************************************************************************************/
void nx_common_init0(void)
{
    /** Initialize the NetX Duo system. */
    nx_system_initialize ();
}
NX_PACKET_POOL g_packet_pool0;
uint8_t g_packet_pool0_pool_memory[(16 * (1568 + sizeof(NX_PACKET)))];
#if defined(__ICCARM__)
#define g_packet_pool0_err_callback_WEAK_ATTRIBUTE
#pragma weak g_packet_pool0_err_callback  = g_packet_pool0_err_callback_internal
#elif defined(__GNUC__)
#define g_packet_pool0_err_callback_WEAK_ATTRIBUTE   __attribute__ ((weak, alias("g_packet_pool0_err_callback_internal")))
#endif
void g_packet_pool0_err_callback(void *p_instance, void *p_data)
g_packet_pool0_err_callback_WEAK_ATTRIBUTE;
/*******************************************************************************************************************//**
 * @brief      This is a weak example initialization error function.  It should be overridden by defining a user  function
 *             with the prototype below.
 *             - void g_packet_pool0_err_callback(void * p_instance, void * p_data)
 *
 * @param[in]  p_instance arguments used to identify which instance caused the error and p_data Callback arguments used to identify what error caused the callback.
 **********************************************************************************************************************/
void g_packet_pool0_err_callback_internal(void *p_instance, void *p_data);
void g_packet_pool0_err_callback_internal(void *p_instance, void *p_data)
{
    /** Suppress compiler warning for not using parameters. */
    SSP_PARAMETER_NOT_USED (p_instance);
    SSP_PARAMETER_NOT_USED (p_data);

    /** An error has occurred. Please check function arguments for more information. */
    BSP_CFG_HANDLE_UNRECOVERABLE_ERROR (0);
}
/*******************************************************************************************************************//**
 * @brief     Initialization function that the user can choose to have called automatically during thread entry.
 *            The user can call this function at a later time if desired using the prototype below.
 *            - void packet_pool_init0(void)
 **********************************************************************************************************************/
void packet_pool_init0(void)
{
    UINT g_packet_pool0_err;
    /* Create Client packet pool. */
    g_packet_pool0_err = nx_packet_pool_create (&g_packet_pool0, "g_packet_pool0 Packet Pool", 1568,
                                                &g_packet_pool0_pool_memory[0], (16 * (1568 + sizeof(NX_PACKET))));
    if (NX_SUCCESS != g_packet_pool0_err)
    {
        g_packet_pool0_err_callback ((void *) &g_packet_pool0, &g_packet_pool0_err);
    }
}
NX_IP g_ip0;
#ifndef NX_DISABLE_IPV6
UINT g_ip0_interface_index = 0;
UINT g_ip0_address_index;
NXD_ADDRESS g_ip0_global_ipv6_address;
NXD_ADDRESS g_ip0_local_ipv6_address;
#endif            
uint8_t g_ip0_stack_memory[4096] BSP_PLACE_IN_SECTION_V2(".stack.g_ip0") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
#if 1 == 1                       // Check for ARP is enabled
#if (0 == 0)    // Check for ARP cache storage units is in bytes
#define    NX_ARP_CACHE_SIZE    (520)
#else
#define    NX_ARP_CACHE_SIZE    (520 * sizeof(NX_ARP))
#endif
uint8_t g_ip0_arp_cache_memory[NX_ARP_CACHE_SIZE] BSP_ALIGN_VARIABLE(4);
#endif
ULONG g_ip0_actual_status;

#ifndef NULL
#define NULL_DEFINE
void NULL(struct NX_IP_STRUCT *ip_ptr, UINT interface_index, UINT link_up);
#endif            
#if defined(__ICCARM__)
#define g_ip0_err_callback_WEAK_ATTRIBUTE
#pragma weak g_ip0_err_callback  = g_ip0_err_callback_internal
#elif defined(__GNUC__)
#define g_ip0_err_callback_WEAK_ATTRIBUTE   __attribute__ ((weak, alias("g_ip0_err_callback_internal")))
#endif
void g_ip0_err_callback(void *p_instance, void *p_data)
g_ip0_err_callback_WEAK_ATTRIBUTE;
/*******************************************************************************************************************//**
 * @brief      This is a weak example initialization error function.  It should be overridden by defining a user  function
 *             with the prototype below.
 *             - void g_ip0_err_callback(void * p_instance, void * p_data)
 *
 * @param[in]  p_instance arguments used to identify which instance caused the error and p_data Callback arguments used to identify what error caused the callback.
 **********************************************************************************************************************/
void g_ip0_err_callback_internal(void *p_instance, void *p_data);
void g_ip0_err_callback_internal(void *p_instance, void *p_data)
{
    /** Suppress compiler warning for not using parameters. */
    SSP_PARAMETER_NOT_USED (p_instance);
    SSP_PARAMETER_NOT_USED (p_data);

    /** An error has occurred. Please check function arguments for more information. */
    BSP_CFG_HANDLE_UNRECOVERABLE_ERROR (0);
}

/*******************************************************************************************************************//**
 * @brief     Initialization function that the user can choose to have called automatically during thread entry.
 *            The user can call this function at a later time if desired using the prototype below.
 *            - void ip_init0(void)
 **********************************************************************************************************************/
void ip_init0(void)
{
    UINT g_ip0_err;
#ifndef NX_DISABLE_IPV6
    FILL_NXD_IPV6_ADDRESS(g_ip0_global_ipv6_address, 0x2001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1);
    FILL_NXD_IPV6_ADDRESS(g_ip0_local_ipv6_address, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);

#endif
    /* Create an IP instance. */
    g_ip0_err = nx_ip_create (&g_ip0, "g_ip0 IP Instance", IP_ADDRESS (192, 168, 10, 182),
                              IP_ADDRESS (255, 255, 255, 0), &g_packet_pool0, g_sf_el_nx, &g_ip0_stack_memory[0], 4096,
                              0);
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback ((void *) &g_ip0, &g_ip0_err);
    }
#define SYNERGY_NOT_DEFINED     (0xFFFFFFFF)
#if (SYNERGY_NOT_DEFINED != 1)
    g_ip0_err = nx_arp_enable (&g_ip0, &g_ip0_arp_cache_memory[0], NX_ARP_CACHE_SIZE);
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback ((void *) &g_ip0, &g_ip0_err);
    }
#endif
#if (SYNERGY_NOT_DEFINED != SYNERGY_NOT_DEFINED)
    g_ip0_err = nx_rarp_enable(&g_ip0);
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback((void *)&g_ip0,&g_ip0_err);
    }
#endif
#if (SYNERGY_NOT_DEFINED != 1)
    g_ip0_err = nx_tcp_enable (&g_ip0);
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback ((void *) &g_ip0, &g_ip0_err);
    }
#endif
#if (SYNERGY_NOT_DEFINED != 1)
    g_ip0_err = nx_udp_enable (&g_ip0);
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback ((void *) &g_ip0, &g_ip0_err);
    }
#endif
#if (SYNERGY_NOT_DEFINED != 1)
    g_ip0_err = nx_icmp_enable (&g_ip0);
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback ((void *) &g_ip0, &g_ip0_err);
    }
#endif
#if (SYNERGY_NOT_DEFINED != 1)
    g_ip0_err = nx_igmp_enable (&g_ip0);
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback ((void *) &g_ip0, &g_ip0_err);
    }
#endif
#if (SYNERGY_NOT_DEFINED != SYNERGY_NOT_DEFINED)
    g_ip0_err = nx_ip_fragment_enable(&g_ip0);
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback((void *)&g_ip0,&g_ip0_err);
    }
#endif            
#undef SYNERGY_NOT_DEFINED

#ifndef NX_DISABLE_IPV6
    /** Here's where IPv6 is enabled. */
    g_ip0_err = nxd_ipv6_enable (&g_ip0);
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback ((void *) &g_ip0, &g_ip0_err);
    }
    g_ip0_err = nxd_icmp_enable (&g_ip0);
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback ((void *) &g_ip0, &g_ip0_err);
    }
    /* Wait for link to be initialized so MAC address is valid. */
    /** Wait for init to finish. */
    g_ip0_err = nx_ip_interface_status_check (&g_ip0, 0, NX_IP_INITIALIZE_DONE, &g_ip0_actual_status, NX_WAIT_FOREVER);
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback ((void *) &g_ip0, &g_ip0_err);
    }
    /** Setting link local address */
    if (0x0
            == (g_ip0_local_ipv6_address.nxd_ip_address.v6[0] | g_ip0_local_ipv6_address.nxd_ip_address.v6[1]
                    | g_ip0_local_ipv6_address.nxd_ip_address.v6[2] | g_ip0_local_ipv6_address.nxd_ip_address.v6[3]))
    {
        g_ip0_err = nxd_ipv6_address_set (&g_ip0, g_ip0_interface_index, NX_NULL, 10, NX_NULL);
    }
    else
    {
        g_ip0_err = nxd_ipv6_address_set (&g_ip0, g_ip0_interface_index, &g_ip0_local_ipv6_address, 10,
                                          &g_ip0_address_index);
    }
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback ((void *) &g_ip0, &g_ip0_err);
    }
    if (0x0
            != (g_ip0_global_ipv6_address.nxd_ip_address.v6[0] | g_ip0_global_ipv6_address.nxd_ip_address.v6[1]
                    | g_ip0_global_ipv6_address.nxd_ip_address.v6[2] | g_ip0_global_ipv6_address.nxd_ip_address.v6[3]))
    {
        g_ip0_err = nxd_ipv6_address_set (&g_ip0, g_ip0_interface_index, &g_ip0_global_ipv6_address, 64,
                                          &g_ip0_address_index);
    }
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback ((void *) &g_ip0, &g_ip0_err);
    }
#endif

#ifdef NULL_DEFINE
    g_ip0_err = nx_ip_link_status_change_notify_set (&g_ip0, NULL);
    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback ((void *) &g_ip0, &g_ip0_err);
    }
#endif

    /* Gateway IP Address */
#define IP_VALID(a,b,c,d)     (a|b|c|d)
#if IP_VALID(0,0,0,0)
    g_ip0_err = nx_ip_gateway_address_set(&g_ip0,
            IP_ADDRESS(0,0,0,0));

    if (NX_SUCCESS != g_ip0_err)
    {
        g_ip0_err_callback((void *)&g_ip0,&g_ip0_err);
    }
#endif         
#undef IP_VALID

}
const elc_instance_t g_elc =
{ .p_api = &g_elc_on_elc, .p_cfg = NULL };
const ioport_instance_t g_ioport =
{ .p_api = &g_ioport_on_ioport, .p_cfg = NULL };
const cgc_instance_t g_cgc =
{ .p_api = &g_cgc_on_cgc, .p_cfg = NULL };
/* Instance structure to use this module. */
const fmi_instance_t g_fmi =
{ .p_api = &g_fmi_on_fmi };
void g_common_init(void)
{
    /** Call initialization function if user has selected to do so. */
#if (1)
    nx_common_init0 ();
#endif
    /** Call initialization function if user has selected to do so. */
#if (1)
    packet_pool_init0 ();
#endif
    /** Call initialization function if user has selected to do so. */
#if (0)
    ip_init0();
#endif
}
