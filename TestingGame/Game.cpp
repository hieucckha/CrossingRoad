#include "Game.h"

Game::Game()
{
	listVehicle_ = new Vehicle[10];
	for (int i = 0; i < 10; ++i)
	{
		listVehicle_[i].move(i + 20, 15);
	}
}

void Game::drawBorder()
{
	ClearConsoleScreen();

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int row, col;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	col = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	// The top border
	for (int i = 0; i < (col / 3 * 2); ++i)
	{
		std::cout << '#';
	}

	std::cout << '\n';

	// The middle border
	for (int i = 0; i < row - 2; ++i)
	{
		for (int j = 0; j < (col / 3 * 2); ++j)
		{
			if (j == 0 || j == (col / 3 * 2 - 1))
				std::cout << '#';
			else
				std::cout << ' ';
		}
		std::cout << '\n';
	}

	// The bottom border
	for (int i = 0; i < (col / 3 * 2); ++i)
	{
		std::cout << '#';
	}
}

void Game::drawNormalGame()
{
	GotoXY(this->player_.getX(), this->player_.getY());
	std::cout << "P";

	for (int i = 0; i < 10; ++i)
	{
		int x = this->listVehicle_[i].getX(), y = this->listVehicle_[i].getY();
		GotoXY(x, y);
		std::cout << 'V';
	}
}

Player Game::getPlayer() const
{
	return player_;
}

Vehicle* Game::getVehicle() const
{
	return listVehicle_;
}

void Game::exitGame(std::thread& t)
{
	ClearConsoleScreen();
	g_isRunning = false;
	t.join();
}

void Game::startGame()
{

}

void Game::resumeGame(std::thread& t)
{

}

void Game::updatePosPeople(char moving)
{
	if (moving == 'W')
		this->player_.Up(1);
	else if (moving == 'A')
		this->player_.Left(1);
	else if (moving == 'S')
		this->player_.Down(1);
	else if (moving == 'D')
		this->player_.Right(1);
}

void Game::updatePosVehicle()
{

}

void Game::clearPrevPeople()
{
	int x = this->getPlayer().getX(), y = this->getPlayer().getY();
	GotoXY(x, y);
	std::cout << ' ';
}

void Game::clearPrevVehicle()
{
	for (int i = 0; i < 10; ++i)
	{
		int x = this->listVehicle_[i].getX(), y = this->listVehicle_[i].getY();
		GotoXY(x, y);
		std::cout << ' ';
	}
}
