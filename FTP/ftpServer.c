// Server (FTP)
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    FILE *fp;
    int sd, newsd, bd, port;
    socklen_t clilen;
    char rcv[100], fileread[100];
    struct sockaddr_in servaddr, cliaddr;

    printf("Enter the port address: ");
    scanf("%d", &port);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("Can't create socket");
        return -1;
    }
    printf("Socket is created.\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    bd = bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (bd < 0) {
        perror("Can't bind");
        return -1;
    }
    printf("Binded.\n");

    listen(sd, 5);

    clilen = sizeof(cliaddr);
    newsd = accept(sd, (struct sockaddr *)&cliaddr, &clilen);
    if (newsd < 0) {
        perror("Can't accept");
        return -1;
    }
    printf("Accepted.\n");

    int n = recv(newsd, rcv, sizeof(rcv) - 1, 0);
    if (n < 0) {
        perror("Can't receive filename");
        return -1;
    }
    rcv[n] = '\0';

    fp = fopen(rcv, "r");
    if (fp == NULL) {
        perror("Can't open file");
        send(newsd, "error!", 6, 0);
        close(newsd);
        return -1;
    }

    while (fgets(fileread, sizeof(fileread), fp)) {
        if (send(newsd, fileread, strlen(fileread), 0) < 0) {
            perror("Can't send file contents");
            return -1;
        }
        sleep(1);
    }

    if (feof(fp)) {
        send(newsd, "completed", strlen("completed"), 0);
    }

    fclose(fp);
    close(newsd);
    close(sd);

    return 0;
}