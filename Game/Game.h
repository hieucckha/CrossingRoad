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

	bool loadGame()
	{
		//Redo
		return false;
	}

	void saveGame()
	{
		//Redo
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