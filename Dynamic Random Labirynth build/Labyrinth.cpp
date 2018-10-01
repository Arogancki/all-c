#include "stdafx.h"
#include "Labyrinth.h"
#include <conio.h>
#ifdef WIN32 || WIN64
#include <windows.h>
#else
#include <unistd.h>
#endif

// co sie stanie jak watek wywola join na siebie - czekanie 4ever?

Labyrinth::Labyrinth(int _width,int _height)
{
	width = _width;
	height=_height;
	if (width < 4)
		width = 4;
	if (height < 4)
		height = 4;
	if (width > 80)
		width = 80;
	if (height > 80)
		height = 80;
	fields = new field*[width];
	for (int i = 0; i < width; ++i)
	{
		fields[i] = new field[height];
		for (int j = 0; j < height; j++)
		{
			fields[i][j].mutex.lock();
			fields[i][j].type = 0;
			fields[i][j].mutex.unlock();
		}
	}
	srand(time(NULL));
	int x=rand() % width;
	int y = rand() % height;
	build_labyrinth(-1,-1,x,y);
	shortestWayToFinish= findFarestRoom(x, y);
	fields[x][y].type = 6; // start
	std::vector<int> neighborsX = { 1, 0, -1,  0 };
	std::vector<int> neighborsY = { 0, 1,  0, -1 };
	for (int i=shortestWayToFinish.size()-1;i>=0;i--)
	{
		x = x + neighborsX[shortestWayToFinish[i]];
		y = y + neighborsY[shortestWayToFinish[i]];
	}
	fields[x][y].type = 5; // meta
	solved = 0;
}

void Labyrinth::threadTake(int x, int y, int delay, bool isplayer)
{
	solvedMutex.lock();
	if (!solved)
	{
		solvedMutex.unlock();
		if (isplayer)
		{
			fields[x][y].mutex.lock();
			fields[x][y].type = 7;
			fields[x][y].mutex.unlock();
		}
		else
		{
			fields[x][y].mutex.lock();
			fields[x][y].type = 2;
			fields[x][y].mutex.unlock();
		}
		// printing
		if (printMutex.try_lock())
		{
			std::cout << print();
			printMutex.unlock();
		}

		// wait delay time before create new children
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));

		std::vector<int> neighborsX = { 1, 0, -1,  0 };
		std::vector<int> neighborsY = { 0, 1,  0, -1 };
		solvedMutex.lock();
		while (neighborsX.size() > 0 && (!solved))
		{
			solvedMutex.unlock();
			int _rand = rand() % neighborsX.size();
			if (is(x + neighborsX[_rand], y + neighborsY[_rand], 1)==1)
			{
				threadMutex.lock();
				threadList.push_back(std::thread(&Labyrinth::threadTake, this, x + neighborsX[_rand], y + neighborsY[_rand], delay,0));
				threadMutex.unlock();
			}
			else if (is(x + neighborsX[_rand], y + neighborsY[_rand], 4) == 1)
			{
				threadMutex.lock();
				threadList.push_back(std::thread(&Labyrinth::threadTake, this, x + neighborsX[_rand], y + neighborsY[_rand], delay,1));
				threadMutex.unlock();
			}
			else if (is(x + neighborsX[_rand], y + neighborsY[_rand], 5)==1)
			{
				solvedMutex.lock();
				solved = -1;
				solvedMutex.unlock();
				fields[x + neighborsX[_rand]][y + neighborsY[_rand]].mutex.lock();
				fields[x + neighborsX[_rand]][y + neighborsY[_rand]].type = 3;
				fields[x + neighborsX[_rand]][y + neighborsY[_rand]].mutex.unlock();
				// printing
				printMutex.lock();
				std::cout << print();
				printMutex.unlock();
			}
			neighborsX.erase(neighborsX.begin() + _rand);
			neighborsY.erase(neighborsY.begin() + _rand);
			solvedMutex.lock();
		}
		solvedMutex.unlock();
	}
	else
		solvedMutex.unlock();
}

void Labyrinth::playerTake()
{
	int index;
	fields[player.x][player.y].mutex.lock();
	fields[player.x][player.y].type = 4;
	fields[player.x][player.y].mutex.unlock();

	std::vector<int> neighborsX = { 1, 0, -1,  0 ,0 };
	std::vector<int> neighborsY = { 0, 1,  0, -1 ,0 };
	int player_prev_x;
	int player_prev_y;
	char move;

	solvedMutex.lock();
	while (!solved)
	{
		solvedMutex.unlock();

		// printing
		if (printMutex.try_lock())
		{
			std::cout << print();
			printMutex.unlock();
		}

		move = _getch();
		switch (move)
		{
		case 'w':
			index = 3;
			break;
		case 'a':
			index = 2;
			break;
		case 's':
			index = 1;
			break;
		case 'd':
			index = 0;
			break;
		default:
			index = 4;
		}

		player_prev_x = player.x;
		player_prev_y = player.y;
		player.x += neighborsX[index];
		player.y += neighborsY[index];

		if (is(player.x, player.y, 1) == 1)
		{
			fields[player_prev_x][player_prev_y].mutex.lock();
			if (fields[player_prev_x][player_prev_y].type == 7)
				fields[player_prev_x][player_prev_y].type = 2;
			else
				fields[player_prev_x][player_prev_y].type = fields[player_prev_x][player_prev_y].type;
			fields[player_prev_x][player_prev_y].mutex.unlock();

			fields[player.x][player.y].mutex.lock();
			fields[player_prev_x][player_prev_y].type = fields[player.x][player.y].type;
			fields[player.x][player.y].type = 4;
			fields[player.x][player.y].mutex.unlock();

		}
		else if (is(player.x, player.y, 2) == 1)
		{
			fields[player_prev_x][player_prev_y].mutex.lock();
			if (fields[player_prev_x][player_prev_y].type == 7)
				fields[player_prev_x][player_prev_y].type = 2;
			else
				fields[player_prev_x][player_prev_y].type = fields[player_prev_x][player_prev_y].type;
			fields[player_prev_x][player_prev_y].mutex.unlock();

			fields[player.x][player.y].mutex.lock();
			fields[player_prev_x][player_prev_y].type = fields[player.x][player.y].type;
			fields[player.x][player.y].type = 7;
			fields[player.x][player.y].mutex.unlock();
		}
		else if (is(player.x, player.y, 5) == 1)
		{
			fields[player_prev_x][player_prev_y].mutex.lock();
			if (fields[player_prev_x][player_prev_y].type == 7)
				fields[player_prev_x][player_prev_y].type = 2;
			else
				fields[player_prev_x][player_prev_y].type = fields[player_prev_x][player_prev_y].type;
			fields[player_prev_x][player_prev_y].mutex.unlock();

			fields[player.x][player.y].mutex.lock();
			fields[player_prev_x][player_prev_y].type = fields[player.x][player.y].type;
			fields[player.x][player.y].type = 3;
			fields[player.x][player.y].mutex.unlock();

			solvedMutex.lock();
			solved = 1;
			solvedMutex.unlock();
		}
		else
		{
			player.x -= neighborsX[index];
			player.y -= neighborsY[index];
		}

		solvedMutex.lock();
	}
	solvedMutex.unlock();
}

void Labyrinth::build_labyrinth(int parentX,int parentY,int x,int y)
{
	//std::cout << this->print();
	//getchar();
	fields[x][y].mutex.lock();
	fields[x][y].type = 1;
	fields[x][y].mutex.unlock();
	std::vector<int> neighborsX={ 1, 0, -1,  0 };
	std::vector<int> neighborsY={ 0, 1,  0, -1 };
	while (neighborsX.size()>0)
	{
		int _rand = rand() % neighborsX.size();
		if (x + neighborsX[_rand] == parentX && y + neighborsY[_rand] == parentY)
			;
		else
			if (is(x + neighborsX[_rand], y+ neighborsY[_rand],0)==1 && isNeighborsNot(x,y,x + neighborsX[_rand], y + neighborsY[_rand], 1)==1)
				build_labyrinth(x,y,x + neighborsX[_rand], y+ neighborsY[_rand]);
		neighborsX.erase(neighborsX.begin() + _rand);
		neighborsY.erase(neighborsY.begin() + _rand);
	}
	
}

std::vector<int> Labyrinth::findFarestRoom(int x, int y)
{
	std::vector<int> _return = findFarestRoomRec(-1, -1, x, y);
	_return.erase(_return.begin());
	return (_return);
}

std::vector<int> Labyrinth::findFarestRoomRec(int parentX, int parentY,int x, int y)
{
	std::vector<int> neighborsX = { 1, 0, -1,  0 };
	std::vector<int> neighborsY = { 0, 1,  0, -1 };
	std::vector<int> neighbors[4]={{},{},{},{}};
	for (int i = 0; i < 4;i++)
	{
		if (x + neighborsX[i] == parentX && y + neighborsY[i] == parentY) // no repetition
			;
		else
			if (is(x + neighborsX[i], y + neighborsY[i], 1) == 1)
			{
				std::vector<int> temp = findFarestRoomRec(x, y, x + neighborsX[i], y + neighborsY[i]);
				neighbors[i].insert(neighbors[i].end(), temp.begin(), temp.end());
			}
	}
	// find farest point for finish line
	int maxIndex = rand()%4;
	for (int i = 0; i < 4; i++)
		if (neighbors[maxIndex].size() < neighbors[i].size())
			maxIndex = i;
	neighbors[maxIndex].push_back(maxIndex);
	return neighbors[maxIndex];
}

void Labyrinth::gameStart(int delay)
{
	int i, j;
	// find start
	for (i = 0; i < width; ++i)
	{
		for (j = 0; j < height; j++)
		{
			if (is(i, j, 6) == 1)
			{
				goto out;
			}
		}
	}
out:
	player.counter = 0;
	player.x = i;
	player.y = j;
	std::cout << "Press ENTER";
	getchar();
	threadMutex.lock();
	threadList.push_back(std::thread(&Labyrinth::playerTake, this));
	threadList.push_back(std::thread(&Labyrinth::threadTake, this, i, j, delay, 1));
	threadMutex.unlock();
	killThreads();
	if (solved==1)
		std::cout << "\nWinner\n";
	else if (solved == -1)
		std::cout << "\nLosser\n";
	std::cout << "Press ENTER";
	getchar();
}

void Labyrinth::killThreads()
{
	threadMutex.lock();
	for (int i = 1; i<threadList.size(); i++)
	{
		threadMutex.unlock();
		threadList[i].join();
		threadMutex.lock();
	}
	threadMutex.unlock();
	threadList[0].join();
}

int Labyrinth::is(int x,int y, int n)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		fields[x][y].mutex.lock();
		if (fields[x][y].type == n)
		{
			fields[x][y].mutex.unlock();
				return 1; // equal n
		}
		fields[x][y].mutex.unlock();
		return 0; // equal not n
	}
	return -1; // unavailable
}

int Labyrinth::isNeighborsNot(int parentX, int parentY,int x, int y, int n)
{
	std::vector<int> neighborsX = { 1, 0, -1,  0 };
	std::vector<int> neighborsY = { 0, 1,  0, -1 };
	while (neighborsX.size()>0)
	{
		int _rand = rand() % neighborsX.size();
		if (x+neighborsX[_rand] == parentX && y+neighborsY[_rand] == parentY)
			;
		else
			if (is(x + neighborsX[_rand], y + neighborsY[_rand], n) == 1)
				return 0;
		neighborsX.erase(neighborsX.begin() + _rand);
		neighborsY.erase(neighborsY.begin() + _rand);
	}
	return 1;
}

std::string Labyrinth::print()
{
	char hardWallv = 'X';
	char hardWallh = 'X';
	char wall = 'X';
	char meta = 'O';
	char start = 'S';
	char player = '|';
	char room = ' ';
	char pAt = '!';
	char thread = '.';
	char threadOnMeta = '@';

	std::stringstream _return;
	for (int j = 0; j < width+2; j++)
		_return << hardWallh;
	_return << '\n'<<hardWallv;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			fields[j][i].mutex.lock();
			switch(fields[j][i].type)
			{
			case 0:
				_return << wall;
				break;
			case 1:
				_return << room;
				break;
			case 2:
				_return <<thread;
				break;
			case 3:
				_return << threadOnMeta;
				break;
			case 4:
				_return << player;
				break;
			case 5:
				_return << meta;
				break;
			case 6:
				_return << start;
				break;
			case 7:
				_return << pAt;
				break;
			}
			fields[j][i].mutex.unlock();
		}
		_return << hardWallv<<std::endl<< hardWallv;
	}
	for (int j = 0; j < width+1; j++)
		_return << hardWallh;
	_return << '\n';
	system("cls");
	return _return.str();
}

Labyrinth::~Labyrinth()
{
	for (int i = 0; i < width; i++)
	{
		if (fields[i]) delete[] fields[i];
	}
	if (fields)delete[] fields;
	shortestWayToFinish.clear();
	//killThreads();
	threadList.clear();
}