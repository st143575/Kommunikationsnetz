#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>


int main() 
{
	/* create a socket-discriptor: server_sockfd
	   int socket(int famlily, int type, int protocol);
	   domain: protocol suite
	*/
	int server_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(server_sockfd == -1){
		printf("socket error");
		return -1;
	}


	/* sockaddr_in: address of protocol. It's a defined structure. */
	struct sockaddr_in server_sockaddr;  /* server_sockaddr of type sockaddr_in */
	server_sockaddr.sin_family = AF_INET;  /* use IPv4 */
	server_sockaddr.sin_port = htons(8887);  /* listen port 8887 */								 
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* bind local IP with macro */

	/* int bind(int sockfd, const struct sockaddr * myaddr, socklen_t addrlen)
	   assigns the local protocol address to a socket
	 */
	if(bind(server_sockfd, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1){
		printf("bind error");
		return -1;
	}

	/* int listen(int sockfd, int backlog) */
	if(listen(server_sockfd, 20) == -1){
		printf("listen error");
		return -1;
	}


	/* infinite loop to keep the server on */
	for( ; ; ){
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	int clnt_sock = accept(server_sockfd, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
	/* int accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
	   sockfd: listening socket
	 */

	if(clnt_sock == -1){
		printf("accept error");
		return -1;
	}

	char str[] = "Hello. This is a message from server.";
	write(clnt_sock, str, sizeof(str));
	
	close(clnt_sock);
	/* close(server_sockfd); */
	}

}
