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

	Bird* testBird;
	Dinosaur* testDino;
	Car* testCar;
	Truck* testTruck;

	Scene gameScene;
	std::vector<Row*> row;
public:
	Game()
	{
		level_ = 0;

		testBird = new Bird(39, 7);
		testDino = new Dinosaur(39, 12);
		testCar = new Car(39, 17);
		testTruck = new Truck(39, 22);
	}

	~Game()
	{
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
		gameScene.drawEntity(*testBird);
		gameScene.drawEntity(*testDino);
		gameScene.drawEntity(*testCar);
		gameScene.drawEntity(*testTruck);
		gameScene.drawEntity(player_);
		gameScene.PrintBuffer();
	}

	void drawDeadMenu()
	{
		//Redo, Use from scene
	}
	
	// ! Error, don't know why the dead not toggle
	void setPlayerDead()
	{
		player_.setState(false);
	}

	const Player& getPlayer() const
	{
		return player_	;
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