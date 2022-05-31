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
};