//SO2 IS1 211A LAB06
//Artur Ziemba
//aziemba@wi.zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <linux/fs.h>
#include <string.h>
#include <signal.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <ctype.h>
#include <pthread.h>

#define BUF_SIZE 8192
#define MAX_USERS 20

int flagaexit = 0;

char ARCHIVE[MAX_USERS][2][BUF_SIZE] = { { { 0 } } };


void* WATEK(void *para) {
	int nowegniazdo = *((int *)para);
	int nflag, zflag, yflag, wflag, pflag, i;
	char mess[BUF_SIZE]="",NAMEUSER[13]="";
	int flagamoja = 0;
	while (!flagaexit && !flagamoja)
	{
		memset(mess, 0, sizeof(mess));
		nflag = 0; zflag = 0; yflag = 0; wflag = 0; pflag = 0;

		// printf("zaczynam czekac !!!\n");
		if (read(nowegniazdo, mess, BUF_SIZE))
		{
			//printf("zaczynam czekac 5\n");
			printf("%s\n", mess);
			//printf("to %c\n", mess[0]);
			switch (mess[0])
			{
			case 'y': yflag = 1; break;
			case 'w': wflag = 1; break;
			case 'n': nflag = 1; break;
			case 'z': zflag = 1; break;
			case 'p': pflag = 1; break;
			}

			if (nflag)
			{
				for (i = 0; i < MAX_USERS; i++)
					if (strcmp(ARCHIVE[i][0], "") == 0)
					{//printf("Jestes nr %d",i);
						{
							strcpy(ARCHIVE[i][0], mess + 1);
							memset(ARCHIVE[i][1], 0, sizeof(ARCHIVE[i][1]));
							
								if (write(nowegniazdo, ARCHIVE[i][0], strlen(ARCHIVE[i][0])) > 0)
			                	{
		                       			// printf("wyslano userkow\n");
		                   		}
							
						}
						//  printf("imie: %s ",ARCHIVE[i][0]);
						strcpy(NAMEUSER,ARCHIVE[i][0]);
						break;
					}
			}

			if (pflag)
			{
				// printf("darek otworz\n");
				char users[BUF_SIZE] = "";
				for (i = 0; i < MAX_USERS; i++)
					if (ARCHIVE[i][0][0] != '\0')
					{
						strcat(users, ARCHIVE[i][0]);
						strcat(users, " ");
					}
				//printf("userzy %s\n",users);
				if (write(nowegniazdo, users, strlen(users)) > 0)
				{
					// printf("wyslano userkow\n");
				}


			}

			if (yflag)
			{
				//printf("wyslanie historie\n");
				for (i = 0; i < MAX_USERS; i++)
					if (strcmp(ARCHIVE[i][0], mess + 1) == 0)
					{
						// printf("mam cie %s\n",ARCHIVE[i][0]);
						if (strcmp(ARCHIVE[i][1], "") == 0)
						{
							if (write(nowegniazdo, "Brak nowych wiadomosci", strlen("Brak nowych wiadomosci")) > 0)
							{
								printf("wyslano histori-brake\n");
							}
						}
						else
							if (write(nowegniazdo, ARCHIVE[i][1], strlen(ARCHIVE[i][1])) > 0)
							{
								printf("wyslano historie\n");
								memset(ARCHIVE[i][1], 0, sizeof(ARCHIVE[i][1]));
							}
						break;
					}
			}

			if (wflag)
			{
				printf("start:'%s':stop", mess);
				//mess=W"odbiorca" "nadawca" "wiadomosc"\0
				char odbiorca[12] = "";
				for (i = 1; i < 13; i++)
					if (mess[i] != ' ')
						odbiorca[i - 1] = mess[i];
					else
						break;
				int iii = i+1;
				int blad=1;
				for (i = 0; i < MAX_USERS; i++)
					if (strcmp(ARCHIVE[i][0], odbiorca) == 0)
					{
                                              blad=0;
						strcat(ARCHIVE[i][1], (mess + iii));
						break;
					}
					
					if (blad)
						write(nowegniazdo, "1222d", strlen("1222d"));
						else
						write(nowegniazdo, "0", strlen("0"));
				printf("start:'W%sW'&'O%sO':stop", mess+iii,odbiorca);
			}
		}
		else
		{
			printf("Nie udalo sie odebrac- read\n");
			zflag=1;
		}
		
		if (zflag || flagaexit || flagamoja)
			{
				for (i = 0; i < MAX_USERS; i++)
					if (strcmp(ARCHIVE[i][0], NAMEUSER) == 0)
					{
						memset(ARCHIVE[i][0], 0, sizeof(ARCHIVE[i][0]));
						memset(ARCHIVE[i][1], 0, sizeof(ARCHIVE[i][1]));
						ARCHIVE[i][0][0] = '\0';
						flagamoja = 1;
						break;
					}
			}
		
	}
	close(nowegniazdo);
};

void C_reaction(int signal)
{
	// czyszczenie wszystkiego 
	flagaexit = 1;
}

int isRunning(char *name, int killflag) {
	int yyy = 0;
	name = name + 2;
	char wsk[BUF_SIZE] = "/proc";
	char temp[BUF_SIZE] = "";
	char tempname[BUF_SIZE] = "";
	DIR *folder;
	folder = opendir(wsk); // otiweramy /proc

	int i;
	for (i = 2; i<strlen(name); i++)
		tempname[i - 2] = name[i];

	if (folder != NULL) {
		struct dirent *infoFolder;
		while (infoFolder = readdir(folder)) 
		{
			if (strspn(infoFolder->d_name, "0123456789") == strlen(infoFolder->d_name)) {

				strcat(wsk, "/");
				strcat(wsk, infoFolder->d_name);
				char bufer[BUF_SIZE] = "";

				DIR *subFolder;

				subFolder = opendir(wsk); // otiweramy /name

				if (subFolder != NULL) {

					struct dirent *subInfoFolder;

					while (subInfoFolder = readdir(subFolder)) {
						if (strcmp(subInfoFolder->d_name, "exe") == 0) {
							strcat(wsk, "/");
							strcat(wsk, subInfoFolder->d_name);
							readlink(wsk, bufer, BUF_SIZE - 1);
							if (strstr(bufer, name) != NULL && (getpid()!=atoi(infoFolder->d_name) )) {
									yyy++;
									if (killflag) kill(atoi(infoFolder->d_name), SIGINT);
							}
						}
					}
				}
				wsk[0] = '\0';
				strcat(wsk, "/proc");
			}
		};
	}
	return (yyy);
}

int main(int argc, char **argv)
{
	int pid = getpid(), child_pid = 1;

	if ((child_pid = fork()) != 0)
	{
		return(0);
	}

	//ODKOMETOWAC
	
	setsid();
	chdir ("/");

	int jj;
	//for (jj = 0; jj < NR_OPEN; jj++)
	close(0);
	close(1);
	close(2);
	//fclose(stdout);
	//fclose(stderr);

	open("/dev/null", O_RDWR);
	dup (0);
	dup (1);
 

	// od teraz JESTEM DEMONEM

	struct sigaction new_action;
	new_action.sa_handler = C_reaction;
	sigset_t dla_C;
	sigemptyset(&dla_C);
	new_action.sa_mask = dla_C;
	new_action.sa_flags = 0;
	sigaction(SIGINT, &new_action, NULL);

	int qflag = 0, pflag = 0, znak;
	char *port = NULL;

	while ((znak = getopt(argc, argv, "qp:")) != -1)
	{
		switch (znak)
		{
		case 'q': qflag = 1; break;
		case 'p': pflag = 1; port = optarg; break;
		case '?':
			printf("Unknovn option\n");
			return 1;
		defalut: abort();
		}
	}

	if (!qflag && !pflag)
	{
		printf("Missing option p or q\n");
		return(1);
	}

	int ilosc = isRunning(argv[0], 0);
	printf("ilosc juz otwartych %d\n",ilosc);
	if (qflag)
	{
		if (ilosc>1)
		{
			isRunning(argv[0], 1);
			printf("Zamknieto serwer");
			return 0;
		}
		printf("Brak otwartych serwerow\n");
		return 2;
	}

	if (ilosc>1)
	{
		printf("Serwer jest juz uruchomiony\n");
		return 1;
	}

	if (strlen(port) != 4 || ((strlen(port)>3) && !isdigit(port[0]) && !isdigit(port[1]) && !isdigit(port[2]) && !isdigit(port[3])))
	{
		printf("Invaild port number - should be 16 bit digit \n");
		return(1);
	}

	int deskryptor = socket(AF_INET, SOCK_STREAM, 0); // tworzymy socket avp4
	if (deskryptor == -1) {
		printf("Przykro mi, nie da sie - socket\n");
		return 1;
	}

	struct sockaddr_in sa;
	sa.sin_family = AF_INET; // avp4
	sa.sin_addr.s_addr = INADDR_ANY; //poolaczenie na kazdym interfejscie
	sa.sin_port = htons(atoi(port));

	if (bind(deskryptor, (struct sockaddr*)&sa, sizeof(sa)) < 0) { // dawaj adres socketa
		printf("Przykro mi, nie da sie - bind\n");
		return 1;
	}

	struct sockaddr_in nowy_adres;

	if (listen(deskryptor, 100) == -1) {
		printf("Przykro mi, nie da sie - listen\n");
		return 1;
	}

	int i = 0, dlugosc_adresu;
	for (i = 0; i<MAX_USERS; i++)
		memset(ARCHIVE[i][0], 0, sizeof(ARCHIVE[i][0]));
    int ilosc_watkow=0;
    pthread_t id[MAX_USERS];
	while (!flagaexit)
	{
		printf("czekam na usera\n");
		int nowegniazdo;
		nowegniazdo = accept(deskryptor, (struct sockaddr*)&nowy_adres, &dlugosc_adresu); //Wyci¹ga pierwsze ¿¹danie po³¹czenia z kolejki
		if (nowegniazdo > 0 && (ilosc_watkow<MAX_USERS)) {
    
			int *arg = malloc(sizeof(*arg));
			*arg = nowegniazdo;
			if (0 == pthread_create(&id[ilosc_watkow], NULL, WATEK, arg))
				free(arg);
			printf("stworzylem konto\n");
			ilosc_watkow++;
		}
		else
			printf("no sie nie da - accept\n");

	}
    for (i=0;i<ilosc_watkow;i++)
        pthread_kill(id[i], SIGINT);
    
	close(deskryptor);
	return 0;
}



//n nowy z zamkniecie w wiadomosc y podaj wiadomosci p pokaz uzytjkowoniko


