#pragma once

#include <vector>
#include "Proces.h"
#include "Menager.h"

class Menager;

class History
{
	int cycle_counter;
	std::vector<std::vector<Proces>> history;
public:
	History() : cycle_counter(0) {}
	~History();
	void AddNewHistory(Menager*);
	std::string GetHistoryForCount(int);
	std::string GetHistory();
	std::string GetHistoryLast();
};
