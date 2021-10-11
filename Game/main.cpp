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
		if (g_isDeadMenu)
		{
			game->drawDeadMenu();
			continue;
		}

		if (!game->getPlayer().isDead())
			game->updatePosPeople(MOVING);

		MOVING = ' ';
		game->updatePosAnimal();
		game->updatePosVehicle();
		game->drawGame();

		// Dead AAAAAAAAAA
		if (game->getPlayer().isImpact(game->getVehicle()) || game->getPlayer().isImpact(game->getAnimal()))
		{
			// Don't know why the state not set to false, scope
			game->setPlayerDead();
			game->resetLevel();
			g_isDeadMenu = true;
		}
		if (game->getPlayer().isFinish())
		{
			game->levelUp();
			game->resetGame();
			game->startGame();
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
			{
				game->resetGame();
				game->startGame();
			}
			else
			{
				game->exitGame(t1);
				return;
			}
		}
	}
}