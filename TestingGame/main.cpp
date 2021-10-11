#include "Game.h"

#include <iostream>
#include <thread>
#include <conio.h>

char MOVING;
Game* game;

void subThread()
{
	bool isStarting = true;
	while (g_isRunning)
	{
		if (!game->getPlayer().isDead())
		{
			if (isStarting)
			{
				game->drawBorder();
				isStarting = false;
			}

			game->clearPrevPeople();
			game->updatePosPeople(MOVING);
		}

		MOVING = ' ';
		game->clearPrevVehicle();
		game->updatePosVehicle();

		game->drawGame();

		if (game->getPlayer().isImpact(game->getVehicle()))
		{
			ClearConsoleScreen();
			std::cout << "You died\n";
			break;
		}
		if (game->getPlayer().isFinish())
		{
			ClearConsoleScreen();
			std::cout << "You finish\n";
			break;
		}

		Sleep(1);
	}
}

int main()
{
	game = new Game();

	int temp;

	FixConsoleWindow();
	ShowConsoleCursor(false);
	game->startGame();

	std::thread t1(subThread);

	while (true)
	{
		temp = toupper(_getch());
		if (!game->getPlayer().isDead())
		{
			if (temp == 27)
			{
				game->exitGame(t1);
				ClearConsoleScreen();
				return 0;
			} else
			{
				game->resumeGame(t1);
				MOVING = temp;
			}
		} else
		{
			game->exitGame(t1);
			return 0;
		}
	}

	return 0;
}