#include "../include/csapp.h"

struct MC_NODE * MC_HEAD;

int delRequest(rio_t* rio,int connfd)
{
	return MC_SUCC;
}

int listRequest(rio_t* rio,int connfd)
{

	return MC_SUCC;
}


int getRequest(rio_t* rio,int connfd)
{

	return MC_SUCC;
}


int putRequest(rio_t* rio,int connfd)
{
	char buf[MC_NUM_SIZE];
	unsigned int result = MC_SUCC;
	unsigned int netByte;
	unsigned int dataLen;

	char uFiledata[MC_MAX_FILE_SIZE];
	char uFilename[MC_MAX_FILE_NAME_SIZE];

	Rio_readnb(rio, uFilename, MC_MAX_FILE_NAME_SIZE);

	printf("Filename = %s\n",uFilename );
	Rio_readnb(rio, buf, MC_NUM_SIZE);

	memcpy(&netByte,buf,MC_NUM_SIZE);

	dataLen = ntohl(netByte);

	Rio_readnb(rio, uFiledata, dataLen);

	struct MC_NODE * currNode = (struct MC_NODE *)Malloc(sizeof(struct MC_NODE));

	currNode->next = MC_HEAD;

	currNode->datalen = datalen;

	memcpy(currNode->Filedata,uFiledata,dataLen);

	memcpy(currNode->Filename,uFilename,MC_MAX_FILE_NAME_SIZE);
	
	MC_HEAD = currNode;

    netByte = htonl(result);
    memcpy(buf,&netByte,sizeof(int));
    Rio_writen(connfd, buf, MC_NUM_SIZE);
	return result;
}

void printRequestType(int reqType){
	switch(reqType){
		case MC_PUT:
			printf("Request Type = put\n");
			break;
		case MC_GET:
			printf("Request Type = get\n");
			break;
		case MC_DEL:
			printf("Request Type = del\n");
			break;
		case MC_LIST:
			printf("Request Type = list\n");
			printf("Filename = NONE\n");
			break;
		default:
			break;
	}
}

//valid access return 0, otherwise no access
int isValidAccess(unsigned int userKey, unsigned int sysKey){

	return userKey - sysKey;
}

void echo(int connfd,unsigned int secretKey){
    size_t n;
 	unsigned int max_size = MC_NUM_SIZE *2;
    char buf[max_size]; 
    rio_t rio;

    

    unsigned int netByte,result = 0;

    Rio_readinitb(&rio, connfd);
#ifndef MC_DEBUG
    fprintf(stderr,"Server Started reading\n");
#endif

    unsigned int recvLen = MC_NUM_SIZE * 2;


    //Recieve Access Key and Request type 8 byte.
    if(n = Rio_readnb(&rio, buf, recvLen) == recvLen){//line:netp:echo:eof
#ifndef MC_DEBUG
	fprintf(stderr,"server received %d bytes\n", (int)n);
#endif


	char* pBuf = buf;

	memcpy(&netByte,pBuf,MC_NUM_SIZE);
	pBuf += MC_NUM_SIZE;
	unsigned int userKey = ntohl(netByte);
	memcpy(&netByte,pBuf,MC_NUM_SIZE);
	unsigned int requestType = ntohl(netByte);

	printf("Secret Key = %u\n", userKey);
	printRequestType(requestType);



	if(!isValidAccess(userKey,secretKey))
	{
		switch(requestType){
		case MC_PUT:
			result = putRequest(&rio,connfd);
			break;
		case MC_GET:
			result = getRequest(&rio,connfd);
			break;
		case MC_DEL:
			result = delRequest(&rio,connfd);
			break;
		case MC_LIST:
			result = listRequest(&rio,connfd);
			break;
		default:
			result = MC_ERR;
			break;
		}
	}
	else
	{
		result = MC_ERR;
	}


	switch(result){
		case MC_SUCC:
			printf("Operation Status = success\n");
			break;
		default:
			printf("Operation Status = error\n");
			break;
	}

	
	}
}


int main(int argc, char **argv) 
{
	MC_HEAD = NULL;
    int listenfd, connfd, port, clientlen;
    unsigned int secretKey;
    struct sockaddr_in clientaddr;
    struct hostent *hp;
    char *haddrp;
    if (argc != 3) {
	fprintf(stderr, "usage: %s <port> <SecretKey>\n", argv[0]);
	exit(0);
    }
    port = atoi(argv[1]);
    secretKey = atoi(argv[2]);

    listenfd = Open_listenfd(port);
    while (1) {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

	/* determine the domain name and IP address of the client */
	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
			   sizeof(clientaddr.sin_addr.s_addr), AF_INET);
	haddrp = inet_ntoa(clientaddr.sin_addr);
#ifdef MC_DEBUG
	printf("server connected to %s (%s)\n", hp->h_name, haddrp);
#endif
	echo(connfd,secretKey);
	printf("--------------------------\n");
	Close(connfd);
    }
    exit(0);
}