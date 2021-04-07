#include "ftp_server.h"
#include "server_helper_function.h"

int initialize_socket_ipv4(){
	
	int socket_file_descriptor;
	int bind_status;
	int socket_name_status;
	int listen_status;
	int maximum_number_of_pending_connections_for_socket_descriptor = 5;
	socklen_t size_of_address;
	
	//opening stream socket
	socket_file_descriptor = socket(PF_INET, SOCK_STREAM, 0);
	
	if(socket_file_descriptor < 0){
		perror("opening stream socket");
		//log error opening stream socket
		exit(EXIT_FAILURE);
	}

	

	int generated_port_number = generate_random_port_number();

	ftp_server_ipv4.sin_family = PF_INET;
	ftp_server_ipv4.sin_addr.s_addr = htonl(INADDR_ANY);
	ftp_server_ipv4.sin_port = htons(generated_port_number); 

	bind_status = bind(socket_file_descriptor, (struct sockaddr *) &ftp_server_ipv4, sizeof(ftp_server_ipv4));

	if(bind_status != 0){
		perror("binding stream socket");
		//log error binding stream socket
		exit(EXIT_FAILURE);
	}
	//log successfully bind stream socket
	
	size_of_address = sizeof(ftp_server_ipv4);

	socket_name_status = getsockname(socket_file_descriptor, (struct sockaddr *) &ftp_server_ipv4, &size_of_address);

	if(socket_name_status != 0){
		perror("getting socket name");
		exit(EXIT_FAILURE);
	}
	//log successfully getting socket name	
	
	//(void)printf("FTP Server current ip address:%d\n", ntohl(ftp_server_ipv4.sin_addr.s_addr));
	(void)printf("FTP Server has port #%d\n", generated_port_number);

	listen_status = listen(socket_file_descriptor, maximum_number_of_pending_connections_for_socket_descriptor);
	
	if(listen_status < 0){
		perror("listening function");
		exit(EXIT_FAILURE);
	}
	//log successfully listen the port

	return socket_file_descriptor;
}

void handle_ipv4_connection(int file_descriptor, struct sockaddr_in client){
	
	const char *rip;
	int rval;
	char claddr[INET_ADDRSTRLEN];

	if((rip = inet_ntop(PF_INET, &client.sin_addr, claddr, INET_ADDRSTRLEN)) == NULL){

		perror("inet_ntop");
		rip = "unknown";
	}else{
		(void)printf("Client connection from %s!\n", rip);
	}

}

void handle_ipv4_socket(int socket_file_descriptor){
	
	int file_descriptor;
	pid_t process_id;
	struct sockaddr_in ftp_client;
	socklen_t socket_length;

	socket_length = sizeof(ftp_client);

	if((file_descriptor = accept(socket_file_descriptor, (struct sockaddr *) &ftp_client, &socket_length)) < 0){
		perror("error accepting sockets");
		return;
	}

	if((process_id = fork()) < 0){
		perror("error forking");
		exit(EXIT_FAILURE);
	}else if(!process_id){
		handle_ipv4_connection(file_descriptor, ftp_client);
	}
}

void reap_zombie_processes(){
	wait(NULL);
}


int start_ftp_server(char *file_path_to_serve){
	
	if(signal(SIGCHLD, reap_zombie_processes) == SIG_ERR){
		printf("SDSDS");
		perror("signal error");
		exit(EXIT_FAILURE);
	}

	int socket_file_descriptor = initialize_socket_ipv4();

	for(;;){
		fd_set ready;
		struct timeval to;

		FD_ZERO(&ready);
		FD_SET(socket_file_descriptor, &ready);
		to.tv_sec = 5;
		to.tv_usec = 0;

		if(select(socket_file_descriptor + 1, &ready, 0, 0, &to) < 0){
			if(errno != EINTR)
			       perror("error occur in select");
			continue;	
		}

		if(FD_ISSET(socket_file_descriptor, &ready)){
			handle_ipv4_socket(socket_file_descriptor);
		}else{
			(void)printf("FTP Server: waiting for connections . . . \n");
		}
		
	}

}
