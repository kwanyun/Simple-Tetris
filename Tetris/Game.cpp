#include "Game.h"

 Application::Application(std::string name)
	:userName(name), currentTime(time(NULL)) {
	 for (int i = 0; i < 12; i++)
	 {
		 for (int j = 0; j < 10; j++)
		 {
			 if (j == 0 || j == 9) map[i][j] = 'l';
			 else if (i == 11) map[i][j] = '_';
			 else map[i][j] = ' ';
		 }
	 }
 }

void Application::Run()
{
	//random block init
	Block* currentBlock= Application::GenBlock(currentTime % 5);
	blockGenerated = true;
	while (true)
	{
		//move block
		if (currentTime - time(NULL) > 0)
		{
			needUpdate = true;
			currentTime = time(NULL);
			//if block current, move down
			if (blockGenerated)
			{
				//get block one step down
				if (CheckBlock(currentBlock, currentBlock->curR+1, currentBlock->curC ))
				{

				}
				else 
				{
					currentBlock->curR++;
				}
			}
			//if block is not generated, generate
			else
			{
				currentBlock = Application::GenBlock(currentTime%5);
			}
		}

		//check key
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			needUpdate = true;
		}
		else if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{ 
			needUpdate = true;
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			needUpdate = true;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			needUpdate = true;

		}
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			needUpdate = true;
		}
		//check end
		if (isOver)
		{
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
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
};

Block* Application::GenBlock(unsigned int genNum)
{
	Block* mBlock = new Block(genNum);
	//random generation of the block with time

	if (!CheckBlock(mBlock))
	{
		isOver = true;
		delete mBlock;
	}
	else
	return mBlock;
}

bool Application::CheckBlock(Block* theBlock , int leftx , int upy )
{
	for (int i = 0; i < theBlock->rows; i++)
	{
		for (int j = 0; j < theBlock->columns; j++)
		{
			if (map[leftx + i][upy + j] != ' ' || theBlock->blockIn[i + 3 * j] != ' ')
				return false;
		}
	}
	
}