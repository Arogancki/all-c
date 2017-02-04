#pragma once
#include "stdafx.h"
#include <sstream>
#include <ctime>
#include "Bombki.h"

std::string Bombki::draw()
{
	{
		std::stringstream drawning;
		int space_inside = 0;
		bool last = 0;// czy ostatnio bylo _
		srand(time(NULL));
		int snow = rand() % 2;
		for (int size = szerokosc; size >= 0; size--)
		{
			std::stringstream line;
			for (int count = size; count > 0; count--)
			{
				if (count % 3 == snow % 2)
					line << "*";
				else
					line << " ";
			}
			snow++;
			line << "/";
			for (int count = space_inside; count > 0; count--)
			{
				if (count == space_inside && (space_inside % 2 == 0) && size != 0)
				{
					if (last == 0)
					{
						size++;
						space_inside--;
						count--;
						last = 1;
						line << "_";
					}
					else
						last = 0;
				}
				switch (((5 * count) + rand()) % 3)
				{
				case 0:
					line << " "; // srodek
					break;
				case 1:
					line << "O"; // srodek
					break;
				case 2:
					line << "@"; // srodek
				}
			}
			drawning << line.str();
			// dublacja stinga - choinka symetryczna
			for (int count = line.str().size() - 1; count >= 0; count--)
			{
				if (line.str()[count] == 47)
					drawning << "\\";
				else
					if (line.str()[count] == 92)
						drawning << "/";
					else
						drawning << line.str()[count];
			}

			drawning << std::endl;
			space_inside++;
		}
		// pien 
		std::stringstream line;
		for (int size = 0; size <= szerokosc; size++)
		{
			if (size % 2)
				line << "/";
			else
				line << "\\";
		}
		for (int count = line.str().size() - 1; count >= 0; count--)
		{
			if (line.str()[count] == 47)
				line << "\\";
			else
				if (line.str()[count] == 92)
					line << "/";
				else
					line << line.str()[count];
		}
		drawning << line.str() << std::endl;

		for (int count = szerokosc; count > 1; count--)
		{
			if (count % 2 == snow % 2)
				drawning << "*";
			else
				drawning << " ";
		}
		snow++;
		drawning << "/XX\\";
		for (int count = szerokosc; count > 1; count--)
		{
			if (count % 2 == snow % 2)
				drawning << "*";
			else
				drawning << " ";
		}
		drawning << "\n";
		for (int i = 0; i < 2; i++)
		{
			for (int count = (szerokosc + 1) * 2; count > 0; count--)
				drawning << "*";
			drawning << std::endl;
		}
		for (int count = (szerokosc + 1) * 2; count > 0; count--)
			drawning << "_";
		return(drawning.str());
	}
}

Bombki::Bombki(int x) :XmassTree(x)
{
	if (x < 1)
		x = 1;
	szerokosc = x;
}
