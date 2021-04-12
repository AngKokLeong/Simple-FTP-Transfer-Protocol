#include "server_helper_function.h"

int daemonize_ftp_server_process(){
	
	int daemon_creation_status;

	daemon_creation_status = daemon(1, 1);

	if(daemon_creation_status == 0){
		//write a log that daemon have been created successfully
	}else{
		//write a log that daemon was not created
		exit(EXIT_FAILURE);
	}

	return getpid();
}
