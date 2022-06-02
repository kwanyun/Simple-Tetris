#pragma once
#include <array>

class Block
{
private:
	int typenum;

public:
	Block(int n);

	inline int GetType() { return typenum; }
	void Rotate();
	int rows=3;
	int columns=3;
	int curR = 0;
	int curC = 1;
	std::array<int,9> blockIn;
};