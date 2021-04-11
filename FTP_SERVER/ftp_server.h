#ifndef ICT374_ASSIGNMENT02_FTP_SERVER_H
#define ICT374_ASSIGNMENT02_FTP_SERVER_H

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>

#include <netinet/in.h>
#include <netinet/ip.h>

#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <stdbool.h>
#include <sys/sendfile.h>

#include "../PROTOCOL_COMMAND/command.h"


typedef struct{
	int socket;
	socklen_t length;
	int socket_file_descriptor;
	fd_set file_descriptor_write;
    fd_set file_descriptor_read;
    pid_t current_server_pid;
    char *initial_current_directory;
}FTP_SERVER_INFORMATION;

FTP_SERVER_INFORMATION ftp_server_information;
struct sockaddr_in ftp_server_ipv4;
struct sockaddr_in6 ftp_server_ipv6;

#endif

int initialize_socket_ipv6();
int initialize_socket_ipv4();

void handle_ipv4_connection(int file_descriptor, struct sockaddr_in client);
void handle_ipv6_connection();

void handle_ipv4_socket(int socket_file_descriptor);
void handle_ipv6_socket(int socket_file_descriptor);

int build_file_descriptor_sets(FTP_SERVER_INFORMATION *ftp_server_information);

void reap();
void reap_zombie_processes();

int start_ftp_server(char *file_path_to_serve);

void print_ftp_server_information_to_client(int file_descriptor);