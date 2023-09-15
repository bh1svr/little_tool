#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE 1024

// Driver code
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s ip port delay\n", argv[0]);
        return 0;
    }
	int sockfd;
    char buf[1000];
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	int n;
	socklen_t len;

    while (true)
    {
	    sendto(sockfd, (const char *)buf, sizeof(buf),
		    MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = atoi(argv[3]) * 1000000;
        nanosleep(&ts, NULL);
	}
	close(sockfd);
	return 0;
}

