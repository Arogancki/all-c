//SO2 IS1 211A LAB02
//Artur Ziemba
//aziemba@wi.zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int ( *c)();
int ( *d)();
int ( *n)();
int ( *s)();
int ( *t)();
int ( *u)();

int main(int argc, char **argv){

struct passwd *user;
int znak;

void *test = dlopen( "./limitlib.so.0.1", RTLD_LAZY);
// rozwiazwanie niezydentyfikowanych syboli w bibilotece

int cflag=0, dflag=0, nflag=0, sflag=0, tflag=0, uflag=0, anyflag=0;

//opterr=0; // czemu nie dziala :'(

if (test)
{

while ((znak =getopt (argc, argv, "acdnstu")) != -1)
{
	anyflag=1;
	switch (znak)
	{
		case 'c': cflag=1; break;
		case 'd': dflag=1; break;
		case 'n': nflag=1; break;
		case 's': sflag=1; break;
		case 't': tflag=1; break;
		case 'u': uflag=1; break;
	        case 'a': cflag=1; dflag=1; nflag=1;
			  sflag=1; tflag=1; uflag=1; break; 
		case '?':
				printf("Unknovn option\n");
				dlclose(test);
				return 1;
		defalut: abort();
	}
}

if (anyflag)
{
	int ret;


	if (cflag)
	{
		c=dlsym(test,"c");
		if (c==NULL)
			printf("Function -c cannot be loaded\n");
		else
		{
			ret=c();
			if (ret>=0)
				printf("Core file size %d\n", ret);
			else
				printf("Brak obsługi parametru -c\n");
		}
	}


	if (dflag)
	{
		d=dlsym(test,"d");
		if (d==NULL)
			printf("Function -d cannot be loaded\n");
		else
		{
			ret=d();
			if (ret>=0)
				printf("Data seg size %d\n", ret);
			else
				printf("Brak obsługi parametru -d\n");
		}
	}


	if (nflag)
	{
		n=dlsym(test,"n");
		if (n==NULL)
			printf("Function -n cannot be loaded\n");
		else
		{
			ret=n();
			if (ret>=0)
				printf("Open files %d\n", ret);
			else
				printf("Brak obsługi parametru -n\n");
		}
	}
	
	
	if (sflag)
	{
		s=dlsym(test,"s");
		if (s==NULL)
			printf("Function -s cannot be loaded\n");
		else
		{
			ret=s();
			if (ret>=0)
				printf("Stack size %d\n", s());
			else
				printf("Brak obsługi parametru -s\n");
		}
	}
	
	
	if (tflag)
	{
		t=dlsym(test,"t");
		if (t==NULL)
			printf("Function -t cannot be loaded\n");
		else
		{
			ret=t();
			if (ret>=0)
			printf("Cpu time %d\n", ret);
		else
			printf("Brak obsługi parametru -t\n");
		}
	}
	
	
	if (uflag)
	{
		u=dlsym(test,"u");
		if (u==NULL)
			printf("Function -u cannot be loaded\n");
		else
		{
			ret=u();
			if (ret>=0)
				printf("Max user processes %d\n", ret);
			else
				printf("Brak obsługi parametru -u\n");
		}
	}
	
	dlclose(test);
	return 0;
}
	printf("Missing option\n");
	dlclose(test);
	return 1;
}

dlerror();
return 1;
}
