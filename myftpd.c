#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "FTP_SERVER/ftp_server_driver.h"

int main(int argc , char *argv[])
{

	if(argc == 2){
		
		ftp_server_driver_execution(argv[1]);
	}else{
		printf("Please key in the file path you want to setup the FTP\n");
		printf("Terminating program....\n");
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
	/*

    	//create socket
	int socket_desc;
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	
	if (socket_desc == -1)
	{
		printf("Could not create socket.\n");
	}
    	//end create socket

    	//server
	server.sin_addr.s_addr = 0;
	server.sin_port = atoi(argv[1]);

    	//bind socket to port
    	if(bind(socket_desc,(struct sockaddr*)&server,sizeof(server)) == -1){
        	printf("Binding error\n");
        	exit(1);
    	}
    	puts("Bind done.\n");
    	//end bind

    	//listen incoming connnections
    	if(listen(socket_desc, 1) == -1){
        	printf("Listen failed.\n");
    	}

    	//accept incoming connection
    	int len = sizeof(struct sockaddr_in); 
    	int new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&len);
	if(new_socket < 0){
        	perror("Accept failed..\n");
    	}
    	puts("Connection accepted...\n");

    	//read file
    	int i = 1, size, c;
    	char buf[100], command[5], filename[20];
    	int filehandle;
    	struct stat obj;


	initialize_daemon_process();

	pid = getpid();
	printf("server pid: %d", pid);	

	//need to create another fork() to end child process and parent process
	//create a parent process for each socket connection
		

    	while (1) {

		


        	recv(new_socket, buf, 100, 0);
        	sscanf(buf, "%s", command);
        	if (!strcmp(command, "ls")) {
            		system("ls >temps.txt");
            		i = 0;
            		stat("temps.txt", & obj);
            		size = obj.st_size;
            		send(new_socket, & size, sizeof(int), 0);
		//skip all important code folder when server is going to list the files
		//
            		filehandle = open("temps.txt", O_RDONLY);
            		sendfile(new_socket, filehandle, NULL, size);

        	} else if (!strcmp(command, "get")) {
            		sscanf(buf, "%s%s", filename, filename);
            		stat(filename, & obj);
			filehandle = open(filename, O_RDONLY);
			size = obj.st_size;
			if (filehandle == -1)
			    size = 0;
			send(new_socket, & size, sizeof(int), 0);
			if (size)
			    sendfile(new_socket, filehandle, NULL, size);

		} else if (!strcmp(command, "put")) {
		    int c = 0, len;
		    char * f;
		    sscanf(buf + strlen(command), "%s", filename);
		    recv(new_socket, & size, sizeof(int), 0);
		    i = 1;
		    while (1) {
		    filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
		    if (filehandle == -1) {
		    sprintf(filename + strlen(filename), "%d", i);
		    } else
		    break;
		    }
		    f = malloc(size);
		    recv(new_socket, f, size, 0);
		    c = write(filehandle, f, size);
		    close(filehandle);
		    send(new_socket, & c, sizeof(int), 0);
		} else if (!strcmp(command, "pwd")) {
		    system("pwd>temp.txt");
		    i = 0;
		    FILE * f = fopen("temp.txt", "r");
		    while (!feof(f))
		    buf[i++] = fgetc(f);
		    buf[i - 1] = '\0';
		    fclose(f);
		    send(new_socket, buf, 100, 0);
		} else if (!strcmp(command, "cd")) {
		    if (chdir(buf + 3) == 0)
		    c = 1;
		    else
		    c = 0;
		    send(new_socket, & c, sizeof(int), 0);
		} else if (!strcmp(command, "bye") || !strcmp(command, "quit")) {
		    printf("FTP server quitting..\n");
		    i = 1;
		    send(new_socket, & i, sizeof(int), 0);
		    exit(0);
		}
      	}
	*/

}
