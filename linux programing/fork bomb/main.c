//SO2 IS1 211A LAB03
//Artur Ziemba
//aziemba@wi.zut.edu.pl

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BUFSIZE 4096

int main(int argc, char **argv)
{

if (argv[2]!=NULL)
{
	if ((strlen(argv[2]))>BUFSIZE)
		{
			printf("Osiagnieto limit przekazywanych pidow\n");
			exit(1);	
		}
}

/*


*/

if (argc<2)
{
	printf("Brak parametru n\n");
	exit(1);
}

char pid[BUFSIZE]; // dlaczego to dziala ??
snprintf(pid, sizeof(pid), "%d", getpid()); // pid to string 

// przygotowanie argumentow dla excel lub do zwrotu
char arg[BUFSIZE]= ""; 
if (argc<3)
	{
		strcat(arg, pid);
	}
else
	{
		strcat(arg, argv[2]);
		strcat(arg, " ");
		strcat(arg, pid);
	}
// koniec

int n=atoi(argv[1]);
if (n>0)
{
   	pid_t child_pid1;
	pid_t child_pid2;

	char newn[BUFSIZE]; 
	snprintf(newn, sizeof(newn), "%d", n-1); // pid to string 

	if ((child_pid1=fork()) < 0)
	{
		printf("Fork error/n");
		exit(1);
	}
	else
		if (child_pid1==0)
		{
			execl(argv[0], argv[0], &newn, &arg, NULL);
			exit(1); // fail
		}

	if ((child_pid2=fork()) < 0)
	{
		printf("Fork error/n");
		exit(1);
	}
	else
		if (child_pid2==0)
		{
			execl(argv[0], argv[0], &newn, &arg, NULL);
			exit(1); // fail
		}


	int status1;
	if (waitpid(child_pid1,&status1,0) != child_pid1 )
		status1=-1;

	int status2;
	if (waitpid(child_pid2,&status2,0) != child_pid2 )
		status2=-1;
}

// drukowanie pidow
//printf("%d: moj koniec = %d %s\n", getpid(),n,arg);
printf("%s\n",arg);

exit(0);
}
