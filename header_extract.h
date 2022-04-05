#ifndef _DEFAULT_SOURCE
    #define _DEFAULT_SOURCE
#endif
#ifndef _HEADER_EXTRACT_H_
#define _HEADER_EXTRACT_H_

#include <stdlib.h>
#include <stdint.h>

/**
 * Print arrival time of the packet.
 *
 * @param timestamp Packet arrival's timestamp
 */
void print_timestamp(struct timeval timestamp);

/**
 * Extracts and prints MAC addresses from ether header of packet.
 *
 * @param bytes[in] Packet's frame
 * @param size[in]  Number of bytes of the frame
 */
void print_eth_header(const u_char *bytes, size_t size);


/**
 * Extracts and prints IP addresses from ip header of packet.
 * Out buffers must be at least INET6_ADDRSTRLEN big (46 bytes).
 *
 * @param bytes[in]       Packet's frame
 * @param size[in]        Number of bytes of the frame
 * @param ethertype[in]   EtherType of the packet
 */
void print_ip_header(const u_char *bytes, size_t size, uint16_t ethertype);

/**
 * Dumps data buffer as hex.
 *
 * @param bytes[in] Packet's buffer
 * @param size[in]  Buffer size
 */
void data_dump(const u_char *bytes, size_t size);


#endif // _HEADER_EXTRACT_H_
