#include "ftp_client_driver.h"

char ftp_client_response_code[7][1] = {
        "+", //SUCCESS RESPONSE CODE
        "-", //FAILURE RESPONSE CODE
        "=", //PENDING PROCESSING RESPONSE CODE
        "!", // SEND TO SERVER RESPONSE CODE
        "@", // SEND TO CLIENT RESPONSE CODE
        "#", // SEND FILE TO CLIENT RESPONSE CODE
        "%" // SEND FILE TO SERVER RESPONSE CODE
};

char *ftp_client_command_type[2] = {
        "CLIENT",
        "SERVER"
};

char *ftp_client_client_command_array[3] = {
        "pwd",
        "dir",
        "cd"
};

char *ftp_client_server_command_array[5] = {
        "lpwd",
        "ldir",
        "lcd",
        "get",
        "put"
};


int ftp_client_driver_execution(char *ip_address_or_hostname){


	int port_number = generate_port_number();
	ftp_client_information.port_number = port_number;
	
	if(verify_ip_address(ip_address_or_hostname)){
		ftp_client_information.ip_address = ip_address_or_hostname;
		ftp_client_information.ip_address_used = true;
		ftp_client_information.hostname_used = false;
	}else{
		ftp_client_information.hostname = ip_address_or_hostname;
		ftp_client_information.ip_address_used = false;
		ftp_client_information.hostname_used = true;
	}	
	
	open_socket_ipv4();
	set_server_address_ipv4();
	setup_ftp_connection_ipv4();

    char user_input[BUFSIZ];
    char BUFFER[BUFSIZ];
    DATA_PACKET data_packet_instance = {.command = "TEST",.command_type = "TEST" ,.response_code = "TEST", .data = "SDSD", .command_argument[0] = "TEST"};

    while(strcmp(user_input, "quit") != 0){

        printf("Key in a command: ");
        scanf("%s", user_input);

        char *text;

        text = strtok(user_input, " ");
        int counter = 0;
        while(text != NULL){

            if(counter == 0){
                data_packet_instance.command = text;
            }
            data_packet_instance.command_argument[counter] = text;
            text = strtok(NULL, " ");
            counter++;
        }

        data_packet_instance.command_argument_size = counter;
        //line 79 determines whether a data gets send to server
        data_packet_instance = PROCESS_DATA_PACKET(data_packet_instance);

        char BUFFER[BUFSIZ];
        char *result;

        result = PROCESS_DATA_PACKET_FOR_TRANSMISSION(data_packet_instance);
        strcpy(BUFFER,result);

        if(strcmp(data_packet_instance.command_type, ftp_client_command_type[CLIENT]) == 0){
            EXECUTE_COMMAND_IN_CLIENT(data_packet_instance);
        }else if(strcmp(data_packet_instance.command_type, ftp_client_command_type[SERVER]) == 0 && strcmp(data_packet_instance.command, ftp_client_response_code[SEND_TO_SERVER_RESPONSE_CODE]) == 0) {
            printf("%s Sending command %s to FTP Server.... \n", data_packet_instance.response_code, data_packet_instance.command);
            //send data to server
            BUFFER = PROCESS_DATA_PACKET_FOR_TRANSMISSION(data_packet_instance);
            write_to_server(ftp_client_information.socket_file_descriptor, BUFFER);
        }else if(strcmp(data_packet_instance.command_type, ftp_client_command_type[SERVER]) == 0 && strcmp(data_packet_instance.command, ftp_client_response_code[SEND_FILE_TO_SERVER_RESPONSE_CODE]) == 0) {

        }

        read_from_server(ftp_client_information.socket_file_descriptor);

    }


	close_socket(ftp_client_information.socket_file_descriptor);

	return EXIT_SUCCESS;	
}

