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
	Directioner(string NAME, string NICK, string SURNAME, string MOVIES[]);  // konst
	void change(string NAME, string NICK, string SURNAME, string MOVIES[]);
	~Directioner(); // des
	void load();
	void save();
};

class Gene
{
private:
	string name;
public:
	Directioner directs[3];
	void print(); 
	Gene(string NAME, Directioner *DIRECTS); // konstruktor
	~Gene(); // destruktor
};