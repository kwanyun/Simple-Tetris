#include "Game.h"

int main()
{
	std::cout << "Enter user name" << std::endl;
	std::string name;
	std::cin >> name;
	Application game(name);
	game.Run();

}