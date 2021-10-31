#include "Game.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

Game* game;

int main()
{
	srand((unsigned int)time(NULL));

	MoveWindow(GetConsoleWindow(), 10, 10, 1280, 720, TRUE);
	FixConsoleWindow();
	ShowConsoleCursor(false);

	game = new Game();
	game->Menu();
	
	delete game;
	return 0;
}