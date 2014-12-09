#include "csapp.h"


int main(int argc, char** argv)
{
	if(argc < 4 && argc > 5)
	{
		fprintf(stderr, "Usage: %s <MachineName> <TCPport> <SecretKey> <Filename> \n", argv[0] );
	}
	return 0;
}