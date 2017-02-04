#include "stdafx.h"
#include <iostream>
#include <xstring>
using namespace std;


class Directioner
{
private:
	string name;
	string nick;
	string surname; 
	string movies[6];
public:
	void print();  
	void KonstruktorString(string direct);
	Directioner(string NAME, string NICK, string SURNAME, string MOVIES[]);  // konst
	void change(string NAME, string NICK, string SURNAME, string MOVIES[]);
	~Directioner(); // des
	void load(string location);
	string preparetosave(); // przeksztalcenie funkcji print tak aby zwracala string zawierajcy zmienne klasy przygotowane do zapisu
	void save(string location);
};

class Gene
{
private:
	string name;
public:
	Directioner directs[3];
	void savee(string locatio);
	void loadd(string locatio);
	string givename(); // funkcja potrzebna do budowania nazw plikow do zapisu, niezbedna poniewarz nazwa jest prywatna
	void print(); 
	Gene(string NAME, Directioner *DIRECTS); // konstruktor
	~Gene(); // destruktor
};