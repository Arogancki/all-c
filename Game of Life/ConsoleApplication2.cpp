// Artur Ziemba 

#include "stdafx.h"
#include <thread>
#include "GameOfLife.h"

#define Nframe 30
int timeInterval = (1000.0 / Nframe);

int main()
{
	GameOfLife sample(120,120, 2000, 4);
	sample.makeGif("Game Of Life.gif",timeInterval,4);
	//do
	//{
	//	system("cls");
	//	sample.print();
	//	std::this_thread::sleep_for(std::chrono::milliseconds(timeInterval));
	//} while (sample.doStep());
    return 0;
}