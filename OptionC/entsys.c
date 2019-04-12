#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>

int main()
{
	int life[2], nav[2];
	pid_t pID;
	srand(time(NULL));

	time_t timer = time(NULL);
	char * currTime = ctime(&timer);
	printf("TIMER: %s",currTime);

	//flags
	int funcLife = 1;
	int funcNav = 1;
	int funcBridge = 1;

	pipe(life); pipe(nav);


	if((pID = fork())==0)
	{
		pid_t cID;


		if((cID = fork())==0) //create life support, child 2
		{
			while(funcLife==1)
			{
				//life flags
				int funcBreath = 1;
				int funcLighting = 1;
				int funcTemps = 1;
				int wriVer;

				//close life read //close nav write
				close(life[0]);
				close(nav[1]);

				if(funcBreath==0)
				{
					char adjBreath[] = "Breathing Level ADJUSTING";
					wriVer = write(life[1],adjBreath,(strlen(adjBreath))+1);
					close(life[1]);
					sleep(5);
					funcLife = 0;
				}

				char lifeString[] = "LIFE SUPPORT WORKS!";
				wriVer = write(life[1],lifeString,(strlen(lifeString))+1);
				//printf("\nChild 2 is functional :%d: cID=%d",wri,cID);
				close(life[1]);
				funcBreath = 0;
				sleep(5);
			}
		}
		else if(cID>0) //create navigation, child 1
		{
			while(funcNav==1)
			{
				char navString[] = "NAVIGATION IS OPERATIONAL!";
				close(nav[0]);
				close(life[1]);
				write(nav[1],navString,(strlen(navString)+1));
				printf("\nChild 1 is functional :: cID=%d",cID);
				close(nav[1]);
				//sleep(5);
				funcNav = 0;
			}
		}
		else
			printf("\nCHILD FORK ERROR :: GET DATA's HELP\n");

	}
	else if(pID>0) //Start of the bridge
	{
		//sleep(15);
		//wait(NULL);
		int ret;
		char buffer[100];

		while(funcBridge==1)
		{
			//close(life[1]);
			ret = read(life[0],buffer,sizeof(buffer));
			while(ret != 0)
			{
				printf("%s",buffer);
				ret = read(life[0],buffer,sizeof(buffer));
			}
			//close(life[0]);

//			close(nav[1]);
//			ret = read(nav[0],buffer,sizeof(buffer));
//				printf("%s",buffer);
//				close(life[0]);

/*			close(life[1]); close(nav[1]);
			char buffer[100];
			ret = read(life[0],buffer,100);
			printf("\nLife Support Stats: %s%d",buffer,ret);
			read(nav[0],buffer,sizeof(buffer));
			printf("\nNavigation Stats: %s\n",buffer);
			close(life[0]); close(nav[0]);
*/
			if(ret==0)
				funcBridge = 0;
		}
	}

	printf("\nMain command :: pID=%d\n",pID);
	return 0;
}
