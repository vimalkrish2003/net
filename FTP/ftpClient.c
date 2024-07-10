#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(){
	int client_sock_desc;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t clientAddrSize;
	
	FILE* fp;
	//create client socket and serverAddr struct
	client_sock_desc = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5600);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//connect to server
	connect(client_sock_desc,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
	printf("Connected to server at port:5600\n");
	
	//send filename to server
	printf("Enter filename:");
	scanf("%s",buffer);
	send(client_sock_desc,buffer,sizeof(buffer),0);
	
	//receive file from server
	printf("File received from server:\n");
	while(1){
	recv(client_sock_desc,buffer,sizeof(buffer),0);
	if(strncmp(buffer,"EOF",3)==0){
		printf("\nGot: EOF");
		break;
		}
	else if(strncmp(buffer,"NOF",3)==0){
		printf("FILE NOT FOUND on server!!!\n");
		break;
		}
	printf("%s",buffer);
	}
	
	close(client_sock_desc);
	return 0;
}