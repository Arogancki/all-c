//SO2 IS1 211A LAB08
//Artur Ziemba
//aziemba@wi.zut.edu.pl

//#define _XOPEN_SOURCE // co to ?!?!?!?
#define BUF_SIZE 8192

#include <stdio.h>
#include <stdlib.h>
//#include <pwd.h>
//#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <crypt.h>
//#include <dirent.h>
//#include <linux/fs.h>
#include <string.h>
#include <signal.h>
//#include <netinet/in.h>
//#include <netdb.h>
//#include <sys/socket.h>
//#include <ctype.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>


// link with -lcrypt -lrt -pthreat

int rozmiar_dla_watku=0;
int sprawdzono=0;
int flagaexit=0;
int rozmiar=0;
char *path=NULL;
char password[BUF_SIZE]="";
int algorytm= 6; 
char salt[11]="";
char hasloWY[BUF_SIZE]="";
int flagaZEROW=0;
int liczba=0;

char *hashing(char *password4,char *salt27,int type)
{
	//printf("\nFUNKCJAP:'%s' S:'%s'\nT:'%d'\n",password4,salt27,type);
	//printf("p==%s\n",password);
	char salt4[14]="";
	sprintf(salt4, "$%d$", type);
	strcat(salt4,salt27);
	//printf("s==%s\n",salt);
	//printf("\nSN:%s\n",salt4);
	//printf("HAS: '%s'\n",crypt(password4,salt4));
	return(crypt(password4,salt4));
}

void* WATEK(void *arg) 
{
	int koniec = *((int *)arg);
	//printf("Ja %d mam %d\n",getpid(), rozmiar_dla_watku);
	int start=koniec-rozmiar_dla_watku-1;
	char buffer[BUF_SIZE]="";
	int mojplik=open(path,O_RDONLY);;
	
	//printf("Watek: s: %d k: %d\n",start,koniec);
	
	lseek( mojplik, start-1, SEEK_CUR ); // przesunięcie wskaźnika

	read(mojplik,buffer,1);
	
	if (start!=0)
	{
	// cofamy sie do poprzedniego entera
	while (buffer[0] != '\n')
	{
		lseek( mojplik, (-2), SEEK_CUR );
		memset(buffer, 0, sizeof(buffer));
		read(mojplik,buffer,1);
		//printf("s: %c\n",buffer[0]);
		start--;
	}
	start++;
	}
	
	//int is=0;
	while ( (!flagaexit) && (start<=koniec) /*&& (is<1)*/ )
	{
	//is++;
	//printf("s: %d k: %d\n",start,koniec);
		//znalezeinie ostatniego entera
		int enter=start+1;
		lseek( mojplik, enter, SEEK_SET ); // przesunięcie wskaźnika
		while (buffer[0] != '\n')
		{
			memset(buffer, 0, sizeof(buffer));
			read(mojplik,buffer,1);
			enter++;
			//printf("k: %c\n",buffer[0]);
		}
		lseek( mojplik, start, SEEK_SET );
		read(mojplik,buffer,enter-start-2); 
		
		// haslo w bufferze
		//printf("%d/t/tB%sB\n",*((int *)arg),buffer);
		
		//printf("Q %s Q,%s,%d\n",buffer,salt,algorytm);
		
		//printf("hash w b: '%s'\nPass w w: '%s'\n",hashing(buffer,salt,algorytm),password);
		
		if (0==strcmp(hashing(buffer,salt,algorytm),password) && (0!=strcmp(buffer,"\n")) )
		{
			if (!flagaZEROW)
			{
				flagaexit = 1;
				strcpy(hasloWY,buffer);
			}
		}
		
		sprawdzono=sprawdzono+enter-start-2;
		start=enter;
	}
	// szukamy co enter do aktualny== koniec, plusuje co znak sprawdzono

	close(mojplik);
		
		//printf("%d.koniec watku %d czy znalazlem %d\n",++liczba,getppid(),znaleziono);
	
}
/*
void C_reaction(int signal)
{
	// czyszczenie wszystkiego 
	flagaexit = 1;
	printf("dostalem sygnal\n");
}
*/
int main(int argc, char **argv)
{
/*
	struct sigaction new_action;
	new_action.sa_handler = C_reaction;
	sigset_t dla_C;
	sigemptyset(&dla_C);
	new_action.sa_mask = dla_C;
	new_action.sa_flags = 0;
	sigaction(SIGINT, &new_action, NULL);
*/
	int ilosc_watkow;
	if (argc<4)
	{
		if (argc<3)
		{
		printf("Brak parametrow !!\n");
		return 1;
		}
		ilosc_watkow=0;
	}
	else
	ilosc_watkow=atoi(argv[3]);
	
	strcpy(password,argv[1]);
	path=argv[2];
	
	algorytm= atoi(&password[1]); 
	int i;
	for (i=3;i<13;i++)
		salt[i-3]=password[i];
		
	//printf("\n\n%s",salt);
	
	int maxprocesow=sysconf(_SC_NPROCESSORS_ONLN);
	
	if (ilosc_watkow>maxprocesow)
	{
		printf("Zbyt wiele watkow, zmniejszam do %d\n", maxprocesow-1);
		ilosc_watkow=maxprocesow-1;
	}
	
	//printf("1=%s\n2=%s\n3=%d\n4=%d\n",password,path,ilosc_watkow,maxprocesow);
	int plik=0;
	plik=open(path,O_RDONLY);
	if (plik==-1)
	{
		printf("Blad otwarcia pliku\n");
		return 1;
	}
	
	rozmiar = lseek( plik, 0, SEEK_END ); // przesunięcie wskaźnika
	
	if (ilosc_watkow==0)
	{
		flagaZEROW=1;
		ilosc_watkow=1;
	}
		
	close(plik);
	
	int OPTYMALNIE=0;
	double czas=0;
	struct timespec start, stop;
	do {
	struct timespec start, stop;

	rozmiar_dla_watku=(rozmiar/ilosc_watkow);
	//printf("nor: %d\n",rozmiar);
	pthread_t id[ilosc_watkow];
	int arg[ilosc_watkow];
	clock_gettime( CLOCK_REALTIME, &start);// czas start
	//printf("rozmiar dla watku %d rozmiar %d ilosc %d\n",rozmiar_dla_watku,rozmiar,ilosc_watkow);
	for (i=1;i<ilosc_watkow+1;i++)
	{
		arg[i-1] = (rozmiar_dla_watku*i)+i;
		int rr=pthread_create(&id[i-1], NULL, WATEK, &arg[i-1]);
		//printf("W.%d to %d ssss:%d   kkkk:%d \n",i,rr,arg[i-1]-rozmiar_dla_watku,arg[i-1]);
		//rozmiar_dla_watku=rozmiar_dla_watku+rozmiar_dla_watku;
		//printf("%d.koniec %d\n",i,arg);
	}

	int tt=sprawdzono;
	while ((!flagaexit)&&(sprawdzono!=rozmiar))
		{
			if (tt!=sprawdzono)
			{
				tt=sprawdzono;
				if(flagaZEROW)
				{
					if (sprawdzono>10000)
					{
						flagaexit=1;
						//for (i=0;i<ilosc_watkow;i++)
							//pthread_cancel(id[i]);
					}
				}
				else
				{
					system("clear");
					printf("Sprawdzilem juz %d%%\n(%d z %d)\n", ((sprawdzono * 100)) / rozmiar, sprawdzono, rozmiar);
				}
			}
		};

		clock_gettime( CLOCK_REALTIME, &stop);
		
		if (!flagaZEROW)
		{
			if (0!=strcmp("",hasloWY))
			{
				system("clear");
				printf("Udalo sie! Haslo to: '%s'\n",hasloWY);
			}
			else
			{
			system("clear");
			printf("Nie udalo sie odnalesc hasla!\n");
		}		}
		else
		{
			double accum=((double)(stop.tv_sec - start.tv_sec ))+((double)(stop.tv_nsec-start.tv_nsec))/1000000000;
			//printf("%d.Czas %f\n",ilosc_watkow, accum);
			if (accum<czas || czas==0 )
			{
				czas=accum;
				OPTYMALNIE=ilosc_watkow;
			};
			system("clear");
			
			printf("Szukam optymalnej liczby watkow - %d%%\n",((100*ilosc_watkow)-ilosc_watkow)/maxprocesow);
		}
			
		if (ilosc_watkow>maxprocesow)
			flagaZEROW=0;

		sprawdzono=0;
		flagaexit=0;
		ilosc_watkow++;
		liczba=0;

	}while (flagaZEROW==1);
	
	if (ilosc_watkow>maxprocesow)
	{
		//system("clear");
		printf("Gotowe!\nNajbardziej optymalne bedzie %d watkow.\n",OPTYMALNIE);
	}
	
	//for (i=0;i<ilosc_watkow;i++)
       	//	pthread_kill(id[i], SIGINT);

	return 0;
}


