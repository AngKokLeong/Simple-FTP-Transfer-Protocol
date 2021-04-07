#include "ftp_client_driver.h"

int ftp_client_driver_execution(char *ip_address_or_hostname){

	printf("%s", ip_address_or_hostname);
	int port_number = generate_port_number();
	ftp_client_information.port_number = port_number;

	ftp_client_information.hostname = ip_address_or_hostname;

	printf("%s", ip_address_or_hostname);
	ftp_client_information.socket_file_descriptor = open_socket_ipv4();
	set_server_address_ipv4();
	setup_ftp_connection_ipv4();

	//write function

	close_socket(ftp_client_information.socket_file_descriptor);
	//printf("TEST VALUE: %s", ip_address_or_hostname);	
	return EXIT_SUCCESS;	
}

