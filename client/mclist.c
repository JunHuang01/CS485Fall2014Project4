#include "../include/csapp.h"


int main(int argc, char** argv){

	char MachineName[MC_MAX_HOST_NAME_SIZE];
	char Filename[MC_MAX_FILE_NAME_SIZE];
	unsigned int TCPport, SecretKey;
	int hostLen, fileNameLen;
	if(argc < 3 || argc > 4){
		fprintf(stderr, "Usage: %s <MachineName> <TCPport> <SecretKey> <Filename> \n", argv[0] );
		return 0;
	}
	else if (argc == 3){
		strcpy(MachineName,"127.0.0.1");
		TCPport = atoi(argv[1]);
		SecretKey = atoi(argv[2]);
	}
	else if (argc == 4){
		hostLen = strlen(argv[1]);

		if (hostLen > MC_MAX_HOST_NAME_SIZE)
		{
			fprintf(stderr, "Host name is too long, max length is %d\n",MC_MAX_HOST_NAME_SIZE);
			return 0;
		}

		strncpy(MachineName,argv[1],MC_MAX_HOST_NAME_SIZE);
		TCPport = atoi(argv[2]);
		SecretKey = atoi(argv[3]);
	}
	unsigned int listbuflen;
	char * listbuf = (char*)Malloc(MC_MAX_FILE_NAME_SIZE*1000);//limitation that we will be accepting at most 1000 files
	int result = mycloud_listfiles(MachineName, TCPport, SecretKey, &listbuf,&listbuflen );

#ifdef MC_DEBUG
	fprintf(stderr, "The length of list is %u \n", listbuflen );
#endif
	Fwrite(listbuf,listbuflen,1,stdout);
	//fprintf(stderr, "%s %u %u %s \n", MachineName, TCPport, SecretKey, Filename );

	if (result != 0)
		printf("Error\n");
	Free(listbuf);
	return 0;
}