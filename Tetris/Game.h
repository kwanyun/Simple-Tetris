#pragma once
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Block.h"
#include <windows.h>

class Application
{
private:
	std::string userName;
	unsigned int score=0;
	unsigned int currentTime = 0;
	char map[12][10];
	bool blockGenerated=false;
	bool needUpdate = false;
	bool isOver = false;
public:
	Application(std::string = "anonymous user");
	void Run();
	void Render();
	Block* GenBlock(unsigned int genNum);
	bool CheckBlock(Block* theBlock ,int leftx=0, int upy=0 );
};