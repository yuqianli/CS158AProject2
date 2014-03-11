/*
 * server.c - A simple UDP server
 * usage: server
 * CS158A Project 2
 * Date created : Mar 7, 2014
 * Date last modified : Mar 10, 2014
 * Authors: Yu Li, Kevin Tan, John Miller, Eric Tam
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define SERVER_PORT 5432
#define MAX_PENDING 5
#define MAX_LINE 256
#define BUFSIZE 1024

int main()
{
	struct sockaddr_in serveraddr; /* server address */
	struct sockaddr_in remaddr; /* remote address */ 
	int addrlen = sizeof(remaddr); /* length of addresses */
	char buf[BUFSIZE]; /* message buffer */
	int s; /* socket */
	int n; /* number of bytes received from recvfrom */

	/* build address data structure */
	bzero((char *)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(SERVER_PORT);

	/* setup passive open */
	if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("ERROR in server: socket");
		exit(1);
	}

	/* bind: associate the parent's socket with a port */
	if ((bind(s, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0) {
		perror("ERROR in server: bind");
		exit(1);
	}
	
	/* main loop fuction*/
	while (1){
		/*receive message from client*/
		if (n = recvfrom(s, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen) < 0)
			perror("ERROR in recvfrom");
		fputs(buf, stdout);

		/*send message back to client*/
		if ( n = sendto(s, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, addrlen) < 0)
			perror("ERROR in sendto");

		close(n);
	}
}
