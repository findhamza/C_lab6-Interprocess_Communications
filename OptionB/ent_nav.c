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
	seedRandGenerator();
	int navTime;
	char navBuffer[buff];

	char *commPipeName = "/tmp/pNav";
	int commStatus = mkfifo( commPipeName, 0666);
	int commPipe = open( commPipeName, O_WRONLY);


	while(1)
	{
		navTime = getRandFloat()*6;

		time_t now;
		time(&now);
		struct tm * timeInfo = localtime(&now);

		sleep(navTime);

		char intro[] = "\nNavigation Adjustments Started At";
		sprintf(navBuffer,"\n%s %s \n\n\tNavigation Adjusting in %d seconds\n\n",
			intro,asctime(timeInfo),navTime);

		write(commPipe,navBuffer,buff+1);

		sleep(30);
	}

}
