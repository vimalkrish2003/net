#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // Include this for the close function

int main()
{
    char buf[100];
    int server_sock_desc, client_sock_desc;
    struct sockaddr_in server, client; // Declare a separate struct for the client
    socklen_t client_len;              // Declare a variable for the size of client

    server_sock_desc = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003);

    bind(server_sock_desc, (struct sockaddr *)&server, sizeof(server));

    listen(server_sock_desc, 5);

    client_len = sizeof(client);                                                          // Set client_len to the size of client
    client_sock_desc = accept(server_sock_desc, (struct sockaddr *)&client, &client_len); // Use client here
    recv(client_sock_desc, buf, sizeof(buf) - 1, 0);

    buf[sizeof(buf) - 1] = '\0';
    printf("Message got from client: %s", buf);

    close(client_sock_desc); // Now close should be recognized

    return 0;
}