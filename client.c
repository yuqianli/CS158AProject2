/*
 * client.c - A simple UDP client
 * usage: client <host>
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
#include <time.h>
#define SERVER_PORT 5432
#define BUFSIZE 1024

int main(int argc, char * argv[])
{
	struct sockaddr_in serveraddr; 	/* server address */
	int addrlen=sizeof(serveraddr); /* server address length */
	struct hostent *hp;
	char *host;
	char buf[BUFSIZE]; /* message buffer */
	int s; /* socket */
	int len;; /* lenght of buffer message */
	int n; /* number of bytes sendto or recvfrom */
	time_t currenttime; /* current time */


	if (argc==2) {
		host = argv[1];
	}

	else {
		fprintf(stderr, "Usage: client <host>");
		exit(1);
	}

	/* translate host name into peer's IP address */
	hp = gethostbyname(host);
	if (!hp) {
		fprintf(stderr, "Unknown host: %s", host);
		exit(1);
	}

	/* build address data structure */
	bzero((char *)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	bcopy(hp->h_addr, (char *)&serveraddr.sin_addr, hp->h_length);
	serveraddr.sin_port = htons(SERVER_PORT);

	/* active open */
	if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("ERROR in server: socket");
		exit(1);
	}

	/* main loop: get and send lines of text */
	while (1) {
		time (&currenttime);
		fgets(buf, sizeof(buf), stdin);
		len = strlen(buf) + 1;
		printf("%s", ctime(&currenttime));
		/* message send to server */
		if (n = sendto(s, buf, len, 0, &serveraddr, addrlen ) < 0)
			perror("ERROR in sendto");

		/* message receive from server */
		if (n = recvfrom(s, buf, strlen(buf), 0, (struct sockaddr *) &serveraddr, &addrlen) < 0)
			perror("ERROR in recvform");

		buf[strlen(buf)-1] = '\0';
		printf("Return from server: %s	 %s", buf, ctime(&currenttime));
	}
}
