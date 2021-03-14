#include <stdio.h>


#if !defined(_WIN32)
	#define SOCKET int
#endif


#if defined(_WIN32)
	#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#else
	#define ISVALIDSOCKET(s) ((s) >= 0)
#endif

#if defined(_WIN32)
	#define GETSOCKETERRNO() (WSAGetLastError())
#else
	#define GETSOCKETERRNO() (errno)
#endif


char *initial_current_directory;

void ftp_server_driver(char *current_directory){
	
	initial_current_directory = current_directory;
	printf("The current directory: %s\n", initial_current_directory);
}




