#pragma once
#include "stdafx.h"
#include "magicMatrixSolver.h"
#include <iostream>
#include <sstream>

magicMatrixSolver::magicMatrixSolver(MagicMatrix *_magicznaMacierz)
{
	magicznaMacierz = _magicznaMacierz;
	std::vector<std::thread> threadList;
	matrixKey = -1;
	for (int i = 1; i > -2; i--)
		threadList.push_back(std::thread(&magicMatrixSolver::magicMatrixSolverThread, this, i));
	for (int i = 0; i < 3; i++)
		threadList[i].join();
	threadList.clear();

	if (matrixKey != -1)
		std::cout << "Rozwiazanie:\n" << magicznaMacierz->printMatrix();
	else
		std::cout << "Nie potrafie znalezc rozwiazania :((\n";

}

magicMatrixSolver::~magicMatrixSolver() {
	magicznaMacierz = NULL;
};

void magicMatrixSolver::magicMatrixSolverThread(int type) {
	// function variable depending on type
	int *myFlag;
	std::mutex *myFlagMutex;
	int *myBrotherFlag1;
	int *myBrotherFlag2;
	std::mutex *myBrotherFlagMutex1;
	std::mutex *myBrotherFlagMutex2;
	int maxLoop;
	if (type == 0)
	{
		rowsThreadFlagMutex.lock();
		myFlag = &rowsThreadFlag;
		myFlagMutex = &rowsThreadFlagMutex;
		rowsThreadFlagMutex.unlock();
		columnThreadFlagMutex.lock();
		myBrotherFlag1 = &columnThreadFlag;
		myBrotherFlagMutex1 = &columnThreadFlagMutex;
		columnThreadFlagMutex.unlock();
		diagonalThreadFlagMutex.lock();
		myBrotherFlag2 = &diagonalThreadFlag;
		myBrotherFlagMutex2 = &diagonalThreadFlagMutex;
		diagonalThreadFlagMutex.unlock();
		maxLoop = magicznaMacierz->getsize();
	}
	else if (type == 1)
	{
		columnThreadFlagMutex.lock();
		myFlag = &columnThreadFlag;
		myFlagMutex = &columnThreadFlagMutex;
		columnThreadFlagMutex.unlock();
		rowsThreadFlagMutex.lock();
		myBrotherFlag1 = &rowsThreadFlag;
		myBrotherFlagMutex1 = &rowsThreadFlagMutex;
		rowsThreadFlagMutex.unlock();
		diagonalThreadFlagMutex.lock();
		myBrotherFlag2 = &diagonalThreadFlag;
		myBrotherFlagMutex2 = &diagonalThreadFlagMutex;
		diagonalThreadFlagMutex.unlock();
		maxLoop = magicznaMacierz->getsize();
	}
	else
	{
		diagonalThreadFlagMutex.lock();
		myFlag = &diagonalThreadFlag;
		myFlagMutex = &diagonalThreadFlagMutex;
		diagonalThreadFlagMutex.unlock();
		columnThreadFlagMutex.lock();
		myBrotherFlag1 = &columnThreadFlag;
		myBrotherFlagMutex1 = &columnThreadFlagMutex;
		columnThreadFlagMutex.unlock();
		rowsThreadFlagMutex.lock();
		myBrotherFlag2 = &rowsThreadFlag;
		myBrotherFlagMutex2 = &rowsThreadFlagMutex;
		rowsThreadFlagMutex.unlock();
		maxLoop = 2;
	}
	int correctFlag=0;

	int solvedCounter = 0;

	myBrotherFlagMutex1->lock();
	myBrotherFlagMutex2->lock();
	myFlagMutex->lock();
	*myFlag = 0;
	while ((solvedCounter < maxLoop )&& (!*myBrotherFlag1 || !*myBrotherFlag2 || !*myFlag))
	{
		myBrotherFlagMutex1->unlock();
		myBrotherFlagMutex2->unlock();
		myFlagMutex->unlock();

		solvedCounter = 0;

			for (int j = 0; j < maxLoop; j++)
			{
				answer actualAnswer = magicznaMacierz->getSumOfElements(j, type);

				matrixKeyMutex.lock();
				if (matrixKey != -1) // defined sum
				{
					matrixKeyMutex.unlock();
					if (actualAnswer.wrong.size() <= 1) // able to repair
					{
						if (actualAnswer.wrong.size() == 1)
						{
							repairWithKey(actualAnswer);
							correctFlag = 1;
						}
						solvedCounter++;
					}
					// else unable to repair 
				}
				else
				{
					if (actualAnswer.wrong.size() == 0) // real sum can be defined
					{
						matrixKey = actualAnswer.sum;
						matrixKeyMutex.unlock();
						solvedCounter++;
					}
					else // real sum can't be defined
						matrixKeyMutex.unlock();
				}
			}

		if (correctFlag==1)
		{
			myFlagMutex->lock();
			*myFlag = 0;
			myFlagMutex->unlock();
			myBrotherFlagMutex1->lock();
			if (*(myBrotherFlag1)!=2)
				*(myBrotherFlag1) = 0;
			myBrotherFlagMutex1->unlock();
			myBrotherFlagMutex2->lock();
			if (*(myBrotherFlag2) != 2)
				*(myBrotherFlag2) = 0;
			myBrotherFlagMutex2->unlock();
		}
		else
		{
			myFlagMutex->lock();
			*myFlag = 1;
			myFlagMutex->unlock();
		}
		correctFlag = 0;

		myBrotherFlagMutex1->lock();
		myBrotherFlagMutex2->lock();
		myFlagMutex->lock();
	}
	*myFlag = 2;
	myFlagMutex->unlock();
	myBrotherFlagMutex1->unlock();
	myBrotherFlagMutex2->unlock();

//	std::cout<<magicznaMacierz->printMatrix()<<std::endl;
	if (solvedCounter < maxLoop)
		matrixKey = -1;

	/*

	myFlagMutex->lock();
	*myFlag = 2;
	myFlagMutex->unlock();

	correctFlagMutex.lock();
	if (correctFlag)
	{
		correctFlagMutex.unlock();
		myFlagMutex->lock();
		*myFlag = 2;
		myFlagMutex->unlock();

		myBrotherFlagMutex1->lock();
		myBrotherFlagMutex2->lock();
		while (*myBrotherFlag1<2 || *myBrotherFlag2<2)
		{
			myBrotherFlagMutex1->unlock();
			myBrotherFlagMutex2->unlock();
 			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			myBrotherFlagMutex1->lock();
			myBrotherFlagMutex2->lock();
		}
		myBrotherFlagMutex1->unlock();
		myBrotherFlagMutex2->unlock();
		correctFlagMutex.lock();
		correctFlag = 0;
		correctFlagMutex.unlock();
		
		magicMatrixSolverThread(solvedCounter, type);
	}
	else
		correctFlagMutex.unlock();
		*/
}

void magicMatrixSolver::repairWithKey(answer ans)
{
	int brakujaca = matrixKey - ans.sum;
	magicznaMacierz->insertElement(ans.row, ans.wrong[0], ans.trigger, brakujaca);
	ans.wrong.erase(ans.wrong.begin());
	ans.sum += brakujaca;
}