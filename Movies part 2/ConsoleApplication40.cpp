#include "stdafx.h"
#include <iostream>
#include "ConsoleApplication40.h"
#include <string>
#include <sstream>
#include <ctime>
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
	horror.print();
	akcja.print();
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
	horror.print();
	akcja.print();
	horror_kopia.print();
	system("cls");


	// Zadanie 22.10
	cout << "Zadanie 22.10\n";
	// stworzenie 4 gatunku i wczytanie z pliku
	cout << "Podaj nazwe pliku znajdujacego sie w biezacym katalogu\nz danymi okreslajacymi nowy gatunek\n";
		string location;
		cin >> location;
		cout << endl;
		getchar();
		for (count = 0; count <5; count++)
		{
			stringstream s;
			s << "Jakis Film Komedia " << count + 1;
			movies[count] = s.str();
		}
		Directioner seventh("Imie41", "Pseudonim41", "Nazwisko41", movies);

		for (count = 0; count <5; count++)
		{
			stringstream s;
			s << "Przykladowy Film Komedia " << count + 1;
			movies[count] = s.str();
		}
		Directioner eith("Imie42", "Pseudonim42", "Nazwisko42", movies);

		for (count = 0; count <5; count++)
		{
			stringstream s;
			s << "Wybrany Film Komedia " << count + 1;
			movies[count] = s.str();
		}
		Directioner nine("Imie43", "Pseudonim43", "Nazwisko43", movies);
		directs[0] = seventh;
		directs[1] = eith;
		directs[2] = nine;
		pointer = &directs[0];
		Gene komedia("komedia", pointer);
	komedia.loadd(location);
	komedia.print();
	// modyfikacja pierwszego rezysera z komedi
	for (count = 0; count <5; count++)
	{
		stringstream s;
		s << "Zmodyfikowany Film Komedia " << count + 1;
		movies[count] = s.str();
	}
	komedia.directs[0].change("ZmodyfikowaneImie", "ZmodyfikowanyNick", "ZmodyfikowaneNazwisko", movies);
	// wyswietlanie wszystkich 4 gatunkow
	cout << "Wypisanie wszystkich 4 gatunkow \n";
	cout << "2 Gatunki unikalne:\n";
	horror.print();
	akcja.print();
	cout << "Gatunek kopia gatunku horror (po modyfikacji 1 rezysera (zadanie poprzednie)):\n";
	horror_kopia.print();
	cout << "Gatunek wczytany z pliku ze zmodyfikowanym pierwszym rezyserem :\n";
	komedia.print();
	
	// ilosc sekund do polnocy 
	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t);
	stringstream time;
	time << now.tm_hour << "-" << now.tm_min << "-" << now.tm_sec;

		// zapis gatunkow do plikow "gatunek"+nazwa+aktualny czas
	stringstream name;
	name << "gatunek " << horror.givename() << time.str()<< ".txt";
		horror.savee(name.str());
		name.str("");
		name << "gatunek " << akcja.givename() << time.str() << ".txt";
		akcja.savee(name.str());
		name.str("");
		cout << "\nNastapi zmiana nazwy pliku\nDzieje sie tak poniewaz\njest to kopia gatunku ktory zostal juz zapisany na dysku\nich nazwy sa takie same wiec plik\n(wedlug wytycznych okreslonych w tresci zadania)\npowinien nosic taka sama nazwe \n\n";
		name << "gatunek " << horror_kopia.givename() << time.str() << ".txt";
		horror_kopia.savee(name.str());
		name.str("");
		name << "gatunek " << komedia.givename() << time.str() << ".txt";
		komedia.savee(name.str());
	getchar();
}

