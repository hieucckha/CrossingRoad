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
#include <cstdio>
#include <fstream>
#include <string>

static bool g_isRunning = false;
static bool g_isPause = false;
static bool g_isMenu = false;
static bool g_isDeadMenu = false;

class Game
{
private:
	std::vector<Animal*> listAnimal_;
	std::vector<Vehicle*> listVehicle_;

	Player player_;

	int level_;

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

	/// <summary>
	/// Display generated Buffer to the monitor
	/// </summary>
	void PrintBuffer()
	{
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

	/// <summary>
	/// Generate and display ALL elements of the game
	/// </summary>
	void drawGame()
	{
		//ClearConsoleScreen();
		int row = 30, col = 120;

		for (int i = 0; i < row; ++i)
			Buffer[i][col - 1] = '\n';

		for (int r = 0; r < row; ++r)
		{
			for (int c = 0; c < col - 40; ++c)
			{
				if (r == 0 || r == row - 1)
					Buffer[r][c] = '#';
				else if (r % 5 == 0)
				{
					if (c == 0 || c == col - 41)
						Buffer[r][c] = '#';
					else
						Buffer[r][c] = '_';
				} else
				{
					if (c == 0 || c == col - 41)
						Buffer[r][c] = '#';
					else
						Buffer[r][c] = ' ';
				}
			}
		}

		for (size_t i = 0; i < listVehicle_.size(); ++i)
		{
			listVehicle_[i]->drawSprite();
		}

		for (size_t i = 0; i < listAnimal_.size(); ++i)
		{
			listAnimal_[i]->drawSprite();
		}

		player_.drawSprite();

		snprintf((*(Buffer + 15) + 90), 14, "Level: %d", level_);
		PrintBuffer();
	}

	void drawDeadMenu()
	{
		/*
			################################
			#                              #
			#  Press Y to continue playing #
			#                              #
			################################
		*/

		char DeadMenu[5][33] = {
			{"################################"},
			{"#                              #"},
			{"#  Press Y to continue playing #"},
			{"#                              #"},
			{"################################"}
		};

		memcpy((*(Buffer + 1) + 30), (DeadMenu + 1), sizeof(DeadMenu[1]));

		for (int i = 0; i < 5; ++i)
			memcpy((*(Buffer + 15 + i) + 30), (DeadMenu + i), sizeof(DeadMenu[i]));

		PrintBuffer();
	}

	// ! Error, don't know why the dead not toggle
	void setPlayerDead()
	{
		player_.setState(false);
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

	void levelUp()
	{
		level_++;
	}

	void resetLevel()
	{
		level_ = 0;
	}

	void resetGame()
	{
		for (size_t i = 0; i < listAnimal_.size(); ++i)
			delete listAnimal_[i];
		listAnimal_.resize(0);

		for (size_t i = 0; i < listVehicle_.size(); ++i)
			delete listVehicle_[i];
		listVehicle_.resize(0);

		g_isDeadMenu = false;
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
		player_.setState(true);

		//Temporarily disabled for sprite testing
		// if level
		// 5 Car, 5 Truck
		// Car
		/*for (int i = 0; i < 5; ++i)
			listVehicle_.push_back(new Car(35 + i * 2, 22));
		for (int i = 0; i < 5; ++i)
			listVehicle_.push_back(new Truck(35 + i * 2, 17));

		for (int i = 0; i < 5; ++i)
			listAnimal_.push_back(new Dinosaur(35 + i * 2, 12));
		for (int i = 0; i < 5; ++i)
			listAnimal_.push_back(new Bird(35 + i * 2, 7));*/

		listVehicle_.push_back(new Car(39, 22, Buffer));
		listVehicle_.push_back(new Truck(39, 17, Buffer));
		listAnimal_.push_back(new Dinosaur(39, 12, Buffer));
		listAnimal_.push_back(new Bird(39, 7, Buffer));

		player_.move(39, 27, Buffer);
	}

	bool loadGame()
	{
		//std::fstream filename("SaveGame.txt", std::ios::in);
		//std::vector<std::string> listName;
		//std::vector<int> listLevel;
		//std::string temp1;
		//int temp2, cor_x = 15, cor_y = 5;

		////Get the information from file text
		//while (filename.eof() == false)
		//{
		//	filename >> temp2;
		//	filename.ignore(80, ' ');
		//	getline(filename, temp1);
		//	listName.push_back(temp1);
		//	listLevel.push_back(temp2);
		//}
		//filename.close();

		////Print the load game
		//char Load[20][50];
		//for (int i = 0; i < 20; i++)
		//	for (int j = 0; j < 50; j++)
		//		if (i == 0 || i == 19)
		//			Load[i][j] = '#';
		//		else
		//			if (j == 0 || j == 49)
		//				Load[i][j] = '#';
		//			else
		//				Load[i][j] = ' ';
		//for (int i = 0; i < 20; i++)
		//{
		//	GotoXY(cor_x, cor_y + i);
		//	for (int j = 0; j < 50; j++)
		//		std::cout << Load[i][j];
		//	std::cout << std::endl;
		//}
		//GotoXY(cor_x, cor_y + 2); std::cout << "\t\t\t   LOAD GAME";
		//GotoXY(cor_x, cor_y + 4); std::cout << "\t   The nickname in the game:";
		//if (listName.size() == 0)
		//{
		//	GotoXY(cor_x, cor_y + 5);
		//	std::cout << "\tDon't have any nickname saved to load!";
		//	return false;
		//}
		//for (unsigned int i = 0; i < listName.size(); i++)
		//{
		//	GotoXY(cor_x, cor_y + 5 + i); 
		//	std::cout << "\t\t" << listName[i] << " - Level: " << listLevel[i];
		//}
		//GotoXY(cor_x, cor_y + 17); std::cout << "\t Enter the nickname you choose: ";
		//getline(std::cin, temp1);
		//for (int i = 0; i < listName.size(); i++)
		//	if (temp1 == listName[i])
		//	{
		//		level_ = listLevel[i];
		//		return true;
		//	}
		//GotoXY(cor_x, cor_y + 18); std:: cout << "\t\tDon't have any nickname saved to load!";
		//Sleep(5);
		//return false;

		char tempBuffer[30][120];
		std::memcpy((char*)tempBuffer, (const char*)Buffer, 120 * 30);
		for (int i = 5; i < 29; i++)
			for (int j = 1; j < 78; j++)
				Buffer[i][j] = 'M';
		PrintBuffer();
		std::memcpy((char*)Buffer, (const char*)tempBuffer, 120 * 30);
		return true;
	}

	void saveGame()
	{
		//int cor_x = 15, cor_y = 5;
		//std::string temp;
		//char Load[20][50];

		////Print the save game
		//for (int i = 0; i < 20; i++)
		//	for (int j = 0; j < 50; j++)
		//		if (i == 0 || i == 19)
		//			Load[i][j] = '#';
		//		else
		//			if (j == 0 || j == 49)
		//				Load[i][j] = '#';
		//			else
		//				Load[i][j] = ' ';
		//for (int i = 0; i < 20; i++)
		//{
		//	GotoXY(cor_x, cor_y + i);
		//	for (int j = 0; j < 50; j++)
		//		std::cout << Load[i][j];
		//	std::cout << std::endl;
		//}
		//GotoXY(cor_x, cor_y + 2); std::cout << "\t\t\t   SAVE GAME";
		//GotoXY(cor_x, cor_y + 10); std::cout << "\t Enter the nickname you save: ";
		//getline(std::cin, temp);

		////Add the new nickname into the file text
		//std::fstream filename("SaveGame.txt", std::ios::app);
		//filename << level_ << " " << temp << std::endl;;
		//filename.close();

		////Check and delete the old nickname (the number of nickname <= 10)
		//std::vector<std::string> listName;
		//std::vector<int> listLevel;
		//std::string temp1;
		//int temp2;

		////Get the information from file text
		//std::fstream in("SaveGame.txt", std::ios::in);
		//while (in.eof() == false)
		//{
		//	in >> temp2;
		//	in.ignore(80, ' ');
		//	getline(in, temp1);
		//	listName.push_back(temp1);
		//	listLevel.push_back(temp2);
		//}
		//in.close();
		//if (listName.size() > 10)
		//{
		//	for (int i = 0; i < listName.size() - 10; i++)
		//	{
		//		listName.erase(listName.begin());
		//		listLevel.erase(listLevel.begin());
		//	}
		//}
		////Print to the file text
		//std::fstream out("SaveGame.txt", std::ios::out);
		//for (int i = 0; i < listName.size(); i++)
		//	out << listLevel[i] << " " << listName[i] << std::endl;
		//out.close();
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
			player_.Up();
		else if (moveKey == 'A')
			player_.Left();
		else if (moveKey == 'S')
			player_.Down();
		else if (moveKey == 'D')
			player_.Right();
	}

	void updatePosVehicle()
	{

	}

	void updatePosAnimal()
	{

	}


};