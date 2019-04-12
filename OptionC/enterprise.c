#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

#define buff 250

int main()
{
	int pLife[2], pNav[2];
	pid_t pID;

	pipe(pLife); pipe(pNav);

	if((pID = fork())==0)
	{
		pid_t cID;

		if((cID = fork())==0) //Life Support Systems
		{
			close(pLife[0]);
			close(pNav[1]);

			printf("\nBegining Life System Adjustments\n");

			//Beginning Gas Level Adjustments
			sleep(2);
			//Beginning Light Level Adjustments
			sleep(2);
			//Beginning Temp Level Adjustments
			sleep(2);

			char lifeBuffer[buff];
			sprintf(lifeBuffer,"\n\tGas Levels Adjusted in %dsecs\n\tLight Levels Adjusted in %dsecs\n\tTemp Levels Adjusted in %dsecs\n",2,2,2);

			write(pLife[1],lifeBuffer,buff+1);
			close(pLife[1]);
		}

		else if(cID>0)
		{
			close(pNav[0]);
			close(pLife[1]);

			printf("\nBegining Navigation Adjustments\n");

			//Beginning Nav Adjustments
			sleep(2);

			char navBuffer[buff];
			sprintf(navBuffer,"\n\tNavigation Adjusted in %dsec\n",2);

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
