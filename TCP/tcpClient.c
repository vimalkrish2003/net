#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h> // Include this for the fgets function

int main()
{
    char buf[100];
    int sock_desc;
    struct sockaddr_in server;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(3003);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_desc, (struct sockaddr *)&server, sizeof(server));

    printf("Enter a message: ");
    fgets(buf, sizeof(buf), stdin); // Read a line of input from the user

    send(sock_desc, buf, strlen(buf), 0);

    close(sock_desc);

    return 0;
}