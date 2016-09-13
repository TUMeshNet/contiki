/*
 *
 * This file is part of the Contiki operating system.
 *
 * \file
 *   Private declarations for ContikiSR.
 * \author
 *   James Novino <james.novino@temple.edu>
 */

#ifndef SR_PRIVATE_H
#define SR_PRIVATE_H

#include "net/sr/sr.h"

#include "lib/list.h"
#include "net/ip/uip.h"
#include "sys/clock.h"
#include "sys/ctimer.h"
#include "net/ipv6/uip-ds6.h"
#include "net/ipv6/uip-ds6-route.h"
#include "net/sr/sr-ns.h"
#include "net/ipv6/multicast/uip-mcast6.h"

/*---------------------------------------------------------------------------*/
/** \brief Is IPv6 address addr the link-local, all-SR-nodes
    multicast address? */
#define uip_is_addr_linklocal_srnodes_mcast(addr)	    \
  ((addr)->u8[0] == 0xff) &&				    \
  ((addr)->u8[1] == 0x02) &&				    \
  ((addr)->u16[1] == 0) &&				    \
  ((addr)->u16[2] == 0) &&				    \
  ((addr)->u16[3] == 0) &&				    \
  ((addr)->u16[4] == 0) &&				    \
  ((addr)->u16[5] == 0) &&				    \
  ((addr)->u16[6] == 0) &&				    \
  ((addr)->u8[14] == 0) &&				    \
  ((addr)->u8[15] == 0x1a))

/** \brief Set IP address addr to the link-local, all-sr-nodes
    multicast address. */
#define uip_create_linklocal_srnodes_mcast(addr)	\
  uip_ip6addr((addr), 0xff02, 0, 0, 0, 0, 0, 0, 0x001a)
/*---------------------------------------------------------------------------*/
/* SR message types */
#define SR_CODE_DIS                   0x00   /* DAG Information Solicitation */
#define SR_CODE_DIO                   0x01   /* DAG Information Option */
#define SR_CODE_DAO                   0x02   /* Destination Advertisement Option */
#define SR_CODE_DAO_ACK               0x03   /* DAO acknowledgment */
#define SR_CODE_SEC_DIS               0x80   /* Secure DIS */
#define SR_CODE_SEC_DIO               0x81   /* Secure DIO */
#define SR_CODE_SEC_DAO               0x82   /* Secure DAO */
#define SR_CODE_SEC_DAO_ACK           0x83   /* Secure DAO ACK */

/* SR control message options. */
#define SR_OPTION_PAD1                  0
#define SR_OPTION_PADN                  1
#define SR_OPTION_DAG_METRIC_CONTAINER  2
#define SR_OPTION_ROUTE_INFO            3
#define SR_OPTION_DAG_CONF              4
#define SR_OPTION_TARGET                5
#define SR_OPTION_TRANSIT               6
#define SR_OPTION_SOLICITED_INFO        7
#define SR_OPTION_PREFIX_INFO           8
#define SR_OPTION_TARGET_DESC           9

#define SR_DAO_K_FLAG                   0x80 /* DAO ACK requested */
#define SR_DAO_D_FLAG                   0x40 /* DODAG ID present */

#define SR_DAO_ACK_UNCONDITIONAL_ACCEPT 0
#define SR_DAO_ACK_ACCEPT               1   /* 1 - 127 is OK but not good */
#define SR_DAO_ACK_UNABLE_TO_ACCEPT     128 /* >127 is fail */
#define SR_DAO_ACK_UNABLE_TO_ADD_ROUTE_AT_ROOT 255 /* root can not accept */

#define SR_DAO_ACK_TIMEOUT              -1

/*---------------------------------------------------------------------------*/
/* SR IPv6 extension header option. */
#define SR_HDR_OPT_LEN			4
#define SR_HOP_BY_HOP_LEN		(SR_HDR_OPT_LEN + 2 + 2)
#define SR_RH_LEN     4
#define SR_SRH_LEN    4
#define SR_RH_TYPE_SRH   3
#define SR_HDR_OPT_DOWN		0x80
#define SR_HDR_OPT_DOWN_SHIFT  	7
#define SR_HDR_OPT_RANK_ERR		0x40
#define SR_HDR_OPT_RANK_ERR_SHIFT   	6
#define SR_HDR_OPT_FWD_ERR		0x20
#define SR_HDR_OPT_FWD_ERR_SHIFT   	5
/*---------------------------------------------------------------------------*/
/* Default values for SR constants and variables. */

/* DAO transmissions are always delayed by SR_DAO_DELAY +/- SR_DAO_DELAY/2 */
#ifdef SR_CONF_DAO_DELAY
#define SR_DAO_DELAY                 SR_CONF_DAO_DELAY
#else /* SR_CONF_DAO_DELAY */
#define SR_DAO_DELAY                 (CLOCK_SECOND * 4)
#endif /* SR_CONF_DAO_DELAY */

/* Delay between reception of a no-path DAO and actual route removal */
#ifdef SR_CONF_NOPATH_REMOVAL_DELAY
#define SR_NOPATH_REMOVAL_DELAY          SR_CONF_NOPATH_REMOVAL_DELAY
#else /* SR_CONF_NOPATH_REMOVAL_DELAY */
#define SR_NOPATH_REMOVAL_DELAY          60
#endif /* SR_CONF_NOPATH_REMOVAL_DELAY */

#ifdef SR_CONF_DAO_MAX_RETRANSMISSIONS
#define SR_DAO_MAX_RETRANSMISSIONS SR_CONF_DAO_MAX_RETRANSMISSIONS
#else
#define SR_DAO_MAX_RETRANSMISSIONS     5
#endif /* SR_CONF_DAO_MAX_RETRANSMISSIONS */

#ifdef SR_CONF_DAO_RETRANSMISSION_TIMEOUT
#define SR_DAO_RETRANSMISSION_TIMEOUT SR_CONF_DAO_RETRANSMISSION_TIMEOUT
#else
#define SR_DAO_RETRANSMISSION_TIMEOUT  (5 * CLOCK_SECOND)
#endif /* SR_CONF_DAO_RETRANSMISSION_TIMEOUT */

/* Special value indicating immediate removal. */
#define SR_ZERO_LIFETIME               0

#define SR_LIFETIME(instance, lifetime) \
          ((unsigned long)(instance)->lifetime_unit * (lifetime))

#ifndef SR_CONF_MIN_HOPRANKINC
/* RFC6550 defines the default MIN_HOPRANKINC as 256.
 * However, we use MRHOF as a default Objective Function (RFC6719),
 * which recommends setting MIN_HOPRANKINC with care, in particular
 * when used with ETX as a metric. ETX is computed as a fixed point
 * real with a divisor of 128 (RFC6719, RFC6551). We choose to also
 * use 128 for SR_MIN_HOPRANKINC, resulting in a rank equal to the
 * ETX path cost. Larger values may also be desirable, as discussed
 * in section 6.1 of RFC6719. */
#if SR_OF_OCP == SR_OCP_MRHOF
#define SR_MIN_HOPRANKINC          128
#else /* SR_OF_OCP == SR_OCP_MRHOF */
#define SR_MIN_HOPRANKINC          256
#endif /* SR_OF_OCP == SR_OCP_MRHOF */
#else /* SR_CONF_MIN_HOPRANKINC */
#define SR_MIN_HOPRANKINC          SR_CONF_MIN_HOPRANKINC
#endif /* SR_CONF_MIN_HOPRANKINC */

#ifndef SR_CONF_MAX_RANKINC
#define SR_MAX_RANKINC             (7 * SR_MIN_HOPRANKINC)
#else /* SR_CONF_MAX_RANKINC */
#define SR_MAX_RANKINC             SR_CONF_MAX_RANKINC
#endif /* SR_CONF_MAX_RANKINC */

#define DAG_RANK(fixpt_rank, instance) \
  ((fixpt_rank) / (instance)->min_hoprankinc)

/* Rank of a virtual root node that coordinates DAG root nodes. */
#define BASE_RANK                       0

/* Rank of a root node. */
#define ROOT_RANK(instance)             (instance)->min_hoprankinc

#define INFINITE_RANK                   0xffff

/*---------------------------------------------------------------------------*/
#define SR_INSTANCE_LOCAL_FLAG         0x80
#define SR_INSTANCE_D_FLAG             0x40

/* Values that tell where a route came from. */
#define SR_ROUTE_FROM_INTERNAL         0
#define SR_ROUTE_FROM_UNICAST_DAO      1
#define SR_ROUTE_FROM_MULTICAST_DAO    2
#define SR_ROUTE_FROM_DIO              3

/* DAG Mode of Operation */
#define SR_MOP_NO_DOWNWARD_ROUTES      0
#define SR_MOP_NON_STORING             1
#define SR_MOP_STORING_NO_MULTICAST    2
#define SR_MOP_STORING_MULTICAST       3

/* SR Mode of operation */
#ifdef  SR_CONF_MOP
#define SR_MOP_DEFAULT                 SR_CONF_MOP
#else /* SR_CONF_MOP */
#if SR_WITH_MULTICAST
#define SR_MOP_DEFAULT                 SR_MOP_STORING_MULTICAST
#else
#define SR_MOP_DEFAULT                 SR_MOP_STORING_NO_MULTICAST
#endif /* SR_WITH_MULTICAST */
#endif /* SR_CONF_MOP */

/*
 * Embed support for storing mode
 */
#ifdef SR_CONF_WITH_STORING
#define SR_WITH_STORING SR_CONF_WITH_STORING
#else /* SR_CONF_WITH_STORING */
/* By default: embed support for non-storing if and only if the configured MOP is not non-storing */
#define SR_WITH_STORING (SR_MOP_DEFAULT != SR_MOP_NON_STORING)
#endif /* SR_CONF_WITH_STORING */

/*
 * Embed support for non-storing mode
 */
#ifdef SR_CONF_WITH_NON_STORING
#define SR_WITH_NON_STORING SR_CONF_WITH_NON_STORING
#else /* SR_CONF_WITH_NON_STORING */
/* By default: embed support for non-storing if and only if the configured MOP is non-storing */
#define SR_WITH_NON_STORING (SR_MOP_DEFAULT == SR_MOP_NON_STORING)
#endif /* SR_CONF_WITH_NON_STORING */

#if SR_WITH_STORING && (UIP_DS6_ROUTE_NB == 0)
#error "SR with storing mode included but #routes == 0. Set UIP_CONF_MAX_ROUTES accordingly."
#if !SR_WITH_NON_STORING && (SR_NS_LINK_NUM > 0)
#error "You might also want to set SR_NS_CONF_LINK_NUM to 0."
#endif
#endif

#if SR_WITH_NON_STORING && (SR_NS_LINK_NUM == 0)
#error "SR with non-storing mode included but #links == 0. Set SR_NS_CONF_LINK_NUM accordingly."
#if !SR_WITH_STORING && (UIP_DS6_ROUTE_NB > 0)
#error "You might also want to set UIP_CONF_MAX_ROUTES to 0."
#endif
#endif

#define SR_IS_STORING(instance) (SR_WITH_STORING && ((instance) != NULL) && ((instance)->mop > SR_MOP_NON_STORING))
#define SR_IS_NON_STORING(instance) (SR_WITH_NON_STORING && ((instance) != NULL) && ((instance)->mop == SR_MOP_NON_STORING))

/* Emit a pre-processor error if the user configured multicast with bad MOP */
#if SR_WITH_MULTICAST && (SR_MOP_DEFAULT != SR_MOP_STORING_MULTICAST)
#error "SR Multicast requires SR_MOP_DEFAULT==3. Check contiki-conf.h"
#endif

/* Multicast Route Lifetime as a multiple of the lifetime unit */
#ifdef SR_CONF_MCAST_LIFETIME
#define SR_MCAST_LIFETIME SR_CONF_MCAST_LIFETIME
#else
#define SR_MCAST_LIFETIME 3
#endif

/* DIS related */
#define SR_DIS_SEND                    1

/*---------------------------------------------------------------------------*/
/* Lollipop counters */

#define SR_LOLLIPOP_MAX_VALUE           255
#define SR_LOLLIPOP_CIRCULAR_REGION     127
#define SR_LOLLIPOP_SEQUENCE_WINDOWS    16
#define SR_LOLLIPOP_INIT                (SR_LOLLIPOP_MAX_VALUE - SR_LOLLIPOP_SEQUENCE_WINDOWS + 1)
#define SR_LOLLIPOP_INCREMENT(counter)                                 \
  do {                                                                  \
    if((counter) > SR_LOLLIPOP_CIRCULAR_REGION) {                      \
      (counter) = ((counter) + 1) & SR_LOLLIPOP_MAX_VALUE;             \
    } else {                                                            \
      (counter) = ((counter) + 1) & SR_LOLLIPOP_CIRCULAR_REGION;       \
    }                                                                   \
  } while(0)

#define SR_LOLLIPOP_IS_INIT(counter)		\
  ((counter) > SR_LOLLIPOP_CIRCULAR_REGION)
/*---------------------------------------------------------------------------*/
/* Logical representation of a DAG Information Object (DIO.) */
struct sr_dio {
  uip_ipaddr_t dag_id;
  sr_ocp_t ocp;
  sr_rank_t rank;
  uint8_t grounded;
  uint8_t mop;
  uint8_t preference;
  uint8_t version;
  uint8_t instance_id;
  uint8_t dtsn;
  uint8_t dag_intdoubl;
  uint8_t dag_intmin;
  uint8_t dag_redund;
  uint8_t default_lifetime;
  uint16_t lifetime_unit;
  sr_rank_t dag_max_rankinc;
  sr_rank_t dag_min_hoprankinc;
  sr_prefix_t destination_prefix;
  sr_prefix_t prefix_info;
  struct sr_metric_container mc;
};
typedef struct sr_dio sr_dio_t;

#if SR_CONF_STATS
/* Statistics for fault management. */
struct sr_stats {
  uint16_t mem_overflows;
  uint16_t local_repairs;
  uint16_t global_repairs;
  uint16_t malformed_msgs;
  uint16_t resets;
  uint16_t parent_switch;
  uint16_t forward_errors;
  uint16_t loop_errors;
  uint16_t loop_warnings;
  uint16_t root_repairs;
};
typedef struct sr_stats sr_stats_t;

extern sr_stats_t sr_stats;
#endif


/*---------------------------------------------------------------------------*/
/* SR macros. */

#if SR_CONF_STATS
#define SR_STAT(code)	(code) 
#else
#define SR_STAT(code)
#endif /* SR_CONF_STATS */
/*---------------------------------------------------------------------------*/
/* Instances */
extern sr_instance_t instance_table[];
extern sr_instance_t *default_instance;

/* ICMPv6 functions for SR. */
void dis_output(uip_ipaddr_t *addr);
void dio_output(sr_instance_t *, uip_ipaddr_t *uc_addr);
void dao_output(sr_parent_t *, uint8_t lifetime);
void dao_output_target(sr_parent_t *, uip_ipaddr_t *, uint8_t lifetime);
void dao_ack_output(sr_instance_t *, uip_ipaddr_t *, uint8_t, uint8_t);
void sr_icmp6_register_handlers(void);
uip_ds6_nbr_t *sr_icmp6_update_nbr_table(uip_ipaddr_t *from,
                                          nbr_table_reason_t r, void *data);

/* SR logic functions. */
void sr_join_dag(uip_ipaddr_t *from, sr_dio_t *dio);
void sr_join_instance(uip_ipaddr_t *from, sr_dio_t *dio);
void sr_local_repair(sr_instance_t *instance);
void sr_process_dio(uip_ipaddr_t *, sr_dio_t *);
int sr_process_parent_event(sr_instance_t *, sr_parent_t *);

/* DAG object management. */
sr_dag_t *sr_alloc_dag(uint8_t, uip_ipaddr_t *);
sr_instance_t *sr_alloc_instance(uint8_t);
void sr_free_dag(sr_dag_t *);
void sr_free_instance(sr_instance_t *);
void sr_purge_dags(void);

/* DAG parent management function. */
sr_parent_t *sr_add_parent(sr_dag_t *, sr_dio_t *dio, uip_ipaddr_t *);
sr_parent_t *sr_find_parent(sr_dag_t *, uip_ipaddr_t *);
sr_parent_t *sr_find_parent_any_dag(sr_instance_t *instance, uip_ipaddr_t *addr);
void sr_nullify_parent(sr_parent_t *);
void sr_remove_parent(sr_parent_t *);
void sr_move_parent(sr_dag_t *dag_src, sr_dag_t *dag_dst, sr_parent_t *parent);
sr_parent_t *sr_select_parent(sr_dag_t *dag);
sr_dag_t *sr_select_dag(sr_instance_t *instance,sr_parent_t *parent);
void sr_recalculate_ranks(void);

/* SR routing table functions. */
void sr_remove_routes(sr_dag_t *dag);
void sr_remove_routes_by_nexthop(uip_ipaddr_t *nexthop, sr_dag_t *dag);
uip_ds6_route_t *sr_add_route(sr_dag_t *dag, uip_ipaddr_t *prefix,
                               int prefix_len, uip_ipaddr_t *next_hop);
void sr_purge_routes(void);

/* Objective function. */
sr_of_t *sr_find_of(sr_ocp_t);

/* Timer functions. */
void sr_schedule_dao(sr_instance_t *);
void sr_schedule_dao_immediately(sr_instance_t *);
void sr_schedule_unicast_dio_immediately(sr_instance_t *instance);
void sr_cancel_dao(sr_instance_t *instance);
void sr_schedule_probing(sr_instance_t *instance);

void sr_reset_dio_timer(sr_instance_t *);
void sr_reset_periodic_timer(void);

/* Route poisoning. */
void sr_poison_routes(sr_dag_t *, sr_parent_t *);


sr_instance_t *sr_get_default_instance(void);

#endif /* SR_PRIVATE_H */
