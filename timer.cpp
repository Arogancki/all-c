#include "stdafx.h"
#include <vector>
#include <iostream>
#include <windows.h>

int main()
{
	int ilosc_minutnikow, input, i;
	std::vector <int> minutniki;
	std::cout << "Podaj liczbe minutnikow\n";
	std::cin >> ilosc_minutnikow;
	for (i=0;i<ilosc_minutnikow;i++)
	{
		std::cout << "Podaj " << i + 1 << " minutnik (sek)\n";
		std::cin >> input;
		minutniki.push_back(input);
	}
	std::cout << "Enter Aby rozpoczac\n";

	while (1)
	{
		for (i = 0; i < ilosc_minutnikow; i++)
		{
			std::cout << "\a";
			Sleep(minutniki[i] * 1000);
		}
	}
}

