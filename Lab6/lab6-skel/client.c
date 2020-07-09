/*
*  	Protocoale de comunicatii: 
*  	Laborator 6: UDP
*	client mini-server de backup fisiere
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
	fprintf(stderr,"Usage: %s ip_server port_server file\n",file);
	exit(0);
}

/*
*	Utilizare: ./client ip_server port_server nume_fisier_trimis
*/

int main(int argc,char**argv)
{
	if (argc < 4)
		usage(argv[0]);
	
	int fd;
	struct sockaddr_in to_station;
	char buf[BUFLEN];


	/*Deschidere socket*/
	int socketused = socket(PF_INET, SOCK_DGRAM, 0);

	if (socketused < 0) {
		fprintf(stderr, "Couldn't create socket.\n");
		exit(EXIT_FAILURE);
	}
	
	to_station.sin_family = AF_INET;
	to_station.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1], &to_station.sin_addr);
	memset(buf, 0, BUFLEN);
	sprintf(buf, "%d", argc - 3);
	sendto(socketused, buf, strlen(buf), 0, (struct sockaddr *) &to_station, sizeof(to_station));
	int i = 3;
	while (i < argc) {
		DIE((fd=open(argv[i],O_RDONLY))==-1,"open file");
		memset(buf, 0, BUFLEN);
		sprintf(buf, "%s", argv[i]);
		sendto(socketused, buf, strlen(buf), 0, (struct sockaddr *) &to_station, sizeof(to_station));
		memset(buf, 0, BUFLEN);
		
		int read_bytes;

		while ((read_bytes = read(fd, buf, BUFLEN))) {
			sendto(socketused, buf, read_bytes, 0, (struct sockaddr *) &to_station, sizeof(to_station));
			memset(buf, 0, BUFLEN);
			usleep(1000);
		}
		
		memset(buf, 0, BUFLEN);
		sprintf(buf, "DONE");
		sendto(socketused, buf, 5, 0, (struct sockaddr *) &to_station, sizeof(to_station));
		close(fd);
		i++;
	}
	close(socketused);
	
	return 0;
}
