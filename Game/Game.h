#pragma once
#include "Animal.h"
#include "Vehicle.h"
#include "Player.h"
#include "Scene.h"
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
	int level_;
	Player player_;

	//!!!!DEBUG_ONLY!!!!
	//Bird* testBird;
	//Dinosaur* testDino;
	//Car* testCar;
	//Truck* testTruck;
	//!!!!END_OF_DEBUG!!!!

	Scene gameScene;
	std::vector<Row*> row;
public:
	Game()
	{
		level_ = 0;

		//testBird = new Bird(0, 7);
		//testDino = new Dinosaur(39, 12);
		//testCar = new Car(39, 17);
		//testTruck = new Truck(39, 22);
	}

	~Game()
	{
	}

	std::vector<Row*>& getRow()
	{
		return row;
	}

	int getLevel() const
	{
		return level_;
	}
	/// <summary>
	/// Display generated Buffer to the monitor
	/// </summary>
	void PrintBuffer()
	{
		gameScene.PrintBuffer();
	}

	/// <summary>
	/// Generate and display ALL elements of the game
	/// </summary>
	void drawGame()
	{
		gameScene.drawScene(level_);
		//gameScene.drawEntity(*testBird);
		//gameScene.drawEntity(*testDino);
		//gameScene.drawEntity(*testCar);
		//gameScene.drawEntity(*testTruck);

		for (auto x : row)
			gameScene.drawOneRow(*x);

		gameScene.drawEntity(player_);
		gameScene.PrintBuffer();
	}

	//Remember to pause the game
	void drawDeadMenu()
	{
		gameScene.drawDeadMenu();
		gameScene.PrintBuffer();
	}

	//!!!Error, don't know why the dead not toggle!!!
	void setPlayerDead()
	{
		player_.setState(false);
	}

	const Player& getPlayer() const
	{
		return player_;
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
		row.clear();
		updatePosPeople(' ');
		updateRows();
		drawGame();
		//Redo
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

		player_.move(39, 27);
		//Redo
	}

	void loadGame()
	{
		std::vector<std::string> listName;
		std::vector<int> listLevel;

		//Get data
		std::fstream input("SaveGame.txt", std::ios::in);
		std::string name;
		int lvl;
		while (input.eof() == false)
		{
			input >> lvl;
			input.ignore(80, ' ');
			getline(input, name);
			listName.push_back(name);
			listLevel.push_back(lvl);
		}
		listName.pop_back();
		listLevel.pop_back();
		input.close();

		//Update the number of data in the file
		int n = listName.size();
		if (n > 4)
		{
			for (int i = 0; i < n - 4; i++)
			{
				listName.erase(listName.begin());
				listLevel.erase(listLevel.begin());
			}
			n = listName.size();
			std::fstream output("SaveGame.txt", std::ios::out);
			for (int i = 0; i < n; i++)
				output << listLevel[i] << " " << listName[i] << std::endl;
			output.close();
		}

		gameScene.drawLoadMenu();
		for (int i = 0; i < n; i++)
		{
			gameScene.setBuffer(23, 15 + i, listName[i]);
			gameScene.setBuffer(37, 15 + i, "level: " + std::to_string(listLevel[i]));
		}
		gameScene.PrintBuffer();

		GotoXY(40, 20); getline(std::cin, name);
		gameScene.setBuffer(40, 20, name);
		gameScene.PrintBuffer();
		
		for (int i = 0; i < n; i++)
			if (name == listName[i])
			{
				level_ = listLevel[i];
				resetGame();
				startGame();
			}
	}

	void saveGame()
	{
		gameScene.drawSaveMenu();
		gameScene.PrintBuffer();

		std::string name;
		GotoXY(37, 16); getline(std::cin, name);
		gameScene.setBuffer(37, 16, name);
		gameScene.PrintBuffer();

		std::fstream out("SaveGame.txt", std::ios::app);
		out << level_ << " " << name << std::endl;
		out.close();
	}

	void pauseGame(HANDLE hd)
	{
		SuspendThread(hd);
	}

	void resumeGame(HANDLE hd)
	{
		ResumeThread(hd);
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

	void updateRows()
	{
		srand((unsigned)time(NULL));
		// Initialize
		if (row.empty())
		{
			row.push_back(new Row(7));
			row.push_back(new Row(12));
			row.push_back(new Row(17));
			row.push_back(new Row(22));
		}

		for (auto& x : row)
		{
			x->setTimeatLevel(level_);
			x->append();
			x->move();
		}
	}

};