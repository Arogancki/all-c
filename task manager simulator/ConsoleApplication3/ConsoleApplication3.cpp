#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include "Proces.h"
#include "Menager.h"
#include "History.h"
#include "FIFO.h"
#include "SJF.h"


int main()
{
	srand(time(NULL));
	
	Menager menFIFO(new FIFO);
	Menager menSJF(new SJF);
	for (int count = 0; count < 8; count++)
	{
		Proces *task=new Proces(1000 + count, ((rand() % 4) + 2));
		menFIFO.AddNewProces(task);
		menSJF.AddNewProces(task);
	}

	menFIFO.StartProcesses();
	std::cout << std::endl << menFIFO.GetHistory()->GetHistory();

	getchar();

	menSJF.StartProcesses();
	std::cout << std::endl << menSJF.GetHistory()->GetHistory();

	getchar();
    return 0;
}

