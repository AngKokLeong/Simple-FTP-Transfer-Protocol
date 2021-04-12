#include "ftp_server.h"
#include "server_helper_function.h"


char ftp_server_response_code[7][1] = {
        "+", //SUCCESS RESPONSE CODE
        "-", //FAILURE RESPONSE CODE
        "=", //PENDING PROCESSING RESPONSE CODE
        "!", // SEND TO SERVER RESPONSE CODE
        "@", // SEND TO CLIENT RESPONSE CODE
        "#", // SEND FILE TO CLIENT RESPONSE CODE
        "%" // SEND FILE TO SERVER RESPONSE CODE
};

char *ftp_server_command_type[2] = {
        "CLIENT",
        "SERVER"
};
char *ftp_server_server_command_array[5] = {
        "lpwd",
        "ldir",
        "lcd",
        "get",
        "put"
};

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
	//(void)printf("FTP Server has port %d\n", generated_port_number);

	listen_status = listen(socket_file_descriptor, maximum_number_of_pending_connections_for_socket_descriptor);
	
	if(listen_status < 0){
		perror("listening function");
		exit(EXIT_FAILURE);
	}
	//log successfully listen the port

	return socket_file_descriptor;
}

void print_server_information_to_client(int file_descriptor){
    char *information = "Server Information\n======================\n";
    if((write(file_descriptor, information, BUFSIZ)) < 0){
        perror("writing on stream socket");
        exit(EXIT_FAILURE);
    }
    information = "";
    sprintf(information, "Current directory in Server: %s\n", ftp_server_information.initial_current_directory);
    if((write(file_descriptor, information, BUFSIZ)) < 0){
        perror("writing on stream socket");
        exit(EXIT_FAILURE);
    }

    information = "";
    sprintf(information, "Current FTP Server Daemon Process ID: %d\n", ftp_server_information.current_server_pid);
    if((write(file_descriptor, information, BUFSIZ)) < 0){
        perror("writing on stream socket");
        exit(EXIT_FAILURE);
    }

}

void handle_ipv4_connection(int file_descriptor, struct sockaddr_in client){

    bool print_initial_server_message = false;
	const char *rip;
	int rval;
	char claddr[INET_ADDRSTRLEN];

	DATA_PACKET data_packet_instance;

	if((rip = inet_ntop(PF_INET, &client.sin_addr, claddr, INET_ADDRSTRLEN)) == NULL){
		perror("inet_ntop");
		rip = "unknown";
	}else {
		(void)printf("Client connection from %s!\n", rip);
	}

	do {

        char BUFFER[BUFSIZ];
        bzero(BUFFER, sizeof(BUFFER));
        if((rval = read(file_descriptor, BUFFER, BUFSIZ)) < 0){
            perror("reading stream message");
        }else if(rval == 0){
            printf("Ending connection from %s.\n", rip);
        }else{
            if(!print_initial_server_message){

                //call the command to change the current working directory to the initial working directory

                data_packet_instance.command = "cd";
                data_packet_instance.command_argument[0] = "cd";
                data_packet_instance.command_argument[1] = ftp_server_information.initial_current_directory;
                data_packet_instance.command_argument[2] = "NULL";

                data_packet_instance.data = "";
                data_packet_instance.response_code = "+";
                //change the current directory to a specific path
                EXECUTE_SERVER_COMMAND(data_packet_instance);

                print_initial_server_message = true;
            }

            print_server_information_to_client(file_descriptor);

            //something to convert buffer to DATA_PACKET
            data_packet_instance = PROCESS_MESSAGE_BUFFER_TO_DATA_PACKET(BUFFER);
            //determine which action to take after reading data packets
            data_packet_instance = PROCESS_DATA_PACKET(data_packet_instance);

            //execute server commands and store the information in DATA_PACKET
            if(strcmp(data_packet_instance.command_type, ftp_server_command_type[SERVER]) == 0) {
                //get the result DATA_PACKET
                //
                data_packet_instance = EXECUTE_SERVER_COMMAND(data_packet_instance);
            }

            char *result;
            //got updated data_packet_instance
            //start to process data_packet to buffer
            result = PROCESS_DATA_PACKET_FOR_TRANSMISSION(data_packet_instance);
            strcpy(BUFFER, result);
            if(strcmp(data_packet_instance.command_type, ftp_server_command_type[SERVER]) == 0 && strcmp(data_packet_instance.command, ftp_server_response_code[SEND_FILE_TO_CLIENT_RESPONSE_CODE]) == 0) {
                if((write(file_descriptor, BUFFER, BUFSIZ)) < 0){
                    perror("writing on stream socket");
                    exit(EXIT_FAILURE);
                }

            }else if(strcmp(data_packet_instance.command_type, ftp_server_command_type[SERVER]) == 0 && strcmp(data_packet_instance.command, ftp_server_response_code[SEND_TO_CLIENT_RESPONSE_CODE]) == 0) {
                //send server command result back to client

                if((write(file_descriptor, BUFFER, BUFSIZ)) < 0){
                    perror("writing on stream socket");
                    exit(EXIT_FAILURE);
                }

            }
        }

	}while(rval != 0);

    (void)close(file_descriptor);
    exit(EXIT_SUCCESS);
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
void reap() {
    wait(NULL);
}
void reap_zombie_processes(){
    if(signal(SIGCHLD, reap_zombie_processes) == SIG_ERR){
        printf("SDSDS");
        perror("signal error");
        exit(EXIT_FAILURE);
    }
}

int start_ftp_server(char *file_path_to_serve){

	reap_zombie_processes();

	ftp_server_information.socket_file_descriptor = initialize_socket_ipv4();
    ftp_server_information.initial_current_directory = file_path_to_serve;


	for(;;){
	    struct timeval to;

        FD_ZERO(&ftp_server_information.file_descriptor_read);
		FD_SET(ftp_server_information.socket_file_descriptor, &ftp_server_information.file_descriptor_read);
		to.tv_sec = 5;
		to.tv_usec = 0;

		if(select(ftp_server_information.socket_file_descriptor + 1, &ftp_server_information.file_descriptor_read, 0, 0, &to) < 0){
			if(errno != EINTR)
			       perror("error occur in select");
			continue;	
		}

		if(FD_ISSET(ftp_server_information.socket_file_descriptor, &ftp_server_information.file_descriptor_read)){
			handle_ipv4_socket(ftp_server_information.socket_file_descriptor);
		}else{
			(void)printf("FTP Server: waiting for connections . . . \n");
		}
		
	}

}

