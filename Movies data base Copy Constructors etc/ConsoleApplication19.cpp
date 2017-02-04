#include "stdafx.h"
#include <iostream>
#include "ConsoleApplication19.h"
#include <string>
#include <sstream>
#include <xstring>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	
	//stworzyc 2 gatunki po 3 rezyserow, 
	// 3 rezyserow i ich gatunek
	string movies[6];
	int count;
	for (count=0; count <5; count++)
	{
		stringstream s;
		s<<"Jakis Film Horror "<<count+1;
		movies[count]=s.str();
	}
	Directioner first("Imie1", "Pseudonim1", "Nazwisko1", movies);
	for (count = 0; count <5; count++)
	{
		stringstream s;
		s << "Przykladowy Film Horror " << count+1;
		movies[count] = s.str();
	}
	Directioner second("Imie2", "Pseudonim2", "Nazwisko2", movies);

	for (count = 0; count <5; count++)
	{
		stringstream s;
		s << "Wybrany Film Horror " << count+1;
		movies[count] = s.str();
	}
	Directioner third("Imie3", "Pseudonim3", "Nazwisko3", movies);
	Directioner directs[3] = { first, second, third };
	Directioner *pointer;
	pointer = &directs[0];
	Gene horror("Horror", pointer);

	// 2 gatunek
	for (count = 0; count <5; count++)
	{
		stringstream s;
		s << "Jakis Film Akcja " << count+1;
		movies[count] = s.str();
	}
	Directioner fourth("Imie11", "Pseudonim11", "Nazwisko11", movies);

	for (count = 0; count <5; count++)
	{
		stringstream s;
		s << "Przykladowy Film Akcja " << count+1;
		movies[count] = s.str();
	}
	Directioner fivth("Imie22", "Pseudonim22", "Nazwisko22", movies);

	for (count = 0; count <5; count++)
	{
		stringstream s;
		s << "Wybrany Film Akcja " << count+1;
		movies[count] = s.str();
	}
	Directioner sixth("Imie33", "Pseudonim33", "Nazwisko33", movies);
	directs[0] = fourth;
	directs[1] = fivth;
	directs[2] = sixth;
	pointer = &directs[0];
	Gene akcja("Akcja", pointer);

	//skopiowac 2 gatunek do 3 gatunu
	Gene horror_kopia = horror;

	//wysiwtlic 3 gatunki,
	cout << "Drukowanie 3 gatunkow - 3 jest kopia 2\n";
	akcja.print();
	horror.print();
	horror_kopia.print();
	//zmienic dane jednego rezysera, 
	for (count = 0; count <5; count++)
	{
		stringstream s;
		s << "Nowy Jakis Film Horror " << count+1;
		movies[count] = s.str();
	}
	horror_kopia.directs[0].change("nowe imie", "nowy pseudonim", "nowe nazwisko", movies);
	//wyswietalic wszystkie gatunki (dane zmienionego rezysera powinny )
	cout << "Zmiana parametrow rezysera Imie1 Nazwisko1, w 3 Gatunku\n";
	akcja.print();
	horror.print();
	horror_kopia.print();
	
	system("cls");
	cout<<"Zadanie 22.10\n";
		first.load();
		first.print();
		getchar();

}

