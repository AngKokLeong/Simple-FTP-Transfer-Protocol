#include "ftp_server_driver.h"

char *initial_current_directory;

int ftp_server_driver_execution(char *current_directory){
	
	initial_current_directory = current_directory;
	//log ftp server is currently serving this directory
	ftp_server_information.initial_current_directory = initial_current_directory;

	daemon(1,1);	
	//int daemon_process_id = daemonize_ftp_server_process();
	//log current process id
	ftp_server_information.current_server_pid = getpid();

	//log ftp server started serving
	start_ftp_server(initial_current_directory);
	//log ftp server ended serving
	//
	return EXIT_SUCCESS;
}
