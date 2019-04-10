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
	pid_t pID = fork();
	srand(time(NULL));

	char buffer[100];

	pipe(life); pipe(nav);


	if(pID==0) //create navigation, child 1
	{
		pid_t cID = fork();

		if(cID==0) //create life support, child 2
		{
			char lifeString[] = "LIFE SUPPORT WORKS!";
			write(life[1],lifeString,(strlen(lifeString)+1));
			printf("\nChild 2 is functional");
			close(life[1]);
			sleep(1);
		}
		else if(cID>0)
		{
			wait(NULL);
			char navString[] = "NAVIGATION IS OPERATIONAL!";
			write(nav[1],navString,(strlen(navString)+1));
			printf("\nChild 1 is functional");
			close(nav[1]);
			sleep(1);
		}
		else
			printf("\nCHILD FORK ERROR :: GET DATA's HELP\n");
		exit(0);
	}
	else if(pID>0)
	{
		printf("HELLO WORLD");
		wait(NULL);
		read(life[0],buffer,sizeof(buffer));
		printf("\nLife Support Stats: %s",buffer);
		read(nav[0],buffer,sizeof(buffer));
		printf("\nNavigation Stats: %s",buffer);
	}

	printf("\nMain command\n");
	exit(1); return 0;
}
