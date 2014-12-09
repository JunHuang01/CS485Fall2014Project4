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


	fprintf(stderr, "%s %u %u \n", MachineName, TCPport, SecretKey);

	return 0;
}