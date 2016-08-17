#pragma once
#include <iostream>
#include <vector>

class Matrix
{
public:
	Matrix(int, int);
	Matrix(std::string);
	~Matrix();
	void setcell(int, int, double);
	void addtoallcells(double); // ustawienie podanej komorki
	std::string getcell(int, int);
	std::string getrow(int);
	std::string getcolumn(int);
	std::string getmatrix();
	Matrix* transpose(); // transpnowanie
	Matrix* add(Matrix); // dodawanie macierzy
	Matrix* sub(Matrix);// odejmowanie macierzy
	Matrix* times(Matrix)throw (std::string); // mnozenie macierzy
	Matrix* changecell(int, int, double); // zwrocenie macierzy ze zmieniona komorka
	std::string save(); // nazwa- hight x width + czas
	double det()throw (std::string); // wyznacznik 2x2
	// operatory
	Matrix operator +(Matrix);
	Matrix operator *(Matrix);
	Matrix operator =(Matrix);
	Matrix operator +=(Matrix);
	Matrix operator *=(Matrix);
	Matrix operator !(); // transponowanie
private:
	int width, height;
	std::vector < std::vector < double > >  matrix;
	void can_Itimes(Matrix);// metoda sprawdzajaca czy wiersze z 1 = kolumny z 2 macierzy
	void can_Iaddsub(Matrix);// metoda sprawdzajaca czy ten sam rozmiar macierzy
};