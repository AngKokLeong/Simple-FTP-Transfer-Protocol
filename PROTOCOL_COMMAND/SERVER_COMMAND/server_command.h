//
// Created by angkokleong on 4/10/21.
//

#ifndef ICT374_ASSIGNMENT02_SERVER_COMMAND_H
#define ICT374_ASSIGNMENT02_SERVER_COMMAND_H

typedef struct MESSAGE_STRUCTURE_SERVER{
    char current_response_code;
    char *unix_command_to_execute_options;
    char *unix_command_to_execute;
    char *command_option;
    char *command;
    char *result;
}MESSAGE_STRUCTURE_SERVER;

MESSAGE_STRUCTURE_SERVER message_structure_server;

void PROCESS_MESSAGE_SERVER_FROM_CLIENT();

//used in Ftp client and server program
void SEND_MESSAGE_SERVER_TO_CLIENT();
void RECEIVE_MESSAGE_SERVER_FROM_CLIENT();

void EXECUTE_COMMAND_SERVER_TO_CLIENT();


#endif //ICT374_ASSIGNMENT02_SERVER_COMMAND_H