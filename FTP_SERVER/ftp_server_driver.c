#include "ftp_server_driver.h"

char *initial_current_directory;

int ftp_server_driver_execution(char *current_directory){
	
	initial_current_directory = current_directory;
	//log ftp server is currently serving this directory
	printf("The current directory: %s\n", initial_current_directory);
	
	int daemon_process_id = daemonize_ftp_server_process();
	//log current process id
	printf("Current FTP Server Daemon Process ID: %d\n", daemon_process_id);

	//log ftp server started serving
	start_ftp_server(initial_current_directory);
	//log ftp server ended serving
	//
	return EXIT_SUCCESS;
}
