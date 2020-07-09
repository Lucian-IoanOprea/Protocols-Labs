// Protocoale de comunicatii
// Laborator 9 - DNS
// dns.c

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int usage(char* name)
{
	printf("Usage:\n\t%s -n <NAME>\n\t%s -a <IP>\n", name, name);
	return 1;
}

// Receives a name and prints IP addresses
void get_ip(char* name)
{
	int ret;
	struct addrinfo hints, *result, *p;

	// TODO: set hints
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_protocol = IPPROTO_TCP;


	// TODO: get addresses
	if ((ret = getaddrinfo(name, NULL, &hints, &result)) < 0) {
		gai_strerror(ret);
	}
	// TODO: iterate through addresses and print them
	for (p = result ; p ; p = p->ai_next) {
			if (p->ai_family == AF_INET) {
				char ipv4[INET_ADDRSTRLEN];
				struct sockaddr_in *addr = (struct sockaddr_in *) p->ai_addr;
				if (inet_ntop(p->ai_family, &(addr->sin_addr), ipv4, sizeof(ipv4)) != NULL) {
					fprintf(stdout, "The IPv4 address is: %s\n", ipv4);
				}

				break;
			}

			else if( p->ai_family == AF_INET6) {
				char ipv6[INET6_ADDRSTRLEN];
				struct sockaddr_in6 *addr = (struct sockaddr_in6 *) p->ai_addr;
				if (inet_ntop(p->ai_family, &(addr->sin6_addr), ipv6, sizeof(ipv6)) != NULL) {
					fprintf(stdout, " The IPv6 address is: %s\n", ipv6);
				}
				break;
			}
	}

	freeaddrinfo(result);
	// TODO: free allocated data
}

// Receives an address and prints the associated name and service
void get_name(char* ip)
{
	int ret;
	struct sockaddr_in addr;
	char host[1024];
	char service[20];

	// TODO: fill in address data
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	inet_aton(ip, &addr.sin_addr);
	// TODO: get name and service
	if ((ret = getnameinfo ((struct sockaddr *)&addr, sizeof(struct sockaddr_in), host, sizeof(host), service, sizeof(service), 0)) < 0) {
		gai_strerror(ret);
	}
	// TODO: print name and service
	fprintf(stdout, "Name: %s\nService: %s\n", host, service);
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		return usage(argv[0]);
	}
	if (strncmp(argv[1], "-n", 2) == 0) {
		get_ip(argv[2]);
	} else if (strncmp(argv[1], "-a", 2) == 0) {
		get_name(argv[2]);
	} else {
		return usage(argv[0]);
	}

	return 0;
}
