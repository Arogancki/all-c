
#include "stdafx.h"
#include "matrix.h"
#include <vector>
#include <iostream>
#include <sstream> 
#include <fstream>
#include <ctime>

// matrix

Matrix::Matrix(int HEIGHT = 0, int WIDTH = 0)
{
	width = WIDTH;
	height = HEIGHT;

	std::vector < double > temp;
	for (int count = 0; count <width; count++)
		temp.push_back(0);
	for (int count = 0; count < height; count++)
		matrix.push_back(temp);
}

Matrix::~Matrix()
{
	matrix.clear();
}

void Matrix::setcell(int HEIGHT, int WIDTH, double newvalue)
{
	if (width != 0 && height != 0)
		matrix[HEIGHT - 1][WIDTH - 1] = newvalue;
}

std::string Matrix::getcell(int HEIGHT, int WIDTH)
{
	std::stringstream value;
	value << matrix[HEIGHT - 1][WIDTH - 1];
	return(value.str());
}

std::string Matrix::getrow(int HEIGHT)
{
	std::stringstream value;
	for (int count = 0; count < width; count++)
		value << matrix[HEIGHT-1][count] << " ";
	return(value.str());
}

std::string Matrix::getcolumn(int WIDTH)
{
	std::stringstream value;
	for (int count = 0; count < height; count++)
		value << matrix[WIDTH - 1][count] << " ";
	return(value.str());
}

std::string Matrix::getmatrix()
{
	std::stringstream value;
	for (int count = 0; count < height; count++)
		value << getrow(count + 1) << std::endl;
	return(value.str());
}

void Matrix::addtoallcells(double value)
{
	for (int count = 0; count < height; count++)
		for (int count2 = 0; count2 < width; count2++)
			matrix[count][count2] += value;
}

Matrix* Matrix::transpose()
{
	Matrix *newmatrix = new Matrix(width, height);
	for (int count = 0; count < width; count++)
		for (int count2 = 0; count2 < height; count2++)
			newmatrix->setcell(count + 1, count2 + 1, matrix[count2][count]);
	return(newmatrix);
}

std::string Matrix::save()
{
	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t);
	std::stringstream location;
	location << height << "x" << width << "t=" << now.tm_hour << "-" << now.tm_min << "-" << now.tm_sec << ".txt";
	std::ifstream inputFile(location.str());
	if (inputFile.is_open())
	{
		std::cout << "Nazwa Pliku jest zajeta, plik zostanie nazwany - \"c" << location.str() << "\"\n";
		std::stringstream locati;
		locati << "c" << location.str();
		location.str("");
		location << locati.str();
	}
	std::ofstream outputFile(location.str());
	outputFile << height << ";" << width << std::endl;
	outputFile << getmatrix();
	std::cout << "zapisano macierz o rozmiarach " << height << " na " << width << " do pliku " << location.str() << std::endl;
	return(location.str());
}

Matrix::Matrix(std::string location)
{
	std::ifstream inputFile(location);
	if (!inputFile.is_open())
	{
		std::cout << "Nie udalo sie odczytac pliku " << location << "!\n";
		return;
	}
	std::string data;
	getline(inputFile, data);
	std::stringstream HEIGHT, WIDTH;
	int count = 0;
	while (';' != data[count])
	{
		HEIGHT << data[count];
		count++;
	}
	count++;
	while (NULL != data[count])
	{
		WIDTH << data[count];
		count++;
	}
	// usuniecie dotychczasowej macierzy 
	matrix.clear();
	// ustawienie nowych width oraz height
	WIDTH >> width;
	HEIGHT >> height;
	// ustawienie nowej macierzy wypelnionej 0
	std::vector < double > temp;
	for (int count = 0; count < width; count++)
		temp.push_back(0);
	for (int count2 = 0; count2 < height; count2++)
		matrix.push_back(temp);
	// wrzucanie kolejnych wartosci do macierzy
	int w, h = 1;
	getline(inputFile, data);
	while (data[0] != NULL)
	{
		w = 1;
		count = 0;
		while (data[count] != NULL)
		{
			std::stringstream value;
			value.str("");
			while (data[count] != ' ')
			{
				value << data[count];
				count++;
			}
			double temp;
			value >> temp;
			setcell(h, w, temp);
			w++;
			count++;
		}
		h++;
		getline(inputFile, data);
	}
	std::cout << "zaladowano dane z pliku " << location << std::endl;
}

Matrix* Matrix::changecell(int HEIGHT, int WIDTH, double newvalve)
{
	Matrix *newmatrix = new Matrix(width, height);
	for (int count = 0; count < width; count++)
		for (int count2 = 0; count2 < height; count2++)
			newmatrix->setcell(count + 1, count2 + 1, matrix[count2][count]);
	newmatrix->setcell(HEIGHT, WIDTH, newvalve);
	return(newmatrix);
}

void Matrix::can_Itimes(Matrix second) throw(std::string)
{
	if (this->width != second.height && this->height != 0 && this->width != 0 && second.height != 0 && second.width != 0)
	{
		std::string exp = "inposible flag";
		throw (exp);
	}
}

Matrix* Matrix::times(Matrix second)throw (std::string)
{
	try
	{
		can_Itimes(second);
	}
	catch (std::string)
	{
		std::string error="Nieprawidlowy rozmiar macierzy\n";
		throw(error);
	}
	Matrix *newmatrix = new Matrix(height, second.width);
	for (int count = 0; count < height; count++)
		for (int count2 = 0; count2 < second.width; count2++)
			for (int count3 = 0; count3 < width; count3++)
				newmatrix->matrix[count][count2] += this->matrix[count][count3] * second.matrix[count3][count2];
	return(newmatrix);
}

Matrix* Matrix::add(Matrix second)throw (std::string)
{
	try
	{
		can_Iaddsub(second);
	}
	catch (std::string)
	{
		std::string error = "Nieprawidlowy rozmiar macierzy\n";
		throw(error);
	}
	Matrix *newmatrix = new Matrix(height, width);
	for (int count = 0; count < height; count++)
		for (int count2 = 0; count2 < width; count2++)
			newmatrix->setcell(count + 1, count2 + 1, matrix[count][count2] + second.matrix[count][count2]);
	return(newmatrix);
}

Matrix* Matrix::sub(Matrix second)throw (std::string)
{
	try
	{
		can_Iaddsub(second);
	}
	catch (std::string)
	{
		std::string error = "Nieprawidlowy rozmiar macierzy\n";
		throw(error);
	}
	try
	{
		can_Iaddsub(second);
	}
	catch (std::string)
	{
		std::string error = "Nieprawidlowy rozmiar macierzy\n";
		throw(error);
	}
	Matrix *newmatrix = new Matrix(height, width);
	for (int count = 0; count < height; count++)
		for (int count2 = 0; count2 < width; count2++)
			newmatrix->setcell(count + 1, count2 + 1, matrix[count][count2] - second.matrix[count][count2]);
	return(newmatrix);
}

void Matrix::can_Iaddsub(Matrix second)throw(std::string)
{
	if (this->width != second.width && this->height != second.height && this->height != 0 && this->width != 0)
	{
		std::string exp = "inposible flag";
		throw (exp);
	}
}


Matrix Matrix::operator+(Matrix second)
{
	try
	{
		this->can_Iaddsub(second);
	}
	catch (std::string)
	{
		std::cout << "Nieprawidlowy rozmiar macierzy\n";
		return(*(this));
	}
	return(*(this->add(second)));
}

Matrix Matrix::operator+=(Matrix second)
{
	try
	{
		this->can_Iaddsub(second);
	}
	catch (std::string)
	{
		std::cout << "Nieprawidlowy rozmiar macierzy\n";
		return(*this);
	}
	Matrix *temp = this->add(second);
	this->matrix = temp->matrix;
	this->height = temp->height;
	this->width = temp->width;
	return(*this);
}

Matrix Matrix::operator*(Matrix second)
{
	try
	{
		this->can_Itimes(second);
	}
	catch (std::string)
	{
		std::cout<<"Nieprawidlowy rozmiar macierzy\n";
		return(*this);
	}
	return(*this->times(second));
}

Matrix Matrix::operator*=(Matrix second)
{
	try
	{
		this->can_Itimes(second);
	}
	catch (std::string)
	{
		std::cout << "Nieprawidlowy rozmiar macierzy\n";
		return(*this);
	}
	Matrix *temp = this->times(second);
	this->matrix = temp->matrix;
	this->height = temp->height;
	this->width = temp->width;
	return(*this);
}

Matrix Matrix::operator!()
{
	return(*this->transpose());
}

Matrix Matrix::operator=(Matrix second)
{
	Matrix temp = second;
	this->matrix =second.matrix;
	this->height = second.height;	
	this->width = second.width;
	return(*this);
}

double Matrix::det() throw (std::string)
{
	if (height > 2 || width >2)
	{
		std::string exp = "Wyznacznik tylko dla 2x2 !!";
		throw (exp);
	}
	double a = (this->matrix[0][0] * this->matrix[1][1]) - (this->matrix[0][1] * this->matrix[1][0]);
	return(a);
}
