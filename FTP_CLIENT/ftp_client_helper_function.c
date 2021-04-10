#include "ftp_client_helper_function.h"

bool verify_ip_address(char *ip_address_or_hostname){
	struct sockaddr_in sa;
	int result = inet_pton(PF_INET, ip_address_or_hostname, &(sa.sin_addr));
	return result != 0;	
}



//returns an array
char** string_splitter(char *string_to_be_split, const char delimiter){
    char **result = 0;
    size_t count = 0;
    char *tmp = string_to_be_split;
    char *last_delimiter = 0;

    char delim[2];
    delim[0] = delimiter;
    delim[1] = 0;

    while(*tmp){
        if(delimiter == *tmp){
            count++;
            last_delimiter = tmp;
        }
        tmp++;
    }

    count += last_comma < (string_to_be_split + strlen(string_to_be_split) - 1);

    count++;

    result = malloc(sizeof(char *) * count);

    if(result){
        size_t index = 0;
        char *token = strtok(string_to_be_split, delim);

        while(token){
            assert(index < count);
            *(result + index++) = strdup(token);
            token = strtok(0, delim);
        }

        assert(index == count - 1);
        *(result + index) = 0;
    }
    return result;
}

//returns the decimal of the ip address through conversion
int convert_ip_address_to_integer(char *ip_address){
    char **splitted_ip_address;
    int converted_ip_address_to_integer = 0;
    splitted_ip_address = string_splitter(ip_address, '.');

    int current_octet_power = 3;

    if(splitted_ip_address){
        int i;
        for(i = 0; *(splitted_ip_address + i); i++){
            char *value = *(splitted_ip_address + i);
            int integer_value = atoi(value);

            converted_ip_address_to_integer += (int)integer_value * pow(256, current_octet_power);

            current_octet_power--;
            free(*(splitted_ip_address + i));
        }
        free(splitted_ip_address);
    }

    return converted_ip_address_to_integer;
}