#pragma once
#include "MagicMatrix.h"
#include <mutex>
#include <iostream>

class magicMatrixSolver {

public:
	magicMatrixSolver(MagicMatrix *_magicznaMacierz);
	~magicMatrixSolver();

	int getMatrixKey() { return matrixKey; }; // if key == -1 cannot solve
private:
	MagicMatrix *magicznaMacierz;
	int matrixKey = 0;
	std::mutex matrixKeyMutex;
	int rowsThreadFlag = 0;
	std::mutex rowsThreadFlagMutex;
	int columnThreadFlag = 0;
	std::mutex columnThreadFlagMutex;
	int diagonalThreadFlag = 0;
	std::mutex diagonalThreadFlagMutex;

	void repairWithKey(answer ans);
	
	void magicMatrixSolverThread(int type);
};