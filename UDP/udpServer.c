// Server (UDP)
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        printf("Error in socket creation!\n");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003); 

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error in bind()!\n");
        return -1;
    }

    char buffer[100];
    printf("Server waiting...\n");

    if (recvfrom(sockfd, buffer, 100, 0, (struct sockaddr *)&client, &client_len) < 0) {
        printf("Error in receiving!\n");
        return -1;
    }

    printf("Got a datagram: %s", buffer);
    return 0;
}