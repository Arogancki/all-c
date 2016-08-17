#pragma once

#include "stdafx.h"
#include "Menager.h"
#include "Strategy.h"
#include <iostream>
#include <sstream>
#include <vector>

Menager::~Menager()
{
	delete arch;
}

Menager::Menager(Strategy *_strategy)
{
	strategy = _strategy;
	last = 0;
	arch = new History;
}


void Menager::AddNewProces(Proces*temp)
{
	if (processes.size()!=0)
	for (int count = 0; count < processes.size(); count++)
		if (temp->GetID() == processes[count].GetID())
			std::cout << "Nie mozna dodac procesu " << temp->GetID() << ". Proces o identycznym ID juz istnieje!\n";
	this->processes.push_back(*temp);
	this->last = temp->GetID();
	this->arch->AddNewHistory(this);
}

void Menager::StartProcesses()
{
	while (1)
	{
		int flag = 0;
		for (int count = 0; count < processes.size(); count++)
			if (processes[count].GetState() != 'Z')
			{
				flag = 1;
				break;
			}
		if (flag == 0)
		{
			this->arch->AddNewHistory(this);
			return;
		}
		/*
		for (int count = 0; count < processes.size(); count++)
		{
			if (processes[count]->GetState() != 'Z')
			{
				processes[count]->DoStep();
				system("cls");
				std::cout << GetProcesses();
				this->arch->AddNewHistory(this);

				processes[count]->EndStep();
				system("cls");
				std::cout << GetProcesses();
				this->arch->AddNewHistory(this);
			}
		}
		*/
			// wykonanie kroku wedlug wybranego algorytmu
		std::vector<int> active_proces =strategy->select(processes);
		for (int count = 0; count < active_proces.size();count++)
		{
			processes[active_proces[count]].DoStep();
			system("cls");
			std::cout << GetProcesses();
			this->arch->AddNewHistory(this);

			processes[active_proces[count]].EndStep();
			system("cls");
			std::cout << GetProcesses();
			this->arch->AddNewHistory(this);
		}
	}
}

int Menager::GetNumberOfProcesses()
{
	return(processes.size());
}

std::string Menager::GetProces(int number)
{
	std::stringstream to_return;
	to_return << processes[number].GetID() << ": " << processes[number].GetState() << "\n";
	return(to_return.str());
}

std::string Menager::GetProcesses()
{
	std::stringstream to_return;
	for (int count = 0; count < this->GetNumberOfProcesses(); count++)
		to_return << processes[count].GetID() << ": " << processes[count].GetState() << "\n";
	return(to_return.str());
}

std::vector<Proces> Menager::GetProcessesVector()
{
	std::vector <Proces> to_return;
	for (int count = 0; count < this->GetNumberOfProcesses(); count++)
		to_return.push_back(processes[count]);
	return(to_return);
}

History* Menager::GetHistory()
{
	return(arch);
}
