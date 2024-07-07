// Client (UDP)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    struct sockaddr_in server;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        printf("Error in socket creation!\n");
        return -1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost
    server.sin_port = htons(3003); // port number

    char buffer[100];
    printf("Enter a message to send to server: ");
    fgets(buffer, 100, stdin);

    if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Error in sending!\n");
        return -1;
    }

    return 0;
}