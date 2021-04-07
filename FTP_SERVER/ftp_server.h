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

typedef struct{
	int socket;
	socklen_t length;
	
}FTP_SERVER_INFORMATION;



struct sockaddr_in ftp_server_ipv4;
struct sockaddr_in6 ftp_server_ipv6;

FTP_SERVER_INFORMATION construct_ftp_server_information();
void destruct_ftp_server_information(FTP_SERVER_INFORMATION ftp_server_information);

int initialize_socket_ipv6();
int initialize_socket_ipv4();

void handle_ipv4_connection(int file_descriptor, struct sockaddr_in client);
void handle_ipv6_connection();

void handle_ipv4_socket(int socket_file_descriptor);
void handle_ipv6_socket(int socket_file_descriptor);

void reap_zombie_processes();

int start_ftp_server(char *file_path_to_serve);
