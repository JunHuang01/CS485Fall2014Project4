#include "../include/csapp.h"


int main(int argc, char** argv){

	char MachineName[MC_MAX_HOST_NAME_SIZE];
	char Filename[MC_MAX_FILE_NAME_SIZE];
	unsigned int TCPport, SecretKey;
	int hostLen, fileNameLen;
	if(argc < 4 || argc > 5){
		fprintf(stderr, "Usage: %s <MachineName> <TCPport> <SecretKey> <Filename> \n", argv[0] );
		return 0;
	}
	else if (argc == 4){
		
		fileNameLen = strlen(argv[3]);
		if (fileNameLen > MC_MAX_FILE_NAME_SIZE){
			fprintf(stderr, "File name is too long, max length is %d\n",MC_MAX_FILE_NAME_SIZE);
			return 0;
		}

		strcpy(MachineName,"127.0.0.1");
		TCPport = atoi(argv[1]);
		SecretKey = atoi(argv[2]);
		strncpy(Filename,argv[3],MC_MAX_FILE_NAME_SIZE);
		Filename[fileNameLen] = '\0';
		fileNameLen++;
	}
	else if (argc == 5){
		hostLen = strlen(argv[1]);

		if (hostLen > MC_MAX_HOST_NAME_SIZE)
		{
			fprintf(stderr, "Host name is too long, max length is %d\n",MC_MAX_HOST_NAME_SIZE);
			return 0;
		}

		fileNameLen = strlen(argv[4]);

		if (fileNameLen > MC_MAX_FILE_NAME_SIZE-1){
			fprintf(stderr, "File name is too long, max length is %d\n",MC_MAX_FILE_NAME_SIZE);
			return 0;
		}

		strncpy(MachineName,argv[1],MC_MAX_HOST_NAME_SIZE);
		TCPport = atoi(argv[2]);
		SecretKey = atoi(argv[3]);
		strncpy(Filename,argv[4],MC_MAX_FILE_NAME_SIZE);
		Filename[fileNameLen] = '\0';
		fileNameLen++;
	}

	char buf[MC_MAX_FILE_SIZE];

	unsigned int datalen;

    if(datalen = Fread(&buf,1,MC_MAX_FILE_SIZE ,stdin) >= 0){
    	fprintf(stderr, "The data length is %u \n",datalen );
    	int res = mycloud_putfile(MachineName, TCPport, SecretKey, Filename, buf , datalen);
    	if (res < 0)
    		printf("Error\n");
    }

	//fprintf(stderr, "%s %u %u %s \n", MachineName, TCPport, SecretKey, Filename );

	return 0;
}