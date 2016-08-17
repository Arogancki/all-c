#pragma once

#include <cstdlib>

class Proces
{
	int ID, steps, to_end, sec_for_step, sec_for_next_step; // id, wykonane kroki, pozostale kroki, ilosc maksymalnie sekund na wykonanie kroku
	char state; // D ziala, W strzymany, Z akonczyon 
public:
	// id, ilosc krokow
	Proces(int _ID, int _to_end): ID(_ID), to_end(_to_end), steps(0), sec_for_step((rand() % 7)+1), state('W'), sec_for_next_step((rand() % 7) + 1) {}
	~Proces();
	// sety
	void DoStep(); // ustawia proces na dzialanie
	void EndStep(); // dodaje 1 do stepsow,  oraz odczekuje czas 
	// zrobilem odzielne dla wyswietlania w Menager::startsproces
	//	gety
	char GetState();
	int GetID();
	int GetSec_for_step();
};
