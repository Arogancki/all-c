#pragma once
#include <vector>
#include <mutex>
#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>

typedef struct field
{
	int type;
	std::mutex mutex;
};

typedef struct user
{
	int counter, x, y;
};

class Labyrinth
{
public:
	Labyrinth(int, int);
	~Labyrinth();
	std::string print();
	void gameStart(int);
private:
	field** fields;
	std::vector<int> shortestWayToFinish;
	std::vector<std::thread> threadList;

	int width;
	int height;
	int solved;
	std::mutex threadMutex;
	std::mutex solvedMutex;
	std::mutex printMutex;
	user player;

	void threadTake(int, int,int,bool);
	void playerTake();
	void build_labyrinth(int,int,int, int); // labyrinth initial, take last build field indexes
	std::vector<int> findFarestRoom(int,int); 
	std::vector<int> findFarestRoomRec(int,int,int,int); 
	void killThreads();
	int is(int,int,int);
	int isNeighborsNot(int,int,int,int,int);
};

