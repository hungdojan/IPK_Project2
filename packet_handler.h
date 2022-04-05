#ifndef _DEFAULT_SOURCE
    #define _DEFAULT_SOURCE
#endif
#ifndef _PACKET_HANDLER_H_
#define _PACKET_HANDLER_H_

// define constant
#define ICMP_PROTOCOL_NUMBER    1
#define ICMPV6_PROTOCOL_NUMBER 58
#define TCP_PROTOCOL_NUMBER     6
#define UDP_PROTOCOL_NUMBER    17

#define IPV4_ETHERTYPE 0x0800
#define IPV6_ETHERTYPE 0x86DD

#include <pcap.h>

/**
 * Function for callback
 */
void packet_handler(u_char *, const struct pcap_pkthdr *, const u_char *);
void set_handle(pcap_t *handle);

#endif // _PACKET_HANDLER_H_
