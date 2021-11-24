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
			//!!!!DEBUG_ONLY!!!!
			game->drawDeadMenu();
			std::cin.ignore();	//Should be pause and let the player choose
			std::cin;			//instead of cin
			g_isDeadMenu = false;
			game->resetGame();
			continue;
			//!!!!END_OF_DEBUG!!!!
		}

		if (!game->getPlayer().isPlayerDead())
			game->updatePosPeople(MOVING);

		MOVING = ' ';
		/*game->updatePosAnimal();
		game->updatePosVehicle();*/
		game->drawGame();

		// Dead AAAAAAAAAA
		//if (game->getPlayer().isImpact(game->getVehicle()) || game->getPlayer().isImpact(game->getAnimal()))
		//{
		//	// Don't know why the state not set to false, scope
		//	game->setPlayerDead();
		//	game->resetLevel();
		//	g_isDeadMenu = true;
		//}
		if (game->getPlayer().isAtFinishLine())
		{
			game->levelUp();
			game->resetGame();
			game->startGame();
		}

		//Redo the impact checking

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
		if (tmp == 'T')
		{
			game->pauseGame(t1.native_handle());
			if (game->loadGame() == true)
			{
				game->resetGame();
				game->startGame();
			}
			else
				game->resumeGame(t1.native_handle());
		}
		if (tmp == 'L')
		{
			game->pauseGame(t1.native_handle());
			game->resumeGame(t1.native_handle());
		}
		if (!game->getPlayer().isPlayerDead())
		{
			if (tmp == 27)
			{
				game->exitGame(t1);
				return;
			}
			else if (tmp == 'P')
				game->pauseGame(t1.native_handle());
			else
			{
				game->resumeGame(t1.native_handle());
				MOVING = tmp;
			}
		}
		else
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
		if (tmp == 'O')
		{
			game->setPlayerDead();
			game->resetLevel();
			g_isDeadMenu = true;
		}
	}
}