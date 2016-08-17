#pragma once

#include "stdafx.h"
#include "Proces.h"
#include <time.h>

Proces::~Proces()
{
}

void Proces::DoStep()
{
	if (state != 'Z')
	{
		state = 'D';
	}
}

void Proces::EndStep()
{
	if (state != 'Z')
	{
		int complate = time(NULL) + sec_for_step;
		while (complate > time(NULL))
			;
		steps++;
		if (steps >= to_end)
			state = 'Z';
		else
			state = 'W';
		sec_for_step = sec_for_next_step;
		sec_for_next_step=(rand() % 7) + 1;
	}
}

char Proces::GetState()
{
	return(state);
}

int Proces::GetID()
{
	return(this->ID);
}

int Proces::GetSec_for_step()
{
	return(sec_for_step);
}
