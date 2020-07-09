/*
*  	Protocoale de comunicatii: 
*  	Laborator 6: UDP
*	mini-server de backup fisiere
*/

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "helpers.h"


void usage(char*file)
{
	fprintf(stderr,"Usage: %s server_port file\n",file);
	exit(0);
}

/*
*	Utilizare: ./server server_port nume_fisier
*/
int main(int argc,char**argv)
{
	int fd;

	if (argc < 2)
		usage(argv[0]);
	
	struct sockaddr_in from_station ;
	char buf[BUFLEN];
	char buf_name[BUFLEN];
	socklen_t client_len;

	int socketused = socket(PF_INET, SOCK_DGRAM, 0);

	if (socketused  < 0) {
		fprintf(stderr, "Couldn't create socket.\n");
		exit(EXIT_FAILURE);
	}
	

	from_station.sin_family = AF_INET;
	from_station.sin_port = htons(atoi(argv[1]));
	from_station.sin_addr.s_addr = INADDR_ANY;

	bind(socketused, (struct sockaddr *) &from_station, sizeof(from_station));
	memset(buf, 0, BUFLEN);
	recvfrom(socketused, buf, BUFLEN, 0, (struct sockaddr *) &from_station, &client_len);
	int iterations = atoi(buf);
	for (int i = 0 ; i < iterations; ++i) {
		memset(buf, 0, BUFLEN);
		recvfrom(socketused, buf, BUFLEN, 0, (struct sockaddr *) &from_station, &client_len);
		
		strcat(buf, ".recv");
		DIE((fd=open(buf,O_WRONLY|O_CREAT|O_TRUNC,0644))==-1,"open file");
		memset(buf, 0, BUFLEN);
		while (1) {
			int read_bytes = recvfrom(socketused, buf, BUFLEN, 0, (struct sockaddr *) &from_station, &client_len);
			if (strcmp(buf, "DONE") == 0) {
				break;
			}

			write(fd, buf, read_bytes);
			memset(buf, 0, BUFLEN);
			
		}

		close(fd);	
	}
		
	close(socketused);
	return 0;
}
