#pragma once
#include "Vehicle.h"
#include "Player.h"
#include "Win32Helper.h"

#include "Windows.h"
#include <iostream>
#include <thread>

static bool g_isRunning = true;

class Game
{
private:
	Vehicle* listVehicle_;
	Player player_;

public:
	Game();

	~Game()
	{
		delete[] listVehicle_;
	}

	void drawBorder();

	void drawNormalGame();

	Player getPlayer() const;

	Vehicle* getVehicle() const;

	void exitGame(std::thread& t);

	void startGame();

	void resumeGame(std::thread& t);

	void updatePosPeople(char moving);

	void updatePosVehicle();

	void clearPrevPeople();

	void clearPrevVehicle();
};

