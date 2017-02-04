#pragma once
#include <vector>
#include <thread>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdlib.h>
#include <iostream>

namespace std{
	class mutex;
}

using std::cout;

#define xxx 480
#define yyy 480

#define dead false
#define live true
#define horizon 1

struct field
{
	bool actual;
	bool prev;
	bool initial;
	//std::mutex mux;
};
struct GifWriter
{
	FILE* f;
	uint8_t* oldImage;
	bool firstFrame;
};
class GameOfLife
{
public:
	GameOfLife(int width, int height, int maxCycles,int numberOfThreads);
	GameOfLife(int width, int height);
	~GameOfLife(); 
	void print();
	bool doStep(int number);
	bool doStep();
	void makeGif(char *name, int timeInterval, int pixelOnPixel);
	void reset();
private:
	GifWriter Gif;
	uint8_t ***pixels;
	void realConstructor(int width, int height, int maxCycles, int numberOfThreads);
	void reserveMemoryForPixels(int pixelOnPixel);
	void freeMemoryForPixels(int pixelOnPixel);
	void updatePixels(int pixelOnPixel);
	std::vector<std::thread> threadList;
	std::vector<field> fields;
	int width, height,cycle,maxCycles;
	int numberOfThreads;
	void saveStates(int start, int end);
	void changeStates(int start, int end);
	void reset2(int,int);
};