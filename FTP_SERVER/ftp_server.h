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
#include <netinet/in.h>
#include <netinet/ip.h> //superset of <netinet/in.h>

typedef struct {
	int socket;
	int port_number;
	struct sockaddr_in ftp_server_ipv4;
	struct sockaddr_in6 ftp_server_ipv6;
	struct hostent *host_information;
}FTP_SERVER_INFORMATION;


FTP_SERVER_INFORMATION construct_ftp_server_information();
void destruct_ftp_server_information(FTP_SERVER_INFORMATION ftp_server_information);


int initialize_socket_ipv6(char *hostname);
int initialize_socket_ipv4(char *hostname);

char* get_server_hostname();
int generate_port_number();

int set_server_address_ipv6(FTP_SERVER_INFORMATION ftp_server_information, char *hostname, int port_number);
int setup_ftp_connectioN_ipv6(int socket_file_descriptor, FTP_SERVER_INFORMATION *ftp_server_information);

int test_write(int socket_file_descriptor);
void close_socket(int socket_file_descriptor);


