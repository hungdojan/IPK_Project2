/*
 * Header file with function that extracts program arguments of this project.
 * TODO:
 *
 * @file    arguments.h
 * @author  Hung Do
 * @date    04/04/2022
 */
#ifndef _ARGUMETS_H_
#define _ARGUMETS_H_

#include <stdlib.h> // size_t

/**
 * Initializes argument structure.
 */
void init_args_t();

/**
 * Process program arguments.
 *
 * @param argv Vector of arguments
 * @param argc Argument count
 * @return Non-zero value when error occures.
 */
int load_args(const int argc, const char *argv[]);

/**
 * Returns interface value from argument structure
 *
 * @param buffer Pointer to buffer to return value
 * @param buffer_size Output buffer size
 * @return Non-zero value when error occures.
 */
int args_get_interface(char *buffer, const size_t buffer_size);

/**
 * Retuns loaded port.
 * Output port will be in range 0-65536. -1 will be returned when user 
 * didn't specified port.
 *
 * @return Port number, -1 when not specified.
 */
int args_get_port();


/**
 * Returns ICMP flag's value.
 * 
 * @return true if user defined ICMP value.
 */
int args_isicmp();

/**
 * Returns TCP flag's value.
 * 
 * @return true if user defined TCP value.
 */
int args_istcp();

/**
 * Returns UDP flag's value.
 * 
 * @return true if user defined UDP value.
 */
int args_isudp();

/**
 * Returns ARP flag's value.
 * 
 * @return true if user defined ARP value.
 */
int args_isarp();

/**
 * Returns number of packets to display.
 *
 * @return Number of values to display.
 */
int args_get_nof_packets();

#endif // _ARGUMETS_H_
