#pragma once
#include "Proces.h"
#include <vector>

class Strategy
{
public:
	virtual std::vector <int> select(std::vector<Proces>) = 0;
};
