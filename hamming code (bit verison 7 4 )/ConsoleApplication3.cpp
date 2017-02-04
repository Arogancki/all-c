// kod hamminga(7,4) Artur Ziemba

#include "stdafx.h"
#include <iostream>

using std::cin;
using std::cout;

long long toB(int n)
{
	long long binaryNumber = 0;
	int remainder, i = 1, step = 1;

	while (n != 0)
	{
		remainder = n % 2;
		n /= 2;
		binaryNumber += remainder*i;
		i *= 10;
	}
	return binaryNumber;
}

int tod(long n)
{
	int decimalNumber = 0, i = 0, remainder;
	while (n != 0)
	{
		remainder = n % 10;
		n /= 10;
		decimalNumber += remainder*pow(2, i);
		++i;
	}
	return decimalNumber;
}

int wczytaj_ciag()
{
	int bity = 0;
	cout << "Podaj ciag bitow \n";
	cin >> bity;
	bity = tod(bity);
	if (bity < 0 || bity > 127)
	{
		bity = 0;
		cout << "Bledne dane wejsciowe\n";
	}
	getchar();
	return (bity);
}

int hamming_koduj(long int bity)
{
	/*
	int b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0, b6 = 0, b7 = 0;

	b3 = ((bity & (1 << 0)) << 2);
	b5 = ((bity & (1 << 1)) << 3);
	b6 = ((bity & (1 << 2)) << 3);
	b7 = ((bity & (1 << 3)) << 3);

	b1 = (!!((bity & (1 << 0)) << 2) ^!!((bity & (1 << 1)) << 3) ^!!((bity & (1 << 3)) << 3));
	b2 = ((!!((bity & (1 << 0)) << 2) ^!!((bity & (1 << 2)) << 3) ^!!((bity & (1 << 3)) << 3)) << 1);
	b4 = ((!!((bity & (1 << 1)) << 3) ^!!((bity & (1 << 2)) << 3) ^!!((bity & (1 << 3)) << 3)) << 3);

	cout << b1 + b2 + b3 + b4 + b5 + b6 + b7;
	*/
	return(
		(!!((bity & (1 << 0)) << 2) ^ !!((bity & (1 << 1)) << 3) ^ !!((bity & (1 << 3)) << 3)) +
		((!!((bity & (1 << 0)) << 2) ^ !!((bity & (1 << 2)) << 3) ^ !!((bity & (1 << 3)) << 3)) << 1) +
		((bity & (1 << 0)) << 2) + ((!!((bity & (1 << 1)) << 3) ^ !!((bity & (1 << 2)) << 3) ^ !!((bity & (1 << 3)) << 3)) << 3) +
		((bity & (1 << 1)) << 3) + ((bity & (1 << 2)) << 3) + ((bity & (1 << 3)) << 3)
		);
}

int neguj_bit(int bity)
{
	int pozycja = 0;
	cout << "Podaj bit do negacji\n";
	cin >> pozycja;
	getchar();
	if (pozycja < 1 || pozycja>8)
		return bity;
	return (bity ^ (1 << (pozycja - 1)));
}

int hamming_odkoduj(int bity)
{
	/*
	int b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0, b6 = 0, b7 = 0, x1 = 0, x2 = 0, x4 = 0, blad=0;

	b1 = ((bity & (1 << 0)));
	b2 = ((bity & (1 << 1)));
	b3 = ((bity & (1 << 2)));
	b4 = ((bity & (1 << 3)));
	b5 = ((bity & (1 << 4)));
	b6 = ((bity & (1 << 5)));
	b7 = ((bity & (1 << 6)));

	x1 = (!!b3 ^ !!b5 ^ !!b7) ^ (!!b1);
	x2 = (((!!b3 ^ !!b6 ^ !!b7) ^ (!!b2)) << 1);
	x4 = (((!!b5 ^ !!b6 ^ !!b7) ^ (!!b4)) << 2);

	blad = tod(x1 + x2 + x4);
	*/
	int index = tod(((!!((bity & (1 << 2))) ^ !!((bity & (1 << 4))) ^ !!((bity & (1 << 6)))) ^ (!!((bity & (1 << 0)))))
		+ (((!!((bity & (1 << 2))) ^ !!((bity & (1 << 5))) ^ !!((bity & (1 << 6)))) ^ (!!((bity & (1 << 1))))) << 1)
		+ (((!!((bity & (1 << 4))) ^ !!((bity & (1 << 5))) ^ !!((bity & (1 << 6)))) ^ (!!((bity & (1 << 3))))) << 2));
	return (bity ^ (!!index << index-1));
}

int main()
{
	cout << "Kod Hamminga(7,4):\n\nZakoduj ciag czterech bitow,\nzaneguj jeden,\nHamming obliczy ktory zanegowales\n\n";
	int ciag = hamming_koduj(wczytaj_ciag());
	cout << "Nadajnik wysyla:\n\t" << toB(ciag) << "\n";
	ciag = neguj_bit(ciag);
	cout << "Odbiornik odebral:\n\t" << toB(ciag) << "\n";
	ciag = hamming_odkoduj(ciag);
	cout << "Po korekcji\n\t" << toB(ciag) << "\n";
	getchar();
	return 0;
}