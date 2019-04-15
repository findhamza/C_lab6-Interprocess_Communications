#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
#include <randapi.h>

#define buff 250
#define NUMITERATIONS 1234567L

int main()
{
	int pLife[2], pNav[2];
	pid_t pID;

	pipe(pLife); pipe(pNav);

	seedRandGenerator();

	if((pID = fork())==0)
	{
		pid_t cID;

		if((cID = fork())==0) //Life Support Systems
		{
			close(pLife[0]);
			close(pNav[1]);

			time_t now;
			time(&now);
			struct tm * timeInfo = localtime(&now);

			printf("\nBegining Life System Adjustments At %s\n",asctime(timeInfo));

			//Beginning Gas Level Adjustments
			float gasTime = 0;
			for(long k=0; k<NUMITERATIONS; k++)
				gasTime += getRandExponential()*5.0;
			gasTime = gasTime / (float)NUMITERATIONS;

			sleep(gasTime);
			//Beginning Light Level Adjustments
			float lightTime = 0;
			for(long k=0; k<NUMITERATIONS; k++)
				lightTime += getRandExponential()*4.0;
			lightTime = lightTime / (float)NUMITERATIONS;

			sleep(lightTime);
			//Beginning Temp Level Adjustments
			float tempTime = 0;
			for(long k=0; k<NUMITERATIONS; k++)
				tempTime += getRandExponential()*4.0;
			tempTime = tempTime / (float)NUMITERATIONS;

			sleep(tempTime);

			char lifeBuffer[buff];
			sprintf(lifeBuffer,"\n\tGas Levels Adjusted in %f seconds\n\tLight Levels Adjusted in %f seconds\n\tTemp Levels Adjusted in %f seconds\n",gasTime,lightTime,tempTime);

			write(pLife[1],lifeBuffer,buff+1);
			close(pLife[1]);
		}

		else if(cID>0)
		{
			close(pNav[0]);
			close(pLife[1]);

			time_t now;
			time(&now);
			struct tm * timeInfo = localtime(&now);

			printf("\nBegining Navigation Adjustments At %s\n",asctime(timeInfo));

			//Beginning Nav Adjustments
			int navTime = getRandInteger(6);
			sleep(navTime);

			char navBuffer[buff];
			sprintf(navBuffer,"\n\tNavigation Adjusted in %d seconds\n",navTime);

			write(pNav[1],navBuffer,buff+1);
			close(pNav[1]);
		}

		else
			printf("\nCHILD FORK ERROR(S) :: CONTACT DATA FOR SUPPORT\n");

	}

	else if(pID>0)
	{
		char bridgeBuffer[buff];


		close(pLife[1]);
		read(pLife[0],bridgeBuffer,sizeof(bridgeBuffer));

		time_t now;
		time(&now);
		struct tm * timeInfo = localtime(&now);

		printf("\nBridge Recieved Message At %s",asctime(timeInfo));
		printf("\nLife Support Adjustment Stats: \n%s",bridgeBuffer);

		close(pNav[1]);
		read(pNav[0],bridgeBuffer,sizeof(bridgeBuffer));

		printf("\nNavigation Adjustment Stats: \n%s",bridgeBuffer);

		close(pLife[0]);
		close(pNav[0]);
	}

	else
		printf("\nPARENT FORK ERROR :: CONTACT DATA FOR SUPPORT\n");

}
