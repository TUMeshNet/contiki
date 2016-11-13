/*
 *
 * This file is part of the Contiki operating system.
 */

/**
 * \file
 *         border-router
 *
 * \author Nhim Roeung <nhim.roeung@temple.edu>.
 */

 #include "contiki.h"
 #include "contiki-lib.h"
 #include "contiki-net.h"
 #include "net/ip/uip.h"
 #include "net/ipv6/uip-ds6.h"
 #include "net/rpl/rpl.h"
 #include "net/rpl/rpl-private.h"
 #if RPL_WITH_NON_STORING
 #include "net/rpl/rpl-ns.h"
 #endif /* RPL_WITH_NON_STORING */
 #include "net/netstack.h"
 #include "dev/button-sensor.h"
 #include "dev/slip.h"

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>

PROCESS(border_router_process, "Border router process");
AUTOSTART_PROCESSES(&border_router_process);

PROCESS_THREAD(border_router_process, ev, data)
{
  static struct etimer et;

  PROCESS_BEGIN();

/* While waiting for the prefix to be sent through the SLIP connection, the future
 * border router can join an existing DAG as a parent or child, or acquire a default
 * router that will later take precedence over the SLIP fallback interface.
 * Prevent that by turning the radio off until we are initialized as a DAG root.
 */
  prefix_set = 0;
  NETSTACK_MAC.off(0);

  PROCESS_PAUSE();

  SENSORS_ACTIVATE(button_sensor);

  PRINTF("Border router started\n");
#if 0
   /* The border router runs with a 100% duty cycle in order to ensure high
     packet reception rates.
     Note if the MAC RDC is not turned off now, aggressive power management of the
     cpu will interfere with establishing the SLIP connection */
  NETSTACK_MAC.off(1);
#endif

  /* Request prefix until it has been received */
  while(!prefix_set) {
    etimer_set(&et, CLOCK_SECOND);
    request_prefix();
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }

  /* Now turn the radio on, but disable radio duty cycling.
   * Since we are the DAG root, reception delays would constrain mesh throughbut.
   */
  NETSTACK_MAC.off(1);

#if DEBUG || 1
  print_local_addresses();
#endif

  while(1) {
    PROCESS_YIELD();
    if (ev == sensors_event && data == &button_sensor) {
      PRINTF("Initiating global repair\n");
      rpl_repair_root(RPL_DEFAULT_INSTANCE);
    }
  }

  PROCESS_END();
}
