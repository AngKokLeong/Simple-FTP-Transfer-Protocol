#include "ftp_client_helper_function.h"

bool verify_ip_address(char *ip_address_or_hostname){
	struct sockaddr_in sa;
	int result = inet_pton(PF_INET, ip_address_or_hostname, &(sa.sin_addr));
	return result != 0;	
}
