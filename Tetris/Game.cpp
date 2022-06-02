#include "Game.h"

Application::Application(std::string name)
	:userName(name), currentTime(std::chrono::steady_clock::now()) {
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
	//random block init
	Block* currentBlock = Application::GenBlock(0);
	while (true)
	{
		//move block
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()- currentTime).count() > 1000)
		{
			currentTime = std::chrono::steady_clock::now();
			//if block current, move down
			if (blockGenerated)
			{
				//move block one step down if possible
				BlockMove(currentBlock, 1, 0);
			}
			//if block is not generated yet, generate
			else
			{
				currentBlock = Application::GenBlock(3);
			}
		}

		//check key
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			BlockMove(currentBlock, 0, -1);
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			BlockMove(currentBlock, 0, 1);
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			BlockMove(currentBlock, 1, 0);
		}
		else if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			//RotateBlock(currentBlock);
		}
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			isOver = true;
		}

		//check end
		if (isOver)
		{
			system("cls");
			std::cout << "Game END" << std::endl;
			return ;
		}

		//render
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
	
	if (!CheckBlock(mBlock))
	{
		isOver = true;
		delete mBlock;
		return NULL;
	}
	else
		return mBlock;
}

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


bool Application::CheckBlock(Block* theBlock , int row , int col )
{
	for (int i = 0; i < theBlock->rows; i++)
	{
		for (int j = 0; j < theBlock->columns; j++)
		{
			if ((map[theBlock->curR + row + i][theBlock->curC + col + j] != ' ' && theBlock->blockIn[3 * (i + row) + (j + col)] != '@')
					&& theBlock->blockIn[3 * i + j] != ' ')
				return false;
		}
	}
	return true;
	
}

void Application::BlockMove(Block* theBlock, int row, int col)
{
	needUpdate = true;
	//move block one step if possible
	if (CheckBlock(theBlock,  row,  col))
	{
		DelBlockFromMap(theBlock);
		theBlock->curR = theBlock->curR + row;
		theBlock->curC = theBlock->curC + col;
		AddBlockToMap(theBlock);
	}
	else
	{
		//Add Block to map for rendering
		AddBlockToMap(theBlock);
		//release memory
		delete theBlock;
		blockGenerated = false;
	}
}