#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>


int main()
{
	int sock_cli = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(sock_cli == -1){
		printf("socket error");
		return -1;
	}


	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET; /* use IPv4 */
	servaddr.sin_port = htons(8887); /* TCP Server's port */
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); /* TCP Server's IP */

	/* int connect(int sockfd, const struct sockaddr * servaddr, socklen_t addrlen) 
       3-way-handshake
	*/
	if(connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
		printf("connect error");
		return -1;
	}

	char str[64];
	read(sock_cli, str, 64);
	printf(str);

	close(sock_cli);
}