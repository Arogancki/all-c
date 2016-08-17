#pragma once
#include "stdafx.h"
#include "FIFO.h"

std::vector <int> FIFO::select(std::vector <Proces> proceses)
{
	std::vector <int> active_processes;
	for (int count = proceses.size()-1; count >=0; count--)
		if (proceses[count].GetState() != 'Z')
			active_processes.push_back(count);
	return(active_processes);
}
