#include "stdafx.h"
#include "GameOfLife.h"
#include "gif.h"

void GameOfLife::realConstructor(int _width, int _height, int _maxCycles, int _numberOfThreads)
{
	if (_width < horizon + 2)
		_width = horizon + 2;
	if (_height < horizon + 2)
		_height = horizon + 2;
	pixels = NULL;
	width = _width;
	height = _height;
	maxCycles = _maxCycles;
	int size = width*height;
	if (_numberOfThreads > size)	numberOfThreads = size;
	else if (_numberOfThreads>0)		numberOfThreads = _numberOfThreads;
	else							numberOfThreads = 1;
	int step = size / numberOfThreads;
	for (int i = 0; i < size; i++)
	{
		bool btemp = rand() % 2;
		field temp = { btemp,dead,btemp };
		fields.push_back(temp);
	}
	cycle = -1;
	doStep();
}

GameOfLife::GameOfLife(int _width, int _height, int _maxCycles, int _numberOfThreads)
{
	srand(time(NULL));
	realConstructor(_width, _height, _maxCycles,  _numberOfThreads);
}

GameOfLife::GameOfLife(int _width, int _height)
{
	srand(time(NULL));
	realConstructor(_width, _height, 0, (rand() % ((_width*_height) - 1)) + 1);
}

bool GameOfLife::doStep(int number)
{
	bool _return = false;
	int size = width*height;
	int step = size / numberOfThreads;
	for (int j = 0; j<number; j++)
	{
		if (cycle++ < maxCycles && maxCycles>0)
		{
			_return = true;
			int i;
			for (i = 0; i < numberOfThreads - 1; i++)
				threadList.push_back(std::thread(&GameOfLife::saveStates, this, i*step, (i + 1)*step));
			threadList.push_back(std::thread(&GameOfLife::saveStates, this, i*step, size));
			for (int i = 0; i < numberOfThreads; i++)
				threadList[i].join();
			threadList.clear();

			for (i = 0; i < numberOfThreads - 1; i++)
				threadList.push_back(std::thread(&GameOfLife::changeStates, this, i*step, (i + 1)*step));
			threadList.push_back(std::thread(&GameOfLife::changeStates, this, i*step, size));
			for (int i = 0; i < numberOfThreads; i++)
				threadList[i].join();
			threadList.clear();
		}
		else
			break;
	}
	return _return;
}

bool GameOfLife::doStep()
{
	return doStep(1);
}

void GameOfLife::reserveMemoryForPixels(int pixelOnPixel)
{
	pixels = new uint8_t**[height*pixelOnPixel];
	//pixels= (uint8_t***)malloc(height*pixelOnPixel * sizeof(uint8_t**));
	for (int i = 0; i < height*pixelOnPixel; i++)
	{
		pixels[i] = new uint8_t*[width*pixelOnPixel];
		//pixels[i] = (uint8_t**)malloc(width*pixelOnPixel * sizeof(uint8_t*));
		for (int j = 0; j < width*pixelOnPixel; j++)
			pixels[i][j] = new uint8_t[4];
			//pixels[i][j]=(uint8_t*)malloc(4 * sizeof(uint8_t));
	}
}

void GameOfLife::freeMemoryForPixels(int pixelOnPixel)
{
	for (int i = 0; i < height*pixelOnPixel; i+=pixelOnPixel)
	{
		for (int j = 0; j < width*pixelOnPixel; j++)
			delete [] pixels[i][j];
		delete [] pixels[i];
	}
	delete [] pixels;
	pixels = NULL;
}

void GameOfLife::updatePixels(int pixelOnPixel)
{
	uint8_t black[4] = { 0,0,0,1 };
	uint8_t white[4] = { 255,255,255,1 };

	int l;
	for (int i = 0; i < height; i++)
	{
		l = 0;
		for (int j=0; j<width;j++)
		{
			if (fields[(width*i) + j].prev) 
				for (int k = 0; k < pixelOnPixel; k++)
				{
					for (int m = 0; m < 4; m++)
						pixels[(i*pixelOnPixel)+l][(j*pixelOnPixel) +k ][m] = black[m];
				}
			else							
				for (int k = 0; k < pixelOnPixel; k++)
				{
					for (int m = 0; m < 4; m++)
						pixels[(i*pixelOnPixel)+l][(j*pixelOnPixel) + k][m] = white[m];
				}
		}
		for (l = 1; l < pixelOnPixel; l++)
			pixels[(i*pixelOnPixel) + l] = pixels[(i*pixelOnPixel)];
	}
}

void GameOfLife::makeGif(char *name, int timeInterval, int pixelOnPixel)
{
	cout << "Start making gif file\n";
	reserveMemoryForPixels(pixelOnPixel);
	GifBegin(&Gif, name, width*pixelOnPixel, height*pixelOnPixel, timeInterval, 8, 0);

	uint8_t tab[xxx][yyy][4];
	do
	{
		updatePixels(pixelOnPixel);
		for (int i = 0; i<height*pixelOnPixel; i++)
			for (int j = 0; j<width*pixelOnPixel; j++)
			{
				for (int m = 0; m < 4; m++)
					tab[i][j][m] = pixels[i][j][m];
			}

		GifWriteFrame(&Gif, **tab, width*pixelOnPixel,height*pixelOnPixel, timeInterval, 8, 0);
	} while (doStep());
	GifEnd(&Gif);
	freeMemoryForPixels(pixelOnPixel);
	reset();
}

void GameOfLife::reset()
{
	cycle = 0;
	int size = width*height;
	int step = size / numberOfThreads;
	int i = 0;
	for (i = 0; i < numberOfThreads - 1; i++)
		threadList.push_back(std::thread(&GameOfLife::reset2, this, i*step, (i + 1)*step));
	threadList.push_back(std::thread(&GameOfLife::reset2, this, i*step, size));
	for (int i = 0; i < numberOfThreads; i++)
		threadList[i].join();
	threadList.clear();
}

void GameOfLife::reset2(int start, int end)
{
	for (int i = start; i<end; i++)
		fields[i].prev = fields[i].initial;
}

void GameOfLife::saveStates(int start, int end)
{
	for (int i=start;i<end;i++)
		fields[i].prev = fields[i].actual;
}

void GameOfLife::changeStates(int start, int end)
{
	for (int i = start; i<end; i++)
	{
		int x = i % width;
		int y = i / height;
		int sumOfLiving = 0;
		for (int j=-horizon; j<= horizon;j++)
			for (int k = -horizon; k <= horizon; k++)
			{
				if (j || k)
				{
					int neighbor_x = x + j;
					int neighbor_y = y + k;
					if (neighbor_x < 0)				neighbor_x = width + j;
					else if (neighbor_x >= width)	neighbor_x = j - 1;
					if (neighbor_y < 0)				neighbor_y = height + k;
					else if (neighbor_y >= height)	neighbor_y = k - 1;
					if (fields[(width*neighbor_y) + neighbor_x].prev)sumOfLiving++;
				}
			}
		if (fields[i].prev)
		{
			if (sumOfLiving>=2 && sumOfLiving <=3)	fields[i].actual = live;
			else									fields[i].actual = dead;
		}
		else  if (sumOfLiving == 3) fields[i].actual = live; 

	}
}

GameOfLife::~GameOfLife()
{
	if (!threadList.empty())
	{
		for (int i = 0; i < threadList.size(); i++)
			threadList[i].join();
		threadList.clear();
	}
	if (!fields.empty())
			fields.clear();
}

void GameOfLife::print()
{


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (fields[(width*i) + j].prev)	cout << "X";
			else								cout << " ";
		}
		cout << "\n";
	}
}