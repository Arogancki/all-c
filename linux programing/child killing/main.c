//SO2 IS1 211A LAB04
//Artur Ziemba
//aziemba@wi.zut.edu.pl

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFSIZE 4096

// C =  SIGINT
// Z = SIGTSTP

int flaga=1;
pid_t child_pid1=0;
pid_t child_pid2=0;

void C_reaction(int signal)
{
    flaga=0;
/*
if (child_pid1!=0)
    kill (child_pid1, SIGINT);
if (child_pid2!=0)
    kill (child_pid2, SIGINT);
*/
    //printf("Bylem tu %d\n", getpid());
}

//void Do_nothing(int signal){}

int main(int argc, char **argv)
{


struct sigaction new_action1/*, old_action*/;
new_action1.sa_handler = C_reaction;

sigset_t dla_C;
sigemptyset(&dla_C);
new_action1.sa_mask=dla_C;
new_action1.sa_flags=0;

//new_action.sa_flags = SA_RESTART;

sigaction (SIGINT, &new_action1, NULL);
//sigaction (SIGCHLD, &new_action, NULL);

/*
sigaction (SIGINT, NULL, &old_action);
if (old_action.sa_handler != SIG_IGN) // akcja ignorowanie
    sigaction (SIGINT, &new_action, NULL);
*/

sigset_t blokowane_sygnaly;
sigemptyset(&blokowane_sygnaly);
sigaddset(&blokowane_sygnaly, SIGTSTP);
sigprocmask(SIG_BLOCK, &blokowane_sygnaly, NULL);


if (argv[2]!=NULL)
{
	if ((strlen(argv[2]))>BUFSIZE)
		{
			printf("Osiagnieto limit przekazywanych pidow\n");
			exit(1);
		}
}

if (argc<2)
{
	printf("Brak parametru n\n");
	exit(1);
}

char pid[BUFSIZE];
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
	char newn[BUFSIZE];
	snprintf(newn, sizeof(newn), "%d", n-1); // pid to string

	if ((child_pid1=fork()) < 0)
	{
		printf("Fork error/n"); // za duzo procesow
		exit(1);
	}
	else
		if (child_pid1==0)
		{
               setsid();
			execl(argv[0], argv[0], &newn, &arg, NULL);
			exit(1); // fail
		}

	if ((child_pid2=fork()) < 0)
	{
		printf("Fork error/n"); // jak wyzej
		exit(1);
	}
	else
		if (child_pid2==0)
		{
                          //printf("Grupa przed - %d\n",getsid(0));
                          setsid();
                          //printf("Grupa po - %d\n",getsid(0));
			execl(argv[0], argv[0], &newn, &arg, NULL);
			exit(1); // fail
		}

	while (flaga)
	        sleep(1);

	
	if (child_pid1!=0)
	    kill (child_pid1, SIGINT);
	if (child_pid2!=0)
	    kill (child_pid2, SIGINT);


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

sigset_t zablokowane_sygnaly;
sigemptyset(&zablokowane_sygnaly);
sigpending(&zablokowane_sygnaly);
if (sigismember(&zablokowane_sygnaly, SIGTSTP)==1)
{
    printf("Wykryto probe zatrzymania sygnalem SIGTSTP\n");

	struct sigaction new_action2/*, old_action*/;

	new_action2.sa_handler = SIG_IGN;
	sigset_t dla_Z;
	sigemptyset(&dla_Z);
	new_action2.sa_mask=dla_Z;
	new_action2.sa_flags=0;

	sigaction (SIGTSTP, &new_action2, NULL);

}
sigemptyset(&zablokowane_sygnaly);
sigprocmask(SIG_UNBLOCK, &blokowane_sygnaly, NULL); 
exit(0);
}
