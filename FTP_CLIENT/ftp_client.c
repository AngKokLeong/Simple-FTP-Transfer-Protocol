#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> //superset of <netinet/in.h>

#include <errno.h>

#include "ftp_server.h"


FTP_SERVER_INFORMATION construct_ftp_client_information(){
	FTP_CLIENT_INFORMATIOn ftp_client_information;
	ftp_client_information = malloc(sizeof(FTP_SERVER_INFORMATION));
	
	if(ftp_client_information == NULL){
		//log that ftp_server_information do not have sufficient memory to allocate
		exit(EXIT_FAILURE);
	}

	//log ftp_client_information has been successfuly constructed
	return ftp_client_information;
}

void destruct_ftp_client_information(FTP_CLIENT_INFORMATION *ftp_client_information){
	
	free(ftp_client_information);
	//log that ftp_client_information have been destructed	
}

int initialize_socket_ipv6(FTP,char *hostname){
	ftp_client_information.socket = 1234;
	return 0;
	
}

int generate_port_number(){
	
	int port_number = (rand() % (40000 - 1500 + 1)) + 1500;
	//log the port number for the current instance of this server
	return port_number;
}

int open_socket_ipv6(int *socket_file_descriptor){
	
	if((socket_file_descriptor = socket(PF_INET6, SOCK_STREAM, 0)) < 0) {
		perror("problem connecting stream socket");
		exit(EXIT_FAILURE);
	}

	//log successfully created a socket 
	return EXIT_SUCCESS;
}


int set_server_address_ipv6(FTP_CLIENT_INFORMATION *ftp_client_information, char *hostname, int port_number){
	ftp_client_information.sin6_family = PF_INET6;
	if((ftp_client_information.host_information = gethostbyname2(hostname, PF_INET6)) == NULL){
		(void) fprintf(stderr, "%s: unknown host \n", hostname);
		exit(EXIT_FAILURE);
	}
	
	bcopy(host_information->h_addr, &ftp_client_information.ftp_server_in6.sin6_addr, host_information->h_length);
	
	ftp_client_information.sin6_port = htons(port_number);
	
	//log that the server address have been set properly

	return EXIT_SUCCESS;
}

int setup_ftp_connection_ipv6(int socket_file_descriptor, FTP_CLIENT_INFORMATION *ftp_client_information){
	
	if(connect(socket_file_descriptor, (struct sockaddr *) ftp_client_information.ftp_server_ipv6, sizeof(ftp_client_information.ftp_server_ipv6)) < 0){
		
		perror("connecting stream socket");
		//log the problem here for problem connection stream socket
		exit(EXIT_FAILURE);
	}
	

	//log the success of creating stream socket
	
	return EXIT_SUCCESS;
}


int test_write(int socket_file_descriptor){
	char * DATA = "TESTING .... TESTING";

	if((write(socket_file_descriptor, DATA, sizeof(DATA))) < 0){
		perror("writing on stream socket");

	}

}

void close_socket(int socket_file_descriptor){

	(void)close(socket_file_descriptor);
	//log close socket
}	


