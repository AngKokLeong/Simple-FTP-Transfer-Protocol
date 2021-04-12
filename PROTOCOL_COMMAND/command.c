#include "command.h"

char response_code[7][1] = {
        "+", //SUCCESS RESPONSE CODE
        "-", //FAILURE RESPONSE CODE
        "=", //PENDING PROCESSING RESPONSE CODE
        "!", // SEND TO SERVER RESPONSE CODE
        "@", // SEND TO CLIENT RESPONSE CODE
        "#", // SEND FILE TO CLIENT RESPONSE CODE
        "%" // SEND FILE TO SERVER RESPONSE CODE
};

char *command_type[2] = {
        "CLIENT",
        "SERVER"
};

char *client_command_array[4] = {
        "pwd",
        "dir",
        "cd",
        "quit"
};

char *server_command_array[5] = {
        "lpwd",
        "ldir",
        "lcd",
        "get",
        "put"
};

DATA_PACKET PROCESS_MESSAGE_BUFFER_TO_DATA_PACKET(char *BUFFER){
    //Response Code ID - Command Type ID - Command ID - Command Argument with delimiter - Data

    DATA_PACKET data_packet_instance;
    char *copy_buffer = BUFFER;

    char *token;
    char *rest = copy_buffer;

    int counter = 1;

    while((token = strtok_r(rest, "-", &rest))){
        if(counter == 1){
            data_packet_instance.response_code = response_code[atoi(token)];
        }else if(counter == 2){
            data_packet_instance.command_type = command_type[atoi(token)];
        }else if(counter == 3){
            if(strcmp(data_packet_instance.command_type, command_type[0]) == 0){
                data_packet_instance.command = client_command_array[atoi(token)];
            }else{
                data_packet_instance.command = server_command_array[atoi(token)];
            }
        }else if(counter == 4){
            char *token_command_argument;
            char *rest_command_argument = token;
            int command_argument_counter = 0;
            while((token_command_argument = strtok_r(rest_command_argument, "|", &rest_command_argument))){
                data_packet_instance.command_argument[command_argument_counter] = token_command_argument;
                command_argument_counter++;
            }

        }else if(counter == 5){
            data_packet_instance.data = token;
        }
        counter++;
    }
    return data_packet_instance;
}

DATA_PACKET PROCESS_DATA_PACKET(DATA_PACKET data_packet_instance){

    for(int i=0; i<SERVER_COMMAND_ARRAY_SIZE; i++){
        if(strcmp(data_packet_instance.command, server_command_array[SERVER_COMMAND_GET]) == 0) {

            data_packet_instance.command_type = command_type[SERVER];
            data_packet_instance.response_code = response_code[SEND_FILE_TO_CLIENT_RESPONSE_CODE];
            return data_packet_instance;
        }else if(strcmp(data_packet_instance.command, server_command_array[SERVER_COMMAND_PUT]) == 0) {

            data_packet_instance.command_type = command_type[SERVER];
            data_packet_instance.response_code = response_code[SEND_FILE_TO_SERVER_RESPONSE_CODE];

            return data_packet_instance;
        }else if(strcmp(data_packet_instance.command, server_command_array[i]) == 0) {
            //if there is a match
            //create a structure and store relevant information
            data_packet_instance.response_code = response_code[SEND_TO_SERVER_RESPONSE_CODE];
            data_packet_instance.command_type = command_type[SERVER];
            return data_packet_instance;
        }
    }

    for(int i=0; i<CLIENT_COMMAND_ARRAY_SIZE; i++){
        if(strcmp(data_packet_instance.command, client_command_array[i]) == 0){
            data_packet_instance.response_code = response_code[SUCCESS_RESPONSE_CODE];
            data_packet_instance.command_type = command_type[CLIENT];
            return data_packet_instance;
        }
    }

    return PRINT_WRONG_COMMAND_ERROR_MESSAGE(data_packet_instance);
}

DATA_PACKET PRINT_WRONG_COMMAND_ERROR_MESSAGE(DATA_PACKET data_packet_instance){
    data_packet_instance.response_code = response_code[FAILURE_RESPONSE_CODE];
    sprintf(data_packet_instance.data,"There is no such command available for [%s]\n", data_packet_instance.command);

    return data_packet_instance;
}

DATA_PACKET EXECUTE_SERVER_COMMAND(DATA_PACKET data_packet_instance){
    //run execl
    //check the command type
    //if the command is send or put

    pid_t pid;
    int link[2];
    char output[BUFSIZ];

    if (pipe(link)==-1)
        die("pipe");

    if ((pid = fork()) < 0)
        die("fork");

    if(pid == 0) {
        dup2 (link[1], STDOUT_FILENO);
        close(link[0]);
        close(link[1]);
        execvp(data_packet_instance.command, data_packet_instance.command_argument);
        die("execvp");
    } else if(pid > 0) {
        close(link[1]);
        read(link[0], output, sizeof(output));
        //store output into message structure and send it back to client
        data_packet_instance.data = output;
        data_packet_instance.response_code = response_code[SEND_TO_CLIENT_RESPONSE_CODE];
        wait(NULL);
    }
    return data_packet_instance;
}

DATA_PACKET EXECUTE_COMMAND_IN_CLIENT(DATA_PACKET data_packet_instance){
    //run execl
    pid_t pid;
    int link[2];
    char output[BUFSIZ];

    if (pipe(link)==-1)
        die("pipe");

    if ((pid = fork()) < 0)
        die("fork");

    if(pid == 0) {
        dup2 (link[1], STDOUT_FILENO);
        close(link[0]);
        close(link[1]);
        execvp(data_packet_instance.command, data_packet_instance.command_argument);
        die("execvp");
    } else if(pid > 0) {
        close(link[1]);
        read(link[0], output, sizeof(output));

        data_packet_instance.data = output;
        data_packet_instance.response_code = response_code[SUCCESS_RESPONSE_CODE];
        printf("%s", data_packet_instance.data);
        wait(NULL);
        //store output into message structure and send it back to client


    }
    return data_packet_instance;
}

DATA_PACKET SEND_FILE_TO_CLIENT(DATA_PACKET data_packet_instance){
    //use send()

    return data_packet_instance;
}

DATA_PACKET SEND_FILE_TO_SERVER(DATA_PACKET data_packet_instance){
    //use send()
    return data_packet_instance;
}

DATA_PACKET RECV_FILE_FROM_CLIENT(DATA_PACKET data_packet_instance){
    //use recv()
    return data_packet_instance;
}
DATA_PACKET RECV_FILE_FROM_SERVER(DATA_PACKET data_packet_instance) {
    //use recv()
    return data_packet_instance;
}

char* PROCESS_DATA_PACKET_FOR_TRANSMISSION(DATA_PACKET data_packet_instance){
    char BUFFER[BUFSIZ];
    //Response Code ID - Command Type ID - Command ID - Command Argument with delimiter - Data

    for(int i=0; i < RESPONSE_CODE_SIZE; i++){
        if(strcmp(data_packet_instance.response_code, response_code[i]) == 0){
            char index[2];
            sprintf(index, "%d", i);
            strcat(BUFFER, index);
        }
    }

    strcat(BUFFER, "-");

    if(strcmp(data_packet_instance.command_type, command_type[0]) == 0){
        strcat(BUFFER, "0");

        strcat(BUFFER, "-");
        for(int i=0; i<CLIENT_COMMAND_ARRAY_SIZE; i++){
            if(strcmp(data_packet_instance.command, client_command_array[i]) == 0){
                char index[2];
                sprintf(index, "%d", i);
                strcat(BUFFER, index);
            }
        }
    }else if(strcmp(data_packet_instance.command_type, command_type[1]) == 0){
        strcat(BUFFER, "1");

        strcat(BUFFER, "-");

        for(int i=0; i<SERVER_COMMAND_ARRAY_SIZE; i++){
           if(strcmp(data_packet_instance.command, server_command_array[i]) == 0) {
                char index[2];
                sprintf(index, "%d", i);
                strcat(BUFFER, index);
            }
        }
    }

    strcat(BUFFER, "-");
    //get command arguments from DATA PACKET

    //delimiter
    for(int i=0; i <= data_packet_instance.command_argument_size; i++){
        strcat(BUFFER, data_packet_instance.command_argument[i]);
        if(i != data_packet_instance.command_argument_size)
            strcat(BUFFER, "|");
    }


    strcat(BUFFER, "-");

    if(!data_packet_instance.data){
        strcat(BUFFER, data_packet_instance.data);
    }

    return BUFFER;
}