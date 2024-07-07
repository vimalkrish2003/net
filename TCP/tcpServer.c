#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // Include this for the close function

int main()
{
    char buf[100];
    int sock_desc, temp_sock_desc;
    struct sockaddr_in server;
    socklen_t len; // Declare a variable for the size of server

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003);

    bind(sock_desc, (struct sockaddr *)&server, sizeof(server));

    listen(sock_desc, 5);

    len = sizeof(server); // Set len to the size of server
    temp_sock_desc = accept(sock_desc, (struct sockaddr *)&server, &len); // Pass &len instead of &(sizeof(server))
    recv(temp_sock_desc, buf, sizeof(buf) - 1, 0);

    buf[sizeof(buf) - 1] = '\0';
    printf("Message got from client: %s", buf);

    close(temp_sock_desc); // Now close should be recognized

    return 0;
}