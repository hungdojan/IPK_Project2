#include "header_extract.h"
#include <stdio.h>          // printf
#include <sys/socket.h>     // struct sockaddr_in
#include <arpa/inet.h>      // inet_ntoa
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/ip6.h>

/**
 * Prints out MAC address format.
 * @param msg   Message to print before MAC format
 * @param addr  Six-byte array contain MAC address
 */
static void print_mac_addr(const char *msg, const unsigned char addr[6]) {
    // at least 18 bytes are needed (including '\0'
    printf("%s%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:\n", msg,
             addr[0], addr[1], addr[2],
             addr[3], addr[4], addr[5]);
}

// -------------------------------------------

void print_timestamp(struct timeval timestamp) {
    // TODO:
    puts("TODO: timestamp");
}

void print_eth_header(const u_char *bytes, const size_t size) {
    // extract ether header from buffer of bytes
    struct ethhdr *eth_header = (struct ethhdr *)(bytes);
    (void)size;

    // display MAC addresses
    print_mac_addr("src MAC: ", eth_header->h_source);
    print_mac_addr("dst MAC: ", eth_header->h_dest);
}

void print_ip_header(const u_char *bytes, const size_t size, const uint16_t ethertype) {
    (void)size;
    // buffer for storing formatted IP address
    char addr_buffer[INET6_ADDRSTRLEN] = {0,};

    if (ethertype == 0x0800) {
        // IPv4
        struct iphdr *ip = (struct iphdr *)(bytes + sizeof(struct ethhdr));
        inet_ntop(AF_INET, &ip->saddr, addr_buffer, INET_ADDRSTRLEN);
        printf("src IP: %s\n", addr_buffer);
        inet_ntop(AF_INET, &ip->daddr, addr_buffer, INET_ADDRSTRLEN);
        printf("dst IP: %s\n", addr_buffer);
    } else if (ethertype == 0x86DD) {
        // IPv6
        struct ip6_hdr *ip = (struct ip6_hdr *)(bytes + sizeof(struct ethhdr));
        inet_ntop(AF_INET6, &ip->ip6_src, addr_buffer, INET6_ADDRSTRLEN);
        printf("src IP: %s\n", addr_buffer);
        inet_ntop(AF_INET6, &ip->ip6_dst, addr_buffer, INET6_ADDRSTRLEN);
        printf("dst IP: %s\n", addr_buffer);
    }
    // Unknown types are ignored
}

void data_dump(const u_char *bytes, const size_t size) {
    // TODO:
    puts("TODO: data dump");
}
/* header_extract.c */
