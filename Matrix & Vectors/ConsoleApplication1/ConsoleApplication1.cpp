// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrix.h"
#include <iostream>
#include <sstream> 

int main()
{
	// Ladowanie z pliku A oraz B
	Matrix A("A.txt"); // 4,3 
	Matrix B("B.txt"); 
	Matrix C("C.txt");
	Matrix D = A + B + C;
	for (int count = 1; count < 5; count++)
		std::cout << A.getrow(count) << " --- " << B.getrow(count) << " --- " << C.getrow(count) << " --- " << D.getrow(count) << std::endl;
	std::cout << std::endl;
	Matrix E("E.txt");
	Matrix F("F.txt");
	Matrix G = E*F;
	G += G*G;
	for (int count = 1; count < 3; count++)
		std::cout << E.getrow(count) << " --- " << F.getrow(count) << " --- " << G.getrow(count) << std::endl;
	std::cout << std::endl;
	G = !G ;
	std::cout << G.getmatrix();
	try {
		G.det();
	}
	catch (std::string)
	{
		std::cout << "Det tylko dla 2x2\n";
	}
		std::cout<<"wyznacznik " << G.det();

	getchar();
	return 0;
}

