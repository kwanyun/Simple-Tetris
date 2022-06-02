#pragma once
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>

#include "Block.h"

#include <chrono>
#include <thread>

#define WALL 10
#define FLOOR 11
#define AIR 13

class Application
{
private:
	std::string userName;
	unsigned int score=0;
	std::chrono::steady_clock::time_point currentTime;

	char map[12][12];
	bool blockGenerated=false;
	bool needUpdate = false;
	bool isOver = false;

public:
	Application(std::string ="anonymous user");
	void Run();
	void Render();
	Block* GenBlock(unsigned int genNum);
	void CheckKey(Block* currentBlock);
	void AddBlockToMap(Block* currentBlock);
	void DelBlockFromMap(Block* currentBlock);
	void BlockMove(Block* theBlock, int leftx = 0, int upy = 0);
	unsigned int CheckBlock(Block* theBlock ,int leftx=0, int upy=0 );
};