#include "stdafx.h"
#include <iostream>
using namespace std;


class Number
{
private:
	string value; // wartosc 
public:
	string ConvertFromSymbolic(); //zmiana symbolu na liczbe
	Number(string VALUE); // konstruktor
	~Number(); // destruktor
};

class Assert
{
private:
	int answer; // wartosc
public:
	int AreEqual(string first, string second); // porownanie dwoch string
	Assert(int ANSWER); // konstruktor
	~Assert(); // destruktor
};