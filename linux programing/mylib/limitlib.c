//SO2 IS1 211A LAB02
//Artur Ziemba
//aziemba@wi.zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

struct rlimit rl_ogr;

int t()
{
	getrlimit(RLIMIT_CPU, &rl_ogr);
	return(rl_ogr.rlim_cur);
}

int d()
{
	getrlimit(RLIMIT_DATA, &rl_ogr);
	return(rl_ogr.rlim_cur);
}

int n()
{
	getrlimit(RLIMIT_NOFILE, &rl_ogr);
	return(rl_ogr.rlim_cur);
}

int u()
{
	getrlimit(RLIMIT_NPROC, &rl_ogr);
	return(rl_ogr.rlim_cur);
}

int s()
{
	getrlimit(RLIMIT_STACK, &rl_ogr);
	return(rl_ogr.rlim_cur);
}

int c()
{
	getrlimit(RLIMIT_CORE, &rl_ogr);
	return(rl_ogr.rlim_max);
	//return(getrlimit(RLIMIT_FSIZE, &rl_ogr));
}



