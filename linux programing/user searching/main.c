//SO2 IS1 211A LAB01
//Artur Ziemba
//aziemba@wi.zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcmp
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>

int main(int argc, char **argv){

struct passwd *user;
int gflag=0, pflag=0, znak;
char *powloka=NULL;

opterr =0; // wylaczenie komunikatow

while ((znak =getopt (argc, argv, "gp:")) != -1)
{
	switch (znak)
	{
		case 'g': gflag=1; break;
		case 'p': pflag=1; gflag=1; powloka=optarg; break;
		case '?':
			if (optopt=='p')
				printf("Missing shell name\n");
			else
				printf("Unknovn option\n");
				return 1;
		defalut: abort();
	}
}

while ((user=getpwent()) != NULL)
{
	if (pflag)
	{
		char *shell=user->pw_shell;
		shell +=5;
		if ((strcmp(shell, powloka))!=0)
			continue;
	}

	printf("%s ", user->pw_name);

	if (gflag)
	{
		printf(" - grupy: ");
		int ng=0;
		getgrouplist(user->pw_name, user->pw_gid, NULL, &ng);
		gid_t *grupy=malloc(ng*sizeof(gid_t));
		getgrouplist(user->pw_name, user->pw_gid, grupy, &ng);
		int i;
		for (i=0; i<ng; i++)
		{
			printf("%s, ", (getgrgid(grupy[i]))->gr_name);
		}
		free(grupy);
	}

	printf("\n");
// getchar();
}

return 0;
}
