#include "ftp_client.h"

int generate_port_number(){	
	int port_number = (rand() % (40000 - 1500 + 1)) + 1500;
	//log the port number for the current instance of this server
	return port_number;
}

void open_socket_ipv4(){
	ftp_client_information.socket_file_descriptor = 0;

	if((ftp_client_information.socket_file_descriptor = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("problem connection stream socket ipv4");
		exit(EXIT_FAILURE);
	}
	//log successfully created an ipv4 socket
}

void open_socket_ipv6(){
	ftp_client_information.socket_file_descriptor = 0;
	
	if((ftp_client_information.socket_file_descriptor = socket(PF_INET6, SOCK_STREAM, 0)) < 0) {
		perror("problem connecting stream socket ipv6");
		exit(EXIT_FAILURE);
	}

	//log successfully created a socket 
}

int set_server_address_ipv4(){
	ftp_client_ipv4.sin_family = PF_INET;

	if(ftp_client_information.ip_address_used == true && ftp_client_information.hostname_used == false){

        ftp_client_ipv4.sin_port = htons(ftp_client_information.port_number);
        ftp_client_ipv4.sin_addr.s_addr = htonl(convert_ip_address_to_integer(ftp_client_information.ip_address));

        printf("IP Address: %s\n", ftp_client_information.ip_address);
        //log the server address have been set properly for this client
	}else if(ftp_client_information.ip_address_used == false && ftp_client_information.hostname_used == true){
        if((host_information = gethostbyname(ftp_client_information.hostname)) == NULL){
            (void) fprintf(stderr, "%s: unknown host \n", ftp_client_information.hostname);
            exit(EXIT_FAILURE);
        }

        bcopy(host_information->h_addr, &ftp_client_ipv4.sin_addr, host_information->h_length);
        ftp_client_ipv4.sin_port = htons(ftp_client_information.port_number);
        printf("IP Address used after converted from hostname: %d\n", ftp_client_ipv4.sin_addr.s_addr);
        printf("Current hostname used: %s\n", ftp_client_information.hostname);
        //log the server address have been set properly for this client
    }
	return EXIT_SUCCESS;
}

int set_server_address_ipv6(){
	ftp_client_ipv6.sin6_family = PF_INET6;
	if((host_information = gethostbyname(ftp_client_information.hostname)) == NULL){
		(void) fprintf(stderr, "%s: unknown host \n", ftp_client_information.hostname);
		exit(EXIT_FAILURE);
	}
	
	bcopy(host_information->h_addr, &ftp_client_ipv6.sin6_addr, host_information->h_length);
	
	ftp_client_ipv6.sin6_port = htons(ftp_client_information.port_number);
	
	//log that the server address have been set properly for this client

	return EXIT_SUCCESS;
}

int setup_ftp_connection_ipv4(){
	if(connect(ftp_client_information.socket_file_descriptor, (struct sockaddr *) &ftp_client_ipv4, sizeof(ftp_client_ipv4)) < 0){
		perror("connecting stream socket ipv4");
		exit(EXIT_FAILURE);
	}else{
		printf("Successfully connected to server \n");
	}
	//log the success of creating stream socket in ipv4
	//
	return EXIT_SUCCESS;
}

int setup_ftp_connection_ipv6(){
	
	if(connect(ftp_client_information.socket_file_descriptor, (struct sockaddr *) &ftp_client_ipv6, sizeof(ftp_client_ipv6)) < 0){
		perror("connecting stream socket");
		//log the problem here for problem connection stream socket
		exit(EXIT_FAILURE);
	}
	//log the success of creating stream socket in ipv6
	return EXIT_SUCCESS;
}


int write_to_server(int socket_file_descriptor, char BUFFER[]){
    if((write(socket_file_descriptor, BUFFER, BUFSIZ)) < 0){
        perror("writing on stream socket");
        exit(EXIT_FAILURE);
    }

	return EXIT_SUCCESS;
}


int read_from_server(int socket_file_descriptor, DATA_PACKET *data_packet_instance){
    //read data from server
    int rval;
    char BUFFER[BUFSIZ];

    if((rval = read(ftp_client_information.socket_file_descriptor, BUFFER, BUFSIZ)) < 0){
        perror("reading stream message");
    }else if(rval == 0){
        printf("Ending connection from server\n");
    }else {
        printf("%s\n", BUFFER);
    }

    //processing to DATA_PACKET

    return EXIT_SUCCESS;
}

void close_socket(int socket_file_descriptor){
	(void)close(socket_file_descriptor);
	//log close socket
}	
