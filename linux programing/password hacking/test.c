//SO2 IS1 211A LAB08
//Artur Ziemba
//aziemba@wi.zut.edu.pl

//#define _XOPEN_SOURCE // co to ?!?!?!?
#define BUF_SIZE 8192

#include <stdio.h>
#include <stdlib.h>
//#include <pwd.h>
//#include <grp.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
#include <unistd.h>
#include <crypt.h>
//#include <dirent.h>
//#include <linux/fs.h>
#include <string.h>
//#include <signal.h>
//#include <netinet/in.h>
//#include <netdb.h>
//#include <sys/socket.h>
//#include <ctype.h>
//#include <pthread.h>
#include <errno.h>

// link with -lcrypt 

char *hashing(char *password4,char *salt27,int type)
{
	//printf("\nFUNKCJAP:'%s' S:'%s'\nT:'%d'\n",password4,salt27,type);
		//printf("p==%s\n",password);
		char salt4[14]="";
		sprintf(salt4, "$%d$", type);
		strcat(salt4,salt27);
		//printf("s==%s\n",salt);
		//printf("\nSN:%s\n",salt4);
		return(crypt(password4,salt4));
}

char *main(int argc, char **argv)
{
	int algorytmtype;
	if (argc<4)
	{
		if (argc<3)
		{
		printf("Brak parametrow !!\n");
		return(NULL);
		}
		algorytmtype=6;
	}
	else
		algorytmtype=atoi(argv[3]);
	
		printf("%s\n",hashing(argv[1],argv[2],algorytmtype));
	return(hashing(argv[1],argv[2],algorytmtype));
}


