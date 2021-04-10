#include "server_helper_function.h"

/*
int daemonize_server_process(){
	
	int index, file_descriptor_0, file_descriptor_1, file_descriptor_2;

	pid_t process_id;
	struct rlimit rl;
	struct sigaction signal_action;

	//Clear file creation mask
	umask(0);

	//Get maximum number of file descriptors
	if(getrlimit(RLIMIT_NOFILE, &rl) < 0)
		err_quit("FTP Server: cannot get file limit");

	//Become a session leader to lose controlling TTY
	if((process_id = fork()) < 0)
		err_quit("FTP Server: cannot fork");
	else if(process_id != 0)
		exit(0);
	setsid();

	//Ensure future opens won't allocate controlling TTYs.
	signal_action.sa_handler = SIG_IGN;
	sigemptyset(&signal_action.sa_mask);
	signal_action.sa_flags = 0;

	if(sigaction(SIGHUP, &signal_action, NULL) < 0)
		err_quit("FTP Server: cannot ignore SIGHUP");
	if((process_id = fork()) < 0)
		err_quit("FTP Server: cannot fork");
	else if(process_id != 0)
		exit(0);
	
	//Change the current working directory to the root so we 
	//won't prevent file systems from being unmounted
	
	if(chdir("/") < 0)
		err_quit("FTP Server: cannot change directory to /");
	
	//Close all open file descriptors
	if(rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for(index=0; index< rl.rlim_max; index++)
		close(index);
	
	//Attach file descriptors 0, 1, 2 to /dev/null
	openlog("FTP Server Daemon", LOG_CONS, LOG_DAEMON);
	if(file_descriptor_0 != 0 || file_descriptor_1 != 1 || file_descriptor_2 != 2){
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", file_descriptor_0, file_descriptor_1, file_descriptor_2);
		exit(1);
	}
}
*/


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
