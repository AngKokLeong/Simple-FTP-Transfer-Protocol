#include <stdio.h>
#include <syslog.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int daemonize_ftp_server_process();

int generate_random_port_number();

char * get_ip_address_in_string(u_int32_t network_byte_order);
