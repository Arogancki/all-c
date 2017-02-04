// Artur Ziemba Magic matrix 
#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include "MagicMatrix.h"
#include "MagicMatrixSolver.h"

#define matrixSize 7
#define hiddenSize 1

std::vector <std::vector <std::mutex >> elementsMutex;
std::vector <std::mutex > elementsMute2x;

int main(int argc, char **argv)
{

		MagicMatrix magicznaMacierz(matrixSize);
		std::cout << "Macierz:\n" << magicznaMacierz.printMatrix() << "\n";
		magicznaMacierz.hideElements(hiddenSize);
		std::cout << "Macierz po ukryciu " << hiddenSize << " elementow\n" << magicznaMacierz.printMatrix() << "\n";
		magicznaMacierz.hideElements(hiddenSize);
		magicMatrixSolver solver(&magicznaMacierz);
		magicznaMacierz.deAlloc();

	getchar();
	system("cls");

}