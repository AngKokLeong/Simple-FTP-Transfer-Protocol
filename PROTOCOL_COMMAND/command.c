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



DATA_PACKET PROCESS_DATA_PACKET(DATA_PACKET data_packet_instance){

    for(int i=0; i<SERVER_COMMAND_ARRAY_SIZE; i++){
        if(strcmp(data_packet_instance.command, server_command_array[SERVER_COMMAND_GET]) == 0) {

            data_packet_instance.command_type = command_type[SERVER];
            data_packet_instance.response_code = response_code[SEND_FILE_TO_CLIENT_RESPONSE_CODE];
            return data_packet_instance;
        }else if(strcmp(data_packet_instance->command, server_command_array[SERVER_COMMAND_PUT]) == 0) {

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

    return data_packet_instance
}

void EXECUTE_SERVER_COMMAND(DATA_PACKET *data_packet_instance){
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
        execvp(data_packet_instance->command, data_packet_instance->command_argument);
        die("execvp");
    } else if(pid > 0) {
        close(link[1]);
        read(link[0], output, sizeof(output));
        //store output into message structure and send it back to client
        data_packet_instance->data = output;
        data_packet_instance->response_code = response_code[SEND_TO_CLIENT_RESPONSE_CODE];
        wait(NULL);
    }

}

void EXECUTE_COMMAND_IN_CLIENT(DATA_PACKET *data_packet_instance){
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
        execvp(data_packet_instance->command, data_packet_instance->command_argument);
        die("execvp");
    } else if(pid > 0) {
        close(link[1]);
        read(link[0], output, sizeof(output));

        data_packet_instance->data = output;
        data_packet_instance->response_code = response_code[SUCCESS_RESPONSE_CODE];
        printf("%s", data_packet_instance->data);
        wait(NULL);
        //store output into message structure and send it back to client


    }
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