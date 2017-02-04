#pragma once
#include "stdafx.h"
#include <mutex>
#include <vector>

typedef struct answer
{
	std::vector<int> wrong;
	int sum;

	// info triggera answera
	int row;
	bool trigger;
};

typedef struct Element
{
	int element;
	std::mutex mutex;
};

class MagicMatrix
{
public:

	MagicMatrix(int);
	~MagicMatrix();
	
	void hideElements(int);
	void hideSelectedElement(int,int); // x , y
	void clearHidden();
	std::string printMatrix();
	bool insertElement(int, int, int, int); // [row number],[horyzontaly on/off], diagonal = [-1],[0] for \ and [-1][1] for / , dig to insert 
	void repairWithKey(answer, int);
	void deAlloc();
	int getsize() { return size; };
	answer getSumOfElements(int, int); // [row number],[horyzontaly on/off], diagonal = [-1],[0] for \ and [-1][1] for / 

private:
	int getHiddenSize() { return(hidden.size()); };
	std::vector <std::vector <int>> hidden;

	Element** elements;
	int size;
};

