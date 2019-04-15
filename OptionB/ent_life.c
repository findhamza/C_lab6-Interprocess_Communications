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
#define NUMI 1234567L

float gre(int);

int main()
{
        seedRandGenerator();

        float gasTime;
	float lightTime;
	float tempTime;

        char lifeBuffer[buff];

	char *commPipeName = "/tmp/pLife";
	int commStatus = mkfifo( commPipeName, 0666);
	int commPipe = open( commPipeName, O_WRONLY);

	while(1)
	{

		gasTime = gre(5);
		lightTime = gre(4);
		tempTime = gre(4);

		time_t now;
                time(&now);
                struct tm * timeInfo = localtime(&now);

		sleep(gasTime);
		sleep(lightTime);
		sleep(tempTime);

		char intro[] = "\nLife Adjustments Started At";
		sprintf(lifeBuffer,"\n%s %s \n\n\tGas levels Adjusted in %f seconds\n\tLights Adjusted in %f seconds\n\tTemps Adjusted in %f seconds\n\n",
			intro,asctime(timeInfo),gasTime,lightTime,tempTime);

		write(commPipe,lifeBuffer,buff+1);

		sleep(30);
	}

}

float gre(int num)
{
	float expoNum = 0;
	for(long k=0; k<NUMI; k++)
		expoNum += getRandExponential()*num;
	return (expoNum / (float)NUMI);
}
