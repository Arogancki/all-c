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
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUF_SIZE 8150

int flagexit = 0;

void C_reaction(int signal)
{
	flagexit = 1;
}

int main(int argc, char **argv)
{

	struct sigaction new_action;
	new_action.sa_handler = C_reaction;
	sigset_t dla_C;
	sigemptyset(&dla_C);
	new_action.sa_mask = dla_C;
	new_action.sa_flags = 0;
	sigaction(SIGINT, &new_action, NULL);

	int aflag = 0, pflag = 0, nflag = 0, znak;
	char *port = NULL, *addres_ip = NULL, *name = NULL;

	while ((znak = getopt(argc, argv, "a:p:n:")) != -1)
	{
		switch (znak)
		{
		case 'a': aflag = 1; addres_ip = optarg; break;
		case 'p': pflag = 1; port = optarg; break;
		case 'n': nflag = 1; name = optarg; break;
		case '?':
			printf("Unknovn option\n");
			return 1;
		default: abort();
		}
	}

	if (!aflag || !pflag || !nflag || (strlen(name)>12) ||
		strlen(port) != 4 || ((strlen(port)>3) && !isdigit(port[0]) && !isdigit(port[1]) && !isdigit(port[2]) && !isdigit(port[3])))
	{
		printf("Missing, or invaild addres_ip, port or name\n");
		return(1);
	}

	int deskryptor = socket(AF_INET, SOCK_STREAM, 0); // tworzymy socket avp4
	if (deskryptor == -1) {
		printf("Przykro mi %s, nie da sie - socket\n", name);
		return 1;
	}

	struct hostent *hn = gethostbyname(addres_ip); // zwraca hostnet
	struct sockaddr_in sa; // socekt adres

	sa.sin_family = AF_INET; //avpt4
	memcpy(&sa.sin_addr.s_addr, hn->h_addr, hn->h_length); // kopiujemy obszary pamieci
	sa.sin_port = htons(atoi(port));

	int i = 0;
	for (i = 0; i<30; i++)
		printf("\n");

	int yflag, wflag, zflag;
	char wwwww, **klienci, fmess[BUF_SIZE + 50] = "n";
	strcat(fmess, name);
	if (connect(deskryptor, (struct sockaddr*)&sa, sizeof(sa)) != -1)
	{
		if (write(deskryptor, fmess, strlen(fmess)) > 0)
		{
                              memset(fmess, 0, sizeof(fmess));
      if (read(deskryptor, fmess, BUF_SIZE)>0)
			printf("Polaczono\n");
			else
	{
		C_reaction(0); printf("Nie udalo sie polaczyc z serwerem\n");
	}
		}
		else
	{
		C_reaction(0); printf("Nie udalo sie polaczyc z serwerem\n");
	}
	}
	else
	{
		C_reaction(0); printf("Nie udalo sie polaczyc z serwerem\n");
	}

	while (!flagexit)
	{
		yflag = 0; wflag = 0; pflag = 0, zflag = 0;
		wwwww = 0;
		memset(fmess, 0, sizeof(fmess));

		printf("_______________________________________________\n");
		printf("Witaj %s na %s w %s\nWybierz:\nP: Pokaz aktualnie podlaczonych klientow\nW: Wyslanie wiadomosci do wybranego uzytkownika\nY: wYswietl otrzymane od klientow komunikaty\nZ: Zamknij program\n", name, addres_ip, port);


		scanf("%c", &wwwww);
		getchar();

		for (i = 0; i<30; i++)
			printf("\n");

		switch (wwwww)
		{
		case 'P':
		case 'p': pflag = 1; break;
		case 'Y':
		case 'y': yflag = 1; break;
		case 'w':
		case 'W': wflag = 1; break;
		case 'z':
		case 'Z': C_reaction(0); zflag = 1; break;
		default:  printf("Nie rozumiem :(");  break;
		}

		printf("\n");

		if (zflag)
		{
			strcpy(fmess, "z");
			strcat(fmess, name);
				if (write(deskryptor, fmess, strlen(fmess)) > 0)
				{
					zflag = 0;
				}
				else
				    {
                    flagexit=1; printf("Serwer nie odpowiada\n");
                          }
		}

		if (pflag||wflag)
		{
			strcpy(fmess, "p");
			if (write(deskryptor, fmess, strlen(fmess)) > 0)
			{
				if (deskryptor > 0)
				{
					memset(fmess, 0, sizeof(fmess));
					read(deskryptor, fmess, BUF_SIZE);
					printf("Dostepni klienci:\n%s\n", fmess);
				}
			}
			else
			{
				C_reaction(0); printf("Rozlaczono z serwerem\n");
			}

		}

		if (wflag)
		{
			//W: Wyslanie wiadomosci do wybranego uzytkownika  
			printf("\nPodaj nazwe uzytkownika\n");
			// printf("no wiec %s\n",mess3);
			char guy[12] = "";
			scanf("%s", &guy);
			getchar();
			printf("\nPodaj pusta linie aby zakonczyc\n");
			printf("Wiadomosc: \n");
			char mess[BUF_SIZE] = "",mess8[BUF_SIZE] = "";
			do
			{
                  memset(mess, 0, sizeof(mess));
                       fgets(mess,BUF_SIZE,stdin);
                       strcat(mess8,"\t");
                       strcat(mess8,mess); 
                       //printf("\n\nW%sW\n\n",mess);
            }while(strcmp(mess,"\n")!=0);
            memset(mess, 0, sizeof(mess));
            	strcpy(mess, mess8);
			if ((strlen(guy) <= 12))
			{
				// wysylanie od name do guy mess
				memset(fmess, 0, sizeof(fmess));
				strcpy(fmess, "w");
				strcat(fmess, guy);
				strcat(fmess, " ");
				strcat(fmess, name);
				strcat(fmess, ":\n");
				strcat(fmess, mess);

				// wyslanie
					if(! (write(deskryptor, fmess, strlen(fmess)) > 0 ) )
				    {
                    flagexit=1; 
                    printf("Serwer nie odpowiada\n");
                          }
                          else
                          {
                              	memset(fmess, 0, sizeof(fmess));
					read(deskryptor, fmess, BUF_SIZE);
					if(strcmp(fmess,"0")==0)
                                            printf("Wiadomosc wyslano\n");
                                            else
                                             printf("Wiadomosc nie wyslana\n");
                              }
                          
                    
        }
			else
				printf("Uzytkownik niedostepny\n");
		}

		if (yflag)
		{
			strcpy(fmess, "y");
			strcat(fmess, name);
			if (write(deskryptor, fmess, strlen(fmess)) > 0)
			{
				memset(fmess, 0, sizeof(fmess));
					read(deskryptor, fmess, BUF_SIZE);
					printf("Wiadomosci:\n%s", fmess);
			}
			else
			{
				C_reaction(0); printf("Rozlaczono z serwerem\n");
			}

		}


	}

	close(deskryptor);
	printf("Do zobaczenia %s :)\n", name);
	return 0;
}

