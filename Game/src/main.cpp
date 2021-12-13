#include "GameMain/Game.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>

Game* game;

int main()
{
	srand((unsigned int)time(nullptr));

	MoveWindow(GetConsoleWindow(), 10, 10, 1280, 720, TRUE);
	FixConsoleWindow();
	ShowConsoleCursor(false);

	game = new Game();
	game->Menu();
	
	delete game;

	_getch();
	return 0;
}