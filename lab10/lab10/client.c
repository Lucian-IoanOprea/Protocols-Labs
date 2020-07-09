#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

#define SERVER "3.8.116.10"

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    int sockfd;
    // Ex 1
    sockfd = open_connection(SERVER, 8080, AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0) {
        perror("Socket error!");
        exit(-1);
     }

    message = compute_get_request(SERVER, "/api/v1/dummy", NULL, NULL, 0);
    send_to_server(sockfd, message);
    printf("%s", message);
    response = receive_from_server(sockfd);
    printf("%s\n", response);
    
    // Ex 2
    char *body_data = "data=10&nume=sef";
    char *content_type = "application/x-www-form-urlencoded";
    message = compute_post_request(SERVER, "/api/v1/dummy", content_type, body_data, NULL, 0);
    send_to_server(sockfd, message);
    printf("%s", message);
    response = receive_from_server(sockfd);
    printf("%s\n", response);

    // Ex 3
    char *body_data1 = "username=student&password=student";
    message = compute_post_request(SERVER, "/api/v1/auth/login", content_type, body_data1, NULL, 0);
    send_to_server(sockfd, message);

    printf("%s", message);
    response = receive_from_server(sockfd);
    printf("%s\n", response);

    // Ex 4
    char *find = strstr(response, "connect");
    char *cookie = malloc(1 * sizeof(char));
    for (int i = 0; *(find) != ';' ; ++find) {
        cookie[i] = *find;
        cookie = realloc(cookie, (++i) * sizeof(char));
    }
    
    char *cookies[1] = {cookie};
    message = compute_get_request(SERVER, "/api/v1/weather/key ", NULL,
        cookies, 1);
    send_to_server(sockfd, message);
    printf("%s", message);
    response = receive_from_server(sockfd);
    printf("%s\n", response);

    // Ex 5
    message = compute_get_request(SERVER, "/api/v1/auth/logout", NULL, cookies, 1);
    send_to_server(sockfd, message);
    printf("%s", message);
    
    response = receive_from_server(sockfd);
    printf("%s\n", response);
    message = compute_get_request(SERVER, "/api/v1/weather/key ", NULL,
        cookies, 1);
    send_to_server(sockfd, message);
    printf("%s\n", message);

    response = receive_from_server(sockfd);
    printf("%s\n", response);
    close_connection(sockfd);

    
    free(cookie);
    return 0;
}
