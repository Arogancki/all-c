//SO2 IS1 211A LAB03
//Artur Ziemba
//aziemba@wi.zut.edu.pl

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
/*
printf("%d: moj start =", getpid());
int y;
for (y=1; y<argc; y++)
	printf(" %s ",argv[y]);
printf("\n");
*/

if (argc<2)
{
	printf("Brak parametru n\n");
	exit(1);
}

char pid[BUFSIZ]; // dlaczego to dziala ??
snprintf(pid, sizeof(pid), "%d", getpid()); // pid to string 

// przygotowanie argumentow dla excel lub do zwrotu
char arg[BUFSIZ]; 
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
    pid_t child_pid;
	char newn[BUFSIZ]; 
	snprintf(newn, sizeof(newn), "%d", n-1); // pid to string 
	int dwa;
	for (dwa=0;dwa<2;dwa++)
	if ((child_pid=fork()) < 0)
	{
		printf("Fork error/n");
		exit(1);
	}
	else
		if (child_pid==0)
		{
			execl(argv[0], argv[0], newn, arg, NULL);
			exit(1); // fail
		}
		else
		{
            int status;
			if (waitpid(child_pid,&status,0) != child_pid )
				status=-1;
		}
}

// drukowanie pidow
//printf("%d: moj koniec = %d %s\n", getpid(),n,arg);
printf("%s\n",arg);

exit(0);
}
