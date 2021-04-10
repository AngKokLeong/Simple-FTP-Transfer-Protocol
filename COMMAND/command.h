//
// Created by angkokleong on 4/10/21.
//

#ifndef ICT374_ASSIGNMENT02_COMMAND_H
#define ICT374_ASSIGNMENT02_COMMAND_H

#include <stdio.h>
#include <stdlib.h>

typedef struct MESSAGE_STRUCTURE{
    char current_response_code;
    char *unix_command_to_execute_options;
    char *unix_command_to_execute;
    char *command_option;
    char *command;
}MESSAGE_STRUCTURE;

MESSAGE_STRUCTURE message_structure;

char* PROCESS_MESSAGE();

//used in Ftp client and server program
void SEND_MESSAGE();
void RECEIVE_MESSAGE();

void EXECUTE_COMMAND();







#endif //ICT374_ASSIGNMENT02_COMMAND_H
