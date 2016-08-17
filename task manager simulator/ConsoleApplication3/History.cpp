#pragma once

#include "stdafx.h"
#include "History.h"
#include <sstream>

History::~History()
{
}

void History::AddNewHistory(Menager* processes)
{
	history.push_back(processes->GetProcessesVector());
	cycle_counter++;
	return;
}

std::string History::GetHistoryForCount(int number)
{
	if (number > cycle_counter)
		return("Bledny numer cyklu!\n");
		number--;
	std::stringstream to_return;
	for (int count = 0; count < history[number].size(); count++)
		to_return << history[number][count].GetID() << ": " << history[number][count].GetState() << std::endl;
	return(to_return.str());
}

std::string History::GetHistory()
{
	std::stringstream to_return;
	for (int count = 0; count < history[history.size() - 1].size(); count++)
	{
		to_return << history[history.size() - 1][count].GetID() << ": "; // id procesu
		int space = 0; // ustalam liczbe spacji
		for (int count2 = 0;; count2++)
			if (history[count2].size() <= count )
				space++;
			else
			{
				//space *= 2; // dodanie "-" co "stan"
				break;
			}
		for (int count2 = 0; count2 < history.size(); count2++)
			if (count2 < space)
				to_return << " ";
			else
			{
				to_return << history[count2][count].GetState();
			//	to_return << "-";
			}
		to_return << "\n";
	}
	return(to_return.str());
}

std::string History::GetHistoryLast()
{
	return(this->GetHistoryForCount(cycle_counter-1));
}
