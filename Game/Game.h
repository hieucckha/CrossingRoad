#pragma once
#include "Animal.h"
#include "Vehicle.h"
#include "Player.h"
#include "Win32Helper.h"

#include "Windows.h"
#include <iostream>
#include <thread>
#include <vector>
#include <cstring>

static bool g_isRunning = true;
static bool g_isPause = false;
static bool g_isMenu = true;


class Game
{
private:
	std::vector<Animal*> listAnimal_;
	std::vector<Vehicle*> listVehicle_;

	Player player_;

	char PrevBuffer[30][120];
	char Buffer[30][120];
public:
	Game()
	{
		memset(PrevBuffer, (int)' ', 120 * 30);
		memset(Buffer, (int)' ', 120 * 30);
	}

	~Game()
	{
	}

	void drawGame()
	{
		//ClearConsoleScreen();
		int row = 30, col = 120;

		for (int r = 0; r < row; ++r)
		{
			for (int c = 0; c < col - 40; ++c)
			{
				if (r == 0 || r == row - 1)
				{
					Buffer[r][c] = '#';
				} else if (r % 5 == 0)
				{
					if (c == 0 || c == col - 41)
					{
						Buffer[r][c] = '#';
						Buffer[r][c + 1] = '\n';
					} else
						Buffer[r][c] = '_';
				} else
				{
					if (c == 0 || c == col - 41)
					{
						Buffer[r][c] = '#';
						Buffer[r][c + 1] = '\n';
					} else
						Buffer[r][c] = ' ';
				}
			}
		}

		for (size_t i = 0; i < listVehicle_.size(); ++i)
		{
			if (listVehicle_[i]->getY() == 22)
				Buffer[listVehicle_[i]->getY()][listVehicle_[i]->getX()] = 'C';
			else if (listVehicle_[i]->getY() == 17)
				Buffer[listVehicle_[i]->getY()][listVehicle_[i]->getX()] = 'T';
		}

		for (size_t i = 0; i < listAnimal_.size(); ++i)
		{
			if (listAnimal_[i]->getY() == 12)
				Buffer[listAnimal_[i]->getY()][listAnimal_[i]->getX()] = 'D';
			else if (listAnimal_[i]->getY() == 7)
				Buffer[listAnimal_[i]->getY()][listAnimal_[i]->getX()] = 'B';
		}

		Buffer[player_.getY()][player_.getX()] = 'P';

		for (size_t row = 0; row < 30; ++row)
		{
			for (size_t col = 0; col < 120; ++col)
			{
				if (Buffer[row][col] == PrevBuffer[row][col])
					continue;

				GotoXY(col, row);
				std::cout << Buffer[row][col];
			}
		}

		std::cout.flush();
		std::memcpy((char*)PrevBuffer, (char const*)Buffer, 120 * 30);
	}

	Player getPlayer() const
	{
		return player_;
	}

	std::vector<Animal*> getAnimal()
	{
		return listAnimal_;
	}

	std::vector<Vehicle*> getVehicle()
	{
		return listVehicle_;
	}

	void resetGame()
	{

	}

	void exitGame(std::thread& thd)
	{
		g_isRunning = false;
		ClearConsoleScreen();
		thd.join();
	}

	void startGame()
	{
		g_isRunning = true;

		// if level
		// 5 Car, 5 Truck
		// Car
		for (int i = 0; i < 5; ++i)
			listVehicle_.push_back(new Car(35 + i * 2, 22));
		for (int i = 0; i < 5; ++i)
			listVehicle_.push_back(new Truck(35 + i * 2, 17));

		for (int i = 0; i < 5; ++i)
			listAnimal_.push_back(new Dinosaur(35 + i * 2, 12));
		for (int i = 0; i < 5; ++i)
			listAnimal_.push_back(new Bird(35 + i * 2, 7));

		player_.move(39, 27);
	}

	void loadGame(std::istream stream)
	{

	}

	void saveGame(std::istream stream)
	{

	}

	void pauseGame(HANDLE hd)
	{

	}

	void resumeGame(HANDLE hd)
	{

	}

	void updatePosPeople(char moveKey)
	{
		if (moveKey == 'W')
			player_.Up(1);
		else if (moveKey == 'A')
			player_.Left(1);
		else if (moveKey == 'S')
			player_.Down(1);
		else if (moveKey == 'D')
			player_.Right(1);
	}

	void updatePosVehicle()
	{

	}

	void updatePosAnimal()
	{

	}


};