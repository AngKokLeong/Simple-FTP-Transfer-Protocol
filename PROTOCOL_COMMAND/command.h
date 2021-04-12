//
// Created by angkokleong on 4/10/21.
//
#ifndef ICT374_ASSIGNMENT02_COMMAND_H
#define ICT374_ASSIGNMENT02_COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);

typedef struct{
    char *response_code;
    char *data;
    char *command_argument[255];
    int command_argument_size;
    char *command;
    char *command_type;
}DATA_PACKET;

#define SERVER 1
#define CLIENT 0

#define RESPONSE_CODE_SIZE 7
#define SUCCESS_RESPONSE_CODE 0
#define FAILURE_RESPONSE_CODE 1
#define PENDING_RESPONSE_CODE 2
#define SEND_TO_SERVER_RESPONSE_CODE 3
#define SEND_TO_CLIENT_RESPONSE_CODE 4
#define SEND_FILE_TO_CLIENT_RESPONSE_CODE 5
#define SEND_FILE_TO_SERVER_RESPONSE_CODE 6

#define SERVER_COMMAND_ARRAY_SIZE 5
#define SERVER_COMMAND_PWD 0
#define SERVER_COMMAND_DIR 1
#define SERVER_COMMAND_CD 2
#define SERVER_COMMAND_GET 3
#define SERVER_COMMAND_PUT 4

#define CLIENT_COMMAND_ARRAY_SIZE 4
#define CLIENT_COMMAND_PWD 0
#define CLIENT_COMMAND_DIR 1
#define CLIENT_COMMAND_CD 2
#define CLIENT_COMMAND_QUIT 3

#define COMMAND_ARGUMENT_DELIMITER '|'

#endif //ICT374_ASSIGNMENT02_COMMAND_H


DATA_PACKET PROCESS_MESSAGE_BUFFER_TO_DATA_PACKET(char *BUFFER);
DATA_PACKET PROCESS_DATA_PACKET(DATA_PACKET data_packet_instance);
char[] PROCESS_DATA_PACKET_FOR_TRANSMISSION(DATA_PACKET data_packet_instance);
void PRINT_WRONG_COMMAND_ERROR_MESSAGE();

DATA_PACKET SEND_FILE_TO_CLIENT(DATA_PACKET data_packet_instance);
DATA_PACKET SEND_FILE_TO_SERVER(DATA_PACKET data_packet_instance);
DATA_PACKET RECV_FILE_FROM_CLIENT(DATA_PACKET data_packet_instance);
DATA_PACKET RECV_FILE_FROM_SERVER(DATA_PACKET data_packet_instance);

DATA_PACKET EXECUTE_SERVER_COMMAND(DATA_PACKET data_packet_instance);
DATA_PACKET EXECUTE_COMMAND_IN_CLIENT(DATA_PACKET data_packet_instance);