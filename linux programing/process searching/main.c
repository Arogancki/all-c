//SO2 IS1 211A LAB05
//Artur Ziemba
//aziemba@wi.zut.edu.pl

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

#define BUF_SIZE 8192

int main(int argc, char **argv)
{

int killflag=0;
if (strcmp(argv[0], "./killall")==0)
   killflag=1;

if (argv[1]==NULL)
   return(0);

int flagaenter=0;

int i;
for(i=1; i<argc; i++)
{
DIR *proc=opendir("/proc");

if (proc==NULL)
   {
               printf("Blad otwarcia /proc\n");
               return(1);
    }
    
    struct dirent *proc_dirent;
    do {
        proc_dirent=readdir(proc);
        if (proc_dirent != NULL) 
        {
              char path[BUF_SIZE]="";
              strcat(path,"/proc/" );
              strcat(path,proc_dirent->d_name );
              strcat(path,"/exe" );
              
              char buffer[BUF_SIZE]="";
              if ( readlink(path, buffer, BUF_SIZE-1) )
                 if (strstr(buffer,argv[i])!=NULL)
                 {
                    if (killflag)
                    {
                         kill(atoi(proc_dirent->d_name), SIGINT);
                    }
                    else
                    {
                        printf("%s ",proc_dirent->d_name);
                        flagaenter=1;
                    }
                 }
        }
        
    } while (proc_dirent != NULL);
    
closedir(proc);
}
if (flagaenter)
   printf("\n");
return(0);
}
