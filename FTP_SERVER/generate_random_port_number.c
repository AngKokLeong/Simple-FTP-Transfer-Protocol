#include "server_helper_function.h"

int generate_random_port_number(){
	int port_number = (rand() % (40000 - 1500 + 1)) + 1500;
	return port_number;
}
