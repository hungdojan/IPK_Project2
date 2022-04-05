/**
 * Header file with declaration of pcap callback function.
 * This file also contains some additional constants used in packet_handler.c file.
 *
 * This source code serves as submission for second project of class IPK at FIT, BUT 2021/2022.
 *
 * @file    packet_handler.h
 * @author  Hung Do
 * @date    04/04/2022
 */
#ifndef _DEFAULT_SOURCE
    #define _DEFAULT_SOURCE
#endif
#ifndef _PACKET_HANDLER_H_
#define _PACKET_HANDLER_H_

// define constant
#define ICMP_PROTOCOL_NUMBER    1
#define TCP_PROTOCOL_NUMBER     6
#define UDP_PROTOCOL_NUMBER    17
#define ICMPV6_PROTOCOL_NUMBER 58

#define IPV4_ETHERTYPE 0x0800
#define IPV6_ETHERTYPE 0x86DD
#define ARP_ETHERTYPE  0x0806

#include <pcap.h>

/**
 * Declaration of pcap callback function
 */
void packet_handler(u_char *, const struct pcap_pkthdr *, const u_char *);

/**
 * Update pcap value.
 * @param handle New instance of pcap handle
 */
void set_handle(pcap_t *handle);

#endif // _PACKET_HANDLER_H_
