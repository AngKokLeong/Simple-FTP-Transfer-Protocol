#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <assert.h>

bool verify_ip_address(char *ip_address_or_hostname);
char** string_splitter(char *string_to_be_split, const char delimiter);
int convert_ip_address_to_integer(char *ip_address);