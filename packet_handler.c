#include "packet_handler.h"
#include "header_extract.h"
#include "argumets.h"

#include <net/ethernet.h>       // struct ethhdr
#include <netinet/ip.h>         // struct iphdr
#include <netinet/ip6.h>        // struct ip6_hdr
#include <netinet/tcp.h>        // struct tcphdr
#include <netinet/udp.h>        // struct udphdr
#include <netinet/ip_icmp.h>    // struct icmphdr
#include <net/if_arp.h>         // struct arphdr
#include <time.h>

/* current handle */
static pcap_t *current_handle = NULL;

/**
 * Returns number of bytes to skip ethernet and ip header
 * @param ether_type Type of communication (IPv4 or IPv6)
 * @return Number of bytes to offset
 */
static inline size_t get_offset(uint16_t ether_type) {
                                    // ip offset depends on IPv4 or IPv6 structure
    return sizeof(struct ethhdr) + (ether_type == 0x0800 ? sizeof(struct iphdr) : sizeof(struct ip6_hdr));
}

// TODO:
static int print_icmp_packet(const u_char *bytes, const unsigned size, struct timeval tv, const uint16_t ether_type) {
    // check filter flags
    if (!args_isicmp())
        return 0;

    // get icmp header
    struct icmphdr *icmp = (struct icmphdr *)(bytes + get_offset(ether_type));
    // print packet's data
    print_timestamp(tv);
    print_eth_header(bytes, size);
    printf("frame length: %d bytes\n", size);
    print_ip_header(bytes, size, ether_type);
    printf("type: %u\ncode: %u", icmp->type, icmp->code);
    puts("\n");
    data_dump(bytes, size);
    return 1;
}

/**
 * Display TCP packet content.
 * @param bytes[in]   Packet's buffer
 * @param size        Buffer size
 * @param tv          Packet's time of arrival
 * @param ether_type  Type of address (IPv4 or IPv6)
 * @return 1 if packet passed through filters and data were displayed; 0 otherwise
 */
static int print_tcp_packet(const u_char *bytes, const unsigned size, struct timeval tv, const uint16_t ether_type) {
    // check filter flags
    if (!args_istcp())
        return 0;

    // get tcp header part
    struct tcphdr *tcp = (struct tcphdr *)(bytes + get_offset(ether_type));

    // apply port filter
    int port = args_get_port();
    if (port != -1) {
        if (port != ntohs(tcp->th_dport) && port != ntohs(tcp->th_sport))
            return 0;
    }

    // print packet's data
    print_timestamp(tv);
    print_eth_header(bytes, size);
    printf("frame length: %d bytes\n", size);
    print_ip_header(bytes, size, ether_type);
    printf("src port: %d\ndst port: %d\n", ntohs(tcp->th_sport), ntohs(tcp->th_dport));
    puts("\n");
    data_dump(bytes, size);
    return 1;
}

/**
 * Display UDP packet content.
 * @param bytes[in]   Packet's buffer
 * @param size        Buffer size
 * @param tv          Packet's time of arrival
 * @param ether_type  Type of address (IPv4 or IPv6)
 * @return 1 if packet passed through filters and data were displayed; 0 otherwise
 */
static int print_udp_packet(const u_char *bytes, const unsigned size, struct timeval tv, const uint16_t ether_type) {
    // check filter flags
    if (!args_isudp())
        return 0;

    // get udp header part
    struct udphdr *udp = (struct udphdr *)(bytes + get_offset(ether_type));

    // apply port filter
    int port = args_get_port();
    if (port != -1) {
        if (port != ntohs(udp->uh_sport) && port != ntohs(udp->uh_dport))
            return 0;
    }

    // print packet's data
    print_timestamp(tv);
    print_eth_header(bytes, size);
    printf("frame length: %d bytes\n", size);
    print_ip_header(bytes, size, ether_type);
    printf("src port: %d\ndst port: %d\n", ntohs(udp->uh_sport), ntohs(udp->uh_dport));
    puts("\n");
    data_dump(bytes, size);
    return 1;
}

// TODO:
static int print_arp_packet(const u_char *bytes, const unsigned size, struct timeval tv, const uint16_t ether_type) {
    // check filter flags
    if (!args_isarp())
        return 0;

    // get icmp header
    struct arphdr *arp = (struct arphdr *)(bytes + sizeof(struct ethhdr));
    // print packet's data
    print_timestamp(tv);
    print_eth_header(bytes, size);
    printf("frame length: %d bytes\n", size);
    print_ip_header(bytes, size, ether_type);
    // TODO: print arp data
    puts("\n");
    data_dump(bytes, size);
    return 1;
}

static uint8_t get_protocol(const u_char *bytes, uint16_t ether_type) {
    if (ether_type == IPV6_ETHERTYPE) {
        // IPv6
        struct ip6_hdr *ip6 = (struct ip6_hdr *)(bytes + sizeof(struct ethhdr));
        return ip6->ip6_ctlun.ip6_un1.ip6_un1_nxt;
    } else if (ether_type == IPV4_ETHERTYPE) {
        // IPv4
        struct iphdr *ip = (struct iphdr *)(bytes + sizeof(struct ethhdr));
        return ip->protocol;
    } else {
        // ignore
        return 0;
    }
}

void set_handle(pcap_t *handle) {
    current_handle = handle;
}

void packet_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    static int counter = 0;
    // buffer for extracting data
    unsigned frame_size = h->len;
    (void)user;

    // get ethernet header and ether type
    struct ethhdr *eth_header = (struct ethhdr *)(bytes);
    uint16_t ether_type = ntohs(eth_header->h_proto);

    // get ether type; ignore all communications except for IPv4 and IPv6
    uint8_t protocol = get_protocol(bytes, ether_type);

    switch(protocol) {
        case ICMP_PROTOCOL_NUMBER:
        case ICMPV6_PROTOCOL_NUMBER:
            // print ICMP and ICMPv6 packet
            counter += print_icmp_packet(bytes, frame_size, h->ts, ether_type);
            break;
        case TCP_PROTOCOL_NUMBER:
            // print TCP packet
            counter += print_tcp_packet(bytes, frame_size, h->ts, ether_type);
            break;
        case UDP_PROTOCOL_NUMBER:
            // print UDP packet
            counter += print_udp_packet(bytes, frame_size, h->ts, ether_type);
            break;
        default:
            // print ARP packet
            if (ntohs(eth_header->h_proto) == 0x0806)
                counter += print_arp_packet(bytes, frame_size, h->ts, ether_type);

            // ignore other packets
            break;
    }

    // check for packet limit
    // end sniffing once limit is reached
    if (counter >= args_get_nof_packets())
        pcap_breakloop(current_handle);
}

/* packet_handler.c */
