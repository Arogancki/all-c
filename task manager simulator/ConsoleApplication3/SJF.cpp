#pragma once
#include "stdafx.h"
#include "SJF.h"
#include <iostream>

std::vector <int> SJF::select(std::vector<Proces> proceses)
{
	std::vector <int> active_processes; 
	for (int count = 0; count < proceses.size(); count++)
		if (proceses[count].GetState() != 'Z')
			active_processes.push_back(count); // tworzenie wektoru indeksow nie Z

	std::vector <int> active_processes2;
	while (active_processes.size()>0) // sortowanie dopoki cos zostalo w nieposortowanym wektorze
	{
		int min = active_processes[0];
		for (int count = 1; count < active_processes.size(); count++) // szukanie najmniejszej
			if (proceses[min].GetSec_for_step()>proceses[active_processes[count]].GetSec_for_step())
				min = active_processes[count]; // podmiana jesli jest mniejsza od najmniejszej

		for (int count = 0; count < active_processes.size(); count++)
			if (min== active_processes[count])
				active_processes.erase(active_processes.begin() + count); // usuniecie z wektoru indeksow
		active_processes2.push_back(min);
	}

	return(active_processes2);
}
