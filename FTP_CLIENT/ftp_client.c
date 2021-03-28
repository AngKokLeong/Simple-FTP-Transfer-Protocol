#include "ftp_client.h"


FTP_CLIENT_INFORMATION *construct_ftp_client_information(){
	FTP_CLIENT_INFORMATION *ftp_client_information;
	ftp_client_information = malloc(sizeof(struct FTP_CLIENT_INFORMATION));
	
	if(ftp_client_information == NULL){
		//log that ftp_server_information do not have sufficient memory to allocate
		exit(EXIT_FAILURE);
	}
	
	//initialize hostname with malloc
	//
	//initialize ftp_server_ipv4 with malloc
	//initialize ftp_server_ipv6 with malloc
	//initialize host_information with malloc
	
	//https://stackoverflow.com/questions/14768230/malloc-for-struct-and-pointer-in-c

	//log ftp_client_information has been successfuly constructed
	return ftp_client_information;
}

void destruct_ftp_client_information(FTP_CLIENT_INFORMATION *ftp_client_information){
	
	free(ftp_client_information);
	//log that ftp_client_information have been destructed	
}

int generate_port_number(){
	
	int port_number = (rand() % (40000 - 1500 + 1)) + 1500;
	//log the port number for the current instance of this server
	return port_number;
}


int open_socket_ipv4(int *socket_file_descriptor){
	int socket_file_descriptor_container = 0;

	socket_file_descriptor = &socket_file_descriptor_container;
	if((socket_file_descriptor_container = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("problem connection stream socket ipv4");
		exit(EXIT_FAILURE);
	}
	

	return EXIT_SUCCESS;
}

int open_socket_ipv6(int *socket_file_descriptor){
	int socket_file_descriptor_container = 0;

	socket_file_descriptor = &socket_file_descriptor_container;
	if((socket_file_descriptor_container = socket(PF_INET6, SOCK_STREAM, 0)) < 0) {
		perror("problem connecting stream socket ipv6");
		exit(EXIT_FAILURE);
	}
	

	//log successfully created a socket 
	return EXIT_SUCCESS;
}

int set_server_address_ipv4(FTP_CLIENT_INFORMATION *ftp_client_information){
	ftp_client_information->ftp_server_ipv4.sin_family = AF_INET;
	if((ftp_client_information->host_information = gethostbyname2(ftp_client_information->hostname, PF_INET)) == NULL){
		(void) fprintf(stderr, "%s: unknown host \n", ftp_client_information->hostname);
		exit(EXIT_FAILURE);
	}

	bcopy(ftp_client_information->host_information->h_addr, &ftp_client_information->ftp_server_ipv4.sin_addr, ftp_client_information->host_information->h_length);
	ftp_client_information->ftp_server_ipv4.sin_port = htons(ftp_client_information->port_number);
	
	//log the server address have been set properly for this client
	return EXIT_SUCCESS;
}

int set_server_address_ipv6(FTP_CLIENT_INFORMATION *ftp_client_information){
	ftp_client_information->ftp_server_ipv6.sin6_family = PF_INET6;
	if((ftp_client_information->host_information = gethostbyname2(ftp_client_information->hostname, PF_INET6)) == NULL){
		(void) fprintf(stderr, "%s: unknown host \n", ftp_client_information->hostname);
		exit(EXIT_FAILURE);
	}
	
	bcopy(ftp_client_information->host_information->h_addr, &ftp_client_information->ftp_server_ipv6.sin6_addr, ftp_client_information->host_information->h_length);
	
	ftp_client_information->ftp_server_ipv6.sin6_port = htons(ftp_client_information->port_number);
	
	//log that the server address have been set properly for this client

	return EXIT_SUCCESS;
}

int setup_ftp_connection_ipv4(FTP_CLIENT_INFORMATION *ftp_client_information){
	if(connect(ftp_client_information->socket_file_descriptor, (struct sockaddr *) &ftp_client_information->ftp_server_ipv4, sizeof(ftp_client_information->ftp_server_ipv4)) < 0){
		perror("connecting stream socket ipv4");
		exit(EXIT_FAILURE);
	}
	
	//log the success of creating stream socket in ipv4
	//
	return EXIT_SUCCESS;
}



int setup_ftp_connection_ipv6(FTP_CLIENT_INFORMATION *ftp_client_information){
	
	if(connect(ftp_client_information->socket_file_descriptor, (struct sockaddr *) &ftp_client_information->ftp_server_ipv6, sizeof(ftp_client_information->ftp_server_ipv6)) < 0){
		
		perror("connecting stream socket");
		//log the problem here for problem connection stream socket
		exit(EXIT_FAILURE);
	}
	

	//log the success of creating stream socket in ipv6
	
	return EXIT_SUCCESS;
}


int test_write(int socket_file_descriptor){
	char * DATA = "TESTING .... TESTING";

	if((write(socket_file_descriptor, DATA, sizeof(DATA))) < 0){
		perror("writing on stream socket");

	}
	
	return EXIT_SUCCESS;
}

void close_socket(int socket_file_descriptor){

	(void)close(socket_file_descriptor);
	//log close socket
}	
