#include "Block.h"

Block::Block(int n) : typenum(n)
{
	if (n == 0)
	{
		blockIn = { ' ', '@', ' ', '@', '@', '@', ' ', ' ', ' ' };
		rows = 2;
		columns = 3;
	}
	else if (n == 1)
	{
		blockIn = { '@',' ',' ','@','@','@', ' ', ' ', ' ' };
		rows = 2;
		columns = 3;
	}
	else if (n == 2)
	{
		blockIn = { ' ','@','@','@','@',' ' , ' ', ' ', ' ' };
		rows = 2;
		columns = 3;
	}
	else if (n == 3)
	{
		blockIn = { '@', '@', ' ', '@', '@', ' ', ' ', ' ', ' ' };
		rows = 2;
		columns = 2;
	}
	else if (n == 4)
	{
		blockIn = { '@', ' ', ' ', '@', ' ', ' ', '@', ' ', ' ' };
		rows = 3;
		columns = 1;
	}
}

void Block::Rotate()
{
	int temp = rows;
	rows = columns;
	columns = temp;

	std::array<int, 9> tempBlockIn = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tempBlockIn[3*j+i] = blockIn[3*i+j];
		}
	}
	blockIn = tempBlockIn;
}