// Lab5 PO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Lab5 PO.h"
#include <sstream> 
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
        // ##X#X##
        // X#####X
        // ##X#X##
        int x[15] = { (-3), (-2), 0, 2, 3, (-2), (-1), 0, 1, 2, (-3), (-2), 0, 2, 3 };
        int y[15] = { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, (-1), (-1), (-1), (-1), (-1), };
        Room *rooms[3][5];
        int count3 = 0;
        for (int count = 0; count < 3; count++)
                for (int count2 = 0; count2 < 5; count2++)
                {
                        stringstream name;
                        name << "Pokoj nr " << count << " " << count2;
                        rooms[count][count2] = new Room(name.str(), x[count3], y[count3]);
                        count3++;
                }
        for (int count = 0; count < 3; count++)
                for (int count2 = 0; count2 < 5; count2++)
                {
                        Room current = *rooms[count][count2];
                        for (int count3 = 0; count3 < 3; count3++)
                                for (int count4 = 0; count4 < 5; count4++)
                                {
                                        Room search = *rooms[count3][count4];
                                        int currentx = current.getx();
                                        int currenty = current.gety();
                                        int searchx = search.getx();
                                        int searchy = search.gety();
                                        if (searchx == currentx && searchy == currenty + 1)
                                                current.setn(rooms[count3][count4]);
                                        if (searchx == currentx && searchy == currenty - 1)
                                                current.sets(rooms[count3][count4]);
                                        if (searchx == currentx + 1 && searchy == currenty)
                                                current.sete(rooms[count3][count4]);
                                        if (searchx == currentx - 1 && searchy == currenty)
                                                current.setw(rooms[count3][count4]);
                                }
                        *rooms[count][count2] = current;
                }
        // koniec usatwainia nazw, sasiadow, x y roomow
        // dziala na bank
		
		// wydrukowanie mapy

		// przechodzenie po pomieszczeniach 
				int steps=0;
			for (int count = 0; count < 3; count++)
                for (int count2 = 0; count2 < 5; count2++)
				{
				Room current = *rooms[0][0];
				// jesli chce zrobic poruszanie sie na biezaco pobierac kierunki news i isc w ich g
				if (current.istheresomethink()!=0)
					cout <<"Przedmiot to "<<current.getitem()<<"\n Krok numer "<<steps;
				steps++;
				}

		//wydrukowanie mapy

				if (map[count]=='#')
				{
					map[count]=//litera przedmiotu;
				}

        getchar();
        // delete rooms[*][*]
		for (int count = 0; count < 3; count++)
                for (int count2 = 0; count2 < 5; count2++)
					delete rooms[count][count2];
		delete[] rooms;
		
        return 0;
}

class Room;

class Map
{
	private:
		int wysokosc;
		int grubosc;
		string map;
	public:
		Map(int WYSOKOSC, int GRUBOSC);
		~Map();
		void mademap(Room *[][], int,int);
		string showmap();
};

Map::Map(int WYSOKOSC, int GRUBOSC)
{
	wysokosc=WYSOKOSC;
	grubosc=GRUBOSC;
	map="0";
}
Map::~Map()
	{}

void Map::mademap(Room *rooms[][], int sizey, int sizex)
{
	stringstream map2;
   for (int count = 0; count < sizex; count++)
   {
		map2<<"X"; 
   }
	for (int count = 0; count < sizey; count++)
	{
	map2<<endl; 
	for (int count2 = 0; count2 < sizex; count2++)
                {
					Room current = *rooms[count][count2];
					if (current.getw==NULL)
						map2<<"X"; 
					map2<<"#";
					if (current.gete==NULL)
						map2<<"X"; 
				}
	}
	for (int count = 0; count < sizex; count++)
    {
		map2<<"X"; 
	}
	map=map2.str();
}

string Map::showmap()
{
	return(map);
}

