#include "Game.h"

#include <iostream>
#include <thread>
#include <conio.h>
#include <ctime>

char MOVING;
Game* game;
bool getchNext;

void SubThread()
{
	int deadBy = 0;
	while (g_isRunning)
	{
		if (!getchNext)
		{
			Sleep(50);
			continue;
		}

		if (g_isMainMenu)
		{
			game->mainMenu();
			continue;
		}
		if (g_isDeadMenu)
		{
			game->deadScene(deadBy);
			game->playerDead();
			getchNext = false;
			continue;
		}

		if (!game->getPlayer().isPlayerDead())
			game->updatePosPeople(MOVING);

		deadBy = 0;
		MOVING = ' ';
		game->updateRows();
		game->drawNormalGame();

		if ((deadBy = game->getPlayer().isImpact(game->getRow())))
		{
			deadBy--;
			game->setPlayerDead();
			game->resetLevel();
			g_isDeadMenu = true;
		}
		if (game->getPlayer().isAtFinishLine())
		{
			game->levelUp();
			game->resetGame();
			game->startGame();
		}

		Sleep(50);
	}
}

void main()
{
	game = new Game();
	getchNext = true;

	int tmp = 0;

	FixConsoleWindow();
	setConsoleFontSize();
	ResizeWindow();
	ShowConsoleCursor(false);

	game->playMusic();
	game->startGame();

	std::thread t1(SubThread);
	while (true)
	{
		tmp = toupper(_getch());

		if (g_isMainMenu)
		{
			g_isMainMenu = false;
			continue;
		}
		if (g_isPause)
		{
			g_isPause = false;
			game->resumeSystem(t1.native_handle());
		}
		if (g_isDeadMenu)
		{
			g_isDeadMenu = false;

			if (tmp == 'Y')
			{
				game->resetGame();
				game->startGame();
				game->playMusic();
			}
			else
				g_isRunning = false;

		}

		if (!game->getPlayer().isPlayerDead())
		{
			if (tmp == 27)
			{
				game->exitGame(t1);
				return;
			}
			else if (tmp == 'P')
			{
				game->pauseSystem(t1.native_handle());
				game->pauseGame();
				g_isPause = true;
				MOVING = tmp;
			}
			else
			{
				game->resumeSystem(t1.native_handle());
				MOVING = tmp;
			}
			if (tmp == 'T')
			{
				game->pauseSystem(t1.native_handle());
				game->loadGame();
				game->resumeSystem(t1.native_handle());
			}
			if (tmp == 'L')
			{
				game->pauseSystem(t1.native_handle());
				game->saveGame();
				game->resumeSystem(t1.native_handle());
			}
		}
		else
		{
			if (!g_isRunning)
			{
				game->exitGame(t1);
				game->stopMusic();
				return;
			}
		}
		getchNext = true;
	}
}