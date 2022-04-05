// issue with types in pcap.h file
// source: https://stackoverflow.com/questions/15393905/c-pcap-library-unknown-types-error
#ifndef _DEFAULT_SOURCE
    #define _DEFAULT_SOURCE
#include <pcap/pcap.h>
#endif

#include <stdio.h>
#include <string.h>

#include "packet_handler.h"
#include "argumets.h"

#define BUFFER_SIZE 1024

/**
 * Display list of active devices.
 */
int display_active_devices() {
    pcap_if_t *alldevsp;
    char errbuf[BUFFER_SIZE] = {0,};

#ifdef DEBUG
    puts("Find available devices ... \n");
#endif

    // load list of available devices
    if (pcap_findalldevs(&alldevsp, errbuf)) {
        fprintf(stderr, "Error while finding devices:\n%s", errbuf);
        return 1;
    }

#ifdef DEBUG
    puts("All available devices\n");
#endif
    // print list of available devices
    for (pcap_if_t *device = alldevsp; device; device = device->next) {
        printf("%s\n", device->name);
    }
    return 0;
}

/**
 * Sniffing packets.
 * TODO:
 */
int process_packets() {
    char errbuf[BUFFER_SIZE] = {0,};
    char interface_name[BUFFER_SIZE];

    // get interface
    if (args_get_interface(interface_name, BUFFER_SIZE)) {
        // TODO: buffer too small
    }

    // TODO: initialize sth i don't know what
    // pcap_t *handle = pcap_open_live(interface_name, 65536, 1, 0, errbuf);
    // TODO: for testing purposes
    pcap_t *handle = pcap_open_live("enp2s0", 65536, 1, 10, errbuf);

    if (handle == NULL) {
        puts("Error occured at buffer\n");
        return 1;
    }
#ifdef DEBUG
    printf("Device %s successfully initializes\n", interface_name);
#endif

    set_handle(handle);
    pcap_loop(handle, -1, packet_handler, NULL);
    return 0;
}

int main(int argc, char *argv[]) {
    // argument processing
    init_args_t();
    enum load_results result = load_args(argc, (const char **)argv);
    // for testing purposes
    // result = LOAD_NO_INTERFACE;

    // TODO:
    switch (result) {
        case LOAD_SUCCESS:
            return process_packets();
        case LOAD_ERROR:
            fprintf(stderr, "Error occured while loading arguments\n");
            return 1;
        case LOAD_NO_INTERFACE:
            return display_active_devices();
    }
    return 0;

}

/* main.c */
