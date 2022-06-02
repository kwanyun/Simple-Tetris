#pragma once
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Block.h"
#include <windows.h>
#include <chrono>
#include <thread>
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
	void AddBlockToMap(Block* currentBlock);
	void DelBlockFromMap(Block* currentBlock);
	void BlockMove(Block* theBlock, int leftx = 0, int upy = 0);
	bool CheckBlock(Block* theBlock ,int leftx=0, int upy=0 );
};