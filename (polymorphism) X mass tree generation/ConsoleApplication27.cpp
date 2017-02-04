// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "XmassTree.h"
#include "Sosna.h"
#include <iostream>
#include "Swieczki.h"
#include "Bombki.h"
#include <ctime>


int main()
{

	srand(time(NULL));
	XmassTree* pointer;
	while (1)
	{
		switch (rand() % 3)
		{
		case 0:
			pointer=(new Sosna(rand() % 30));
			break;
		case 1:
			pointer=(new Bombki(rand() % 30));
			break;
		default:
			pointer=(new Swieczki(rand() % 30));
			break;
		}
		std::cout << pointer->draw();
		delete pointer;
		getchar();
		system("cls");
	}
    return 0;
}
