#include <stdlib.h>
#include <stdio.h>

int ftp_client_driver(char *ip_address_or_hostname){
	
	FTP_CLIENT_INFORMATION ftp_client_information;
	ftp_client_information = construct_ftp_client_information();

	int port_number = generate_port_number();
	
	open_socket_ipv4(&ftp_client_information->socket_file_descriptor);
	
	set_server_address_ipv4(ftp_client_information);

	setup_ftp_connection_ipv4(ftp_client_information);

	//write function

	close_socket(ftp_client_information.socket_file_descriptor);
	//printf("TEST VALUE: %s", ip_address_or_hostname);	
	return EXIT_FAILURE;	
}

