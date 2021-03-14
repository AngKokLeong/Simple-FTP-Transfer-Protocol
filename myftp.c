#include <stdio.h>
#include "FTP_CLIENT/ftp_client_driver.c"


int main(int argc, char *argv[]){


	if(argc == 2)
		ftp_client_driver(argv[1]);	
	else
		printf("The program needs a hostname or an IP Address to start.\n");

	return 0;
}
