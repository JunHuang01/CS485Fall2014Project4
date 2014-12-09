#include "../include/csapp.h"


int echo(int connfd){
    size_t n; 
    char buf[MC_MAX_FILE_SIZE]; 
    rio_t rio;

    

    

    Rio_readinitb(&rio, connfd);
    n = Rio_readn(connfd, buf, MC_MAX_FILE_SIZE);//line:netp:echo:eof
	printf("server received %d bytes\n", (int)n);

    int res = -1;
    memcpy(buf,&res,sizeof(int));
    Rio_writen(connfd, buf, 4);
}


int main(int argc, char **argv) 
{
    int listenfd, connfd, port, clientlen;
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    char *haddrp;
    if (argc != 3) {
	fprintf(stderr, "usage: %s <port> <SecretKey>\n", argv[0]);
	exit(0);
    }
    port = atoi(argv[1]);

    listenfd = Open_listenfd(port);
    while (1) {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

	/* determine the domain name and IP address of the client */
	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
			   sizeof(clientaddr.sin_addr.s_addr), AF_INET);
	haddrp = inet_ntoa(clientaddr.sin_addr);
	printf("server connected to %s (%s)\n", hp->h_name, haddrp);

	echo(connfd);
	Close(connfd);
    }
    exit(0);
}