#pragma once
#include "stdafx.h"
#include "MagicMatrix.h"
#include <iostream>
#include <sstream>

MagicMatrix::MagicMatrix(int _size)
{
	if (_size < 0)
		_size = 0;
	size = _size;
	elements = new Element*[size];
	for (int i = 0; i < size; ++i)
	{
		elements[i] = new Element[size];
		for (int j = 0; j < size; j++)
		{
			elements[i][j].mutex.lock();
			elements[i][j].element = (((size - j - 1) + i * 2 + 1) % size)*size + ((j + i * 2 + 1) % size) + 1;
			elements[i][j].mutex.unlock();
		}
	}
}

MagicMatrix::~MagicMatrix()
{
	
}

void MagicMatrix::deAlloc()
{
		for (int i = 0; i < hidden.size(); i++)
			hidden[i].clear();

			for (int i = 0; i < size; i++)
			{
				if (elements[i]) delete[] elements[i];
			}
			if (elements)delete[] elements;

}

void MagicMatrix::hideElements(int n)
{
	srand(time(NULL));

	if (n > size*size) // trying to hide more then exist SIC!
		n = size*size;

	if (n+hidden.size() > size*size) // can't hide more then real matrix magnitiude order
		n = size*size - hidden.size();

	int i;
	for (i = 0; i < hidden.size(); i++)
		elements[hidden[i][0]][hidden[i][1]].element = 0;
	std::vector<int> temp;
	for (; i < n; i++)
	{
		do 
		{
			temp.clear();
			temp.push_back(rand() % size);
			temp.push_back(rand() % size);
		} while (elements[temp[0]][temp[1]].element == 0);
		hidden.push_back(temp);
		elements[hidden[i][0]][hidden[i][1]].element = 0;
	}
	temp.clear();
}

void MagicMatrix::hideSelectedElement(int x, int y)
{
	std::vector<int> temp;
	temp.push_back(x);
	temp.push_back(y);
	hidden.push_back(temp);
	elements[hidden[hidden.size()-1][0]][hidden[hidden.size()-1][1]].element = 0;
}

std::string MagicMatrix::printMatrix()
{
	std::stringstream _return;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			if (elements[i][j].element!=0)
			_return << elements[i][j].element << "\t";
			else
			_return << "   " << "\t";
		_return << "\n";
	}
	return (_return.str());
			
};

void MagicMatrix::clearHidden()
{
	for (int i = 0; i < hidden.size(); i++)
		hidden[i].clear();
}

answer MagicMatrix::getSumOfElements(int row, int trigger)
{
	answer _return;
	_return.sum = 0;
	if (trigger >= 0)
		if (!trigger)
			for (int i = 0; i < size; i++)
			{
				elements[row][i].mutex.lock();
				if (!elements[row][i].element)
					_return.wrong.push_back(i);
				_return.sum += elements[row][i].element;
				elements[row][i].mutex.unlock();
			}
		else
			for (int i = 0; i < size; i++)
			{
				elements[i][row].mutex.lock();
				if (!elements[i][row].element)
					_return.wrong.push_back(i);
				_return.sum += elements[i][row].element;
				elements[i][row].mutex.unlock();
			}
	else
	{
		if (!row)
			for (int i = 0; i < size; i++)
			{
				elements[i][i].mutex.lock();
				if (!elements[i][i].element)
					_return.wrong.push_back(i);
				_return.sum += elements[i][i].element;
				elements[i][i].mutex.unlock();
			}
		else
			for (int i = 0; i < size; i++)
			{
				elements[i][size - i - 1].mutex.lock();
				if (!elements[i][size-i-1].element)
					_return.wrong.push_back(i);
				_return.sum += elements[i][size - i-1].element;
				elements[i][size - i - 1].mutex.unlock();
			}
	}
	_return.trigger = trigger;
	_return.row = row;
	return(_return);
}

bool MagicMatrix::insertElement(int row, int no, int trigger, int input)
{
	//if (input < 0)
		//std::cout << "i dupa\n";
	if (trigger >= 0)
		if (!trigger) {
			elements[row][no].mutex.lock();
			elements[row][no].element = input;
			elements[row][no].mutex.unlock();
		}
		else
		{
			elements[no][row].mutex.lock();
			elements[no][row].element = input;
			elements[no][row].mutex.unlock();
		}

	else
		if (!row){
			elements[no][no].mutex.lock();
				elements[no][no].element = input;
				elements[no][no].mutex.unlock();
			}
		else{
			elements[no][size - no - 1].mutex.lock();
				elements[no][size - no - 1].element = input;
				elements[no][size - no - 1].mutex.unlock();
			}
	return 0;
}