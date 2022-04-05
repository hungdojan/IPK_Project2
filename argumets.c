#include <string.h>
#include "argumets.h"

#define ICMP_BIT 0
#define TCP_BIT  1
#define UDP_BIT  2
#define ARP_BIT  3
#define INT_BUFFER_SIZE 100

struct args_t {
    char interface[INT_BUFFER_SIZE];
    int port;
    char flags;
    char flags_enable;
    int nof_packets;
};

// define global variable
static struct args_t g_args = {
    .interface = {0,},      /* interface name */
    .port = -1,             /* port filter */
    .flags = 0,             /* flags for packet filtering */
    .flags_enable = 0,      /* when user doesn't specify any flag*/
    .nof_packets = 1        /* number of packets to display */
};


void init_args_t() {
    // empties buffer and sets default values
    g_args.interface[0] = '\0';
    g_args.port = -1;
    g_args.flags = 0;
    g_args.nof_packets = 10;
}

enum load_results load_args(const int argc, const char **argv) {
    // TODO:
    return LOAD_SUCCESS;
}

int args_get_interface(char *buffer, const size_t buffer_size) {
    // check for buffer size
    // halts copy when destination buffer is too small
    if (buffer_size <= strlen(g_args.interface))
        return 1;

    strncpy(buffer, g_args.interface, buffer_size);
    return 0;
}

int args_get_port() {
    return g_args.port;
}

int args_isicmp() {
    return g_args.flags & (1 << ICMP_BIT) || !g_args.flags_enable;
}

int args_istcp() {
    return g_args.flags & (1 << TCP_BIT) || !g_args.flags_enable;
}

int args_isudp() {
    return g_args.flags & (1 << UDP_BIT) || !g_args.flags_enable;
}

int args_isarp() {
    return g_args.flags & (1 << ARP_BIT) || !g_args.flags_enable;
}

int args_get_nof_packets() {
    return g_args.nof_packets;
}
/* argumets.c */
