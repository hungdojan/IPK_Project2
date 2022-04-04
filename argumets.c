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
    int nof_packets;
};

// define global variable
static struct args_t g_args = {
    .interface = {0,},
    .port = -1,
    .flags = 0,
    .nof_packets = 0
};


void init_args_t() {
    // empties buffer and sets default values
    g_args.interface[0] = '\0';
    g_args.port = -1;
    g_args.flags = 0;
    g_args.nof_packets = 1;
}

int load_args(const int argc, const char *argv[]) {
    // TODO:
    return 0;
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
    return g_args.flags & (1 << ICMP_BIT);
}

int args_istcp() {
    return g_args.flags & (1 << TCP_BIT);
}

int args_isudp() {
    return g_args.flags & (1 << UDP_BIT);
}

int args_isarp() {
    return g_args.flags & (1 << ARP_BIT);
}

int args_get_nof_packets() {
    return g_args.nof_packets;
}


/* argumets.c */
