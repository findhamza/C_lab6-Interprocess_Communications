#include <stdio.h>
#include <stdlib.h>
#include <randapi.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define buff 250

int main()
{
	char bridgeBuffer[buff];
	time_t now;

	time(&now);
	struct tm * timeInfo = localtime(&now);
	printf("\nBridge Initiated At %s", asctime(timeInfo));

	char *commPipeLife = "/tmp/pLife";
	int commStatusLife = mkfifo( commPipeLife, 0666);
	int pLife = open( commPipeLife, O_RDONLY);

	char *commPipeNav = "/tmp/pNav";
	int commStatusNav = mkfifo( commPipeNav, 0666);
	int pNav = open( commPipeNav, O_RDONLY);

	while(1)
	{
		time(&now);
		timeInfo = localtime(&now);
		printf("\nBridge Recieved New Message At %s",asctime(timeInfo));

		read(pLife,bridgeBuffer,buff);
		printf("%s",bridgeBuffer);

		read(pNav,bridgeBuffer,buff);
		printf("%s",bridgeBuffer);

		sleep(30);
	}

}
