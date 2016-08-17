#pragma once
#include "Strategy.h"

class SJF:public Strategy
{
public:
	 std::vector <int> select(std::vector<Proces>);
};
