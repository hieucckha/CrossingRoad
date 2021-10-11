#include "Game.h"

#include <iostream>
#include <thread>
#include <conio.h>

char MOVING;
Game* game;

void SubThread()
{
	while (g_isRunning)
	{
		if (!game->getPlayer().isDead())
			game->updatePosPeople(MOVING);

		MOVING = ' ';
		game->updatePosAnimal();
		game->updatePosVehicle();
		game->drawGame();

		if (game->getPlayer().isImpact(game->getVehicle()) || game->getPlayer().isImpact(game->getAnimal()))
		{

			ClearConsoleScreen();
			std::cout << "Your Died\n";
			return;
		}
		if (game->getPlayer().isFinish())
		{
			ClearConsoleScreen();
			std::cout << "You Finish\n";
			return;
		}

		Sleep(17);
	}
}

void main()
{
	game = new Game();
	int tmp = 0;

	FixConsoleWindow();
	ShowConsoleCursor(false);

	game->startGame();
	std::thread t1(SubThread);
	while (true)
	{
		tmp = toupper(_getch());
		if (!game->getPlayer().isDead())
		{
			if (tmp == 27)
			{
				game->exitGame(t1);
				return;
			} else if (tmp == 'P')
				game->pauseGame(t1.native_handle());
			else
			{
				game->resumeGame(t1.native_handle());
				MOVING = tmp;
			}
		} else
		{
			if (tmp == 'Y')
				game->startGame();
			else
			{
				game->exitGame(t1);
				return;
			}
		}
	}
}