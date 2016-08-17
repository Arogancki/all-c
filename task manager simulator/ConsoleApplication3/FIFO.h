#pragma once
#include "Strategy.h"

class FIFO:public Strategy
{
public:
	FIFO() {}
	std::vector <int> select(std::vector <Proces>);
};
