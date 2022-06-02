#include "Game.h"

using namespace std::chrono;

Application::Application(std::string name)
	:userName(name), currentTime(steady_clock::now()) {
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (j == 0 || j == 11) map[i][j] = 'l';
			else if (i == 11) map[i][j] = '-';
			else map[i][j] = ' ';
		}
	}
}

void Application::Run()
{
	auto start = steady_clock::now();
	//random block init
	Block* currentBlock = Application::GenBlock(0);
	while (true)
	{
		CheckKey(currentBlock);		

		if (std::chrono::duration_cast<milliseconds>(steady_clock::now() - currentTime).count() > 1000)
		{
			score += duration_cast<milliseconds>(steady_clock::now() - currentTime).count() / 7;
			currentTime = steady_clock::now();
			if (blockGenerated)
				BlockMove(currentBlock, 1, 0);
			else
				currentBlock = Application::GenBlock(duration_cast<milliseconds>(steady_clock::now()-start).count() % 5);
		}
		//check if game end
		if (isOver||map[0][0]=='@'|| map[0][1] == '@')
		{
			system("cls");
			std::cout << "Game END" << std::endl
				<<"Your Score : "<<score<<std::endl; break;
		}
		BlockScore(currentBlock);
		if (needUpdate)
		{
			needUpdate = false;
			Application::Render();
		}
	}
};

void Application::Render()
{
	system("cls");
	std::cout << std::endl << std::endl;
	for (int i = 0; i < 12; i++)
	{
		std::cout << "\t";
		for (int j = 0; j < 12; j++)
		{
			std::cout << map[i][j];
		}
		if (i == 5)
		{
			std::cout << "\t\t" << "User Name : " << userName;
		}
		else if (i == 6)
		{
			std::cout << "\t\t" << "Your Score : " << score;
		}
		std::cout << std::endl;
	}
	std::cout<<std::endl << "Press ESC to end"<<std::endl;
};
//random generation of the block with time
Block* Application::GenBlock(unsigned int genNum)
{
	Block* mBlock = new Block(genNum);
	blockGenerated = true;
	needUpdate = true;
	
	if (CheckBlock(mBlock)==FLOOR)
	{
		isOver = true;
		blockGenerated = false;
		delete mBlock;
		return NULL;
	}
	else
		return mBlock;
}

//adding block in map to render later
void Application::AddBlockToMap(Block* currentBlock)
{
	for (int i = 0; i < currentBlock->rows; i++)
	{
		for (int j = 0; j < currentBlock->columns; j++)
		{
			if ((map[i+ currentBlock->curR][j + currentBlock->curC] == ' ') && (currentBlock->blockIn[3 * i + j] == '@'))
				map[i + currentBlock->curR][j + currentBlock->curC] = '@';
		}
	}
}
//removing block from the map to render later
void Application::DelBlockFromMap(Block* currentBlock)
{
	for (int i = 0; i < currentBlock->rows; i++)
	{
		for (int j = 0; j < currentBlock->columns; j++)
		{
			if ((map[i + currentBlock->curR][j + currentBlock->curC] == '@') && (currentBlock->blockIn[3 * i + j] == '@'))
				map[i + currentBlock->curR][j + currentBlock->curC] = ' ';
		}
	}
}


unsigned int Application::CheckBlock(Block* theBlock , int row , int col )
{
	DelBlockFromMap(theBlock);
	//check from the start to end
	int startR = theBlock->curR + row;
	int endR = theBlock->curR + row + theBlock->rows;
	int startC = theBlock->curC + col;
	int endC = theBlock->curC + col + theBlock->columns;

	//check if wall/floor/air
	for (int i = startR; i < endR; i++)
	{
		for (int j = startC; j < endC; j++)
		{
			if (theBlock->blockIn[3 * (i - theBlock->curR - row) + (j - theBlock->curC - col)] == ' ') continue;
			if (map[i][j] == 'l') return WALL;
			else if (map[i][j] == '-' || map[i][j] == '@') return FLOOR;
		}
	}
	return AIR;
}

//move if possible
void Application::BlockMove(Block* theBlock, int row, int col)
{
	needUpdate = true;
	//move block one step if possible
	if (CheckBlock(theBlock, row, col) == AIR)
	{
		theBlock->curR = theBlock->curR + row;
		theBlock->curC = theBlock->curC + col;
		AddBlockToMap(theBlock);
	}
	else if (CheckBlock(theBlock, row, col) == FLOOR)
	{
		//Add Block to map for rendering
		AddBlockToMap(theBlock);
		//release memory
		delete theBlock;
		blockGenerated = false;
	}
	else {//do nothing}
	}
}

void Application::CheckKey(Block* block)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x0001)
	{
		BlockMove(block, 0, -1);
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
	{
		BlockMove(block, 0, 1);
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x0001)
	{
		BlockMove(block, 1, 0);
	}
	else if (GetAsyncKeyState(VK_UP) & 0x0001)
	{
		needUpdate = true;
		DelBlockFromMap(block);
		block->Rotate();
	}
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
	{
		isOver = true;
	}
}

void Application::BlockScore(Block* block)
{
	bool getpoint = true;
	for (int i = 10; i >=0; i--)
	{
		getpoint = true;
		for (int j = 1; j < 11; j++)
		{
			if (map[i][j] == ' ') 
				getpoint = false;
		}
		if (getpoint)
		{
			needUpdate = true;
			getpoint = false;
			score += 10000;
			for (int k = 0; k < 12; k++)
			{
				if (map[i][k]=='@') map[i][k] = ' ';
			}
			for (int p = i; p > 1; p--)
			{
				for (int q = 1; q < 11; q++)
					map[p][q] = map[p-1][q];
			}
			block->curR += 1;
			DelBlockFromMap(block);
		}
	}
}
