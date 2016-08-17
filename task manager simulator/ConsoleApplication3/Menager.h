#pragma once

#include <vector>
#include "Proces.h"
#include "History.h"

class Strategy;
class History;

class Menager
{
	std::vector <Proces> processes;
	int last; // ostatnio utworzony proces
	History *arch; // archiwum/historia
	Strategy *strategy;
public:
	Menager(Strategy*);
	~Menager();
	void AddNewProces(Proces*);
	void StartProcesses();
	// gety
	int GetNumberOfProcesses();
	std::string GetProces(int);
	std::string GetProcesses();
	std::vector <Proces> GetProcessesVector();
	History* GetHistory();
};
