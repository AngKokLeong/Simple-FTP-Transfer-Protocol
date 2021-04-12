/*
 * file:	ftp_server.h
 * author:	Ang Kok Leong
 * purpose:	To create a separate code for FTP server to allow easy code extend in the future
 * date:	20/03/2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> //superset of <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <strings.h>
#include <stdbool.h>
#include <sys/sendfile.h>
#include "ftp_client_helper_function.h"
#include "../PROTOCOL_COMMAND/command.h"

typedef struct FTP_CLIENT_INFORMATION{
	int socket;
	int port_number;
	char *hostname;
	char *ip_address;
	bool ip_address_used;
	bool hostname_used;
	int ip_address_INET_NO;
    int socket_file_descriptor;
	fd_set file_descriptor_read;
	fd_set file_descriptor_write;
}FTP_CLIENT_INFORMATION;

FTP_CLIENT_INFORMATION ftp_client_information;


struct sockaddr_in ftp_client_ipv4;
struct sockaddr_in6 ftp_client_ipv6;
struct hostent *host_information;


int generate_port_number();

void open_socket_ipv4();
void open_socket_ipv6();


int set_server_address_ipv4();
int setup_ftp_connection_ipv4();

int set_server_address_ipv6();
int setup_ftp_connection_ipv6();

int write_to_server(int socket_file_descriptor, DATA_PACKET data_packet_instance);
int read_from_server(int socket_file_descriptor);
void close_socket(int socket_file_descriptor);
