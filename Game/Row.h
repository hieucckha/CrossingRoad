#ifndef _ROW
#define _ROW
#pragma once
#include "Animal.h"
#include "Vehicle.h"
#include <Windows.h>
#include <deque> 
#include <ctime>

class Row
{
private:
	int y_coord; // Coordinate Y
	int type; // Type of enemy
	int MAX_ENEMIES; // Max number of enemies on a row
	clock_t t; //Speed
	int redLightTime; // Red light time
	bool isFromRight; // true if Row from right
	bool isRedLight; // true if Row has red light
	std::deque <Entity*> inhabitance; // list of entities on row

public:
	Row(int y) : y_coord(y) // DEFAULT
	{
		type = (rand() % 4);
		t = 0;
		MAX_ENEMIES = 6;
		redLightTime = 10;
		isFromRight = rand() % 2;
		isRedLight = false;
	}

	~Row()
	{
		for (auto x : inhabitance)
			delete x;
		while (!inhabitance.empty())
			inhabitance.pop_back();
	}

	int GetY() const
	{
		return y_coord;
	}

	int GetT() const
	{
		return t;
	}

	int GetTime() const
	{
		return redLightTime;
	}

	bool GetRight() const
	{
		return isFromRight;
	}

	bool GetRedLight() const
	{
		return isRedLight;
	}

	int getType() const
	{
		return type;
	}

	bool getIsFromRight() const
	{
		return isFromRight;
	}
	std::deque <Entity*> GetList() const
	{
		return inhabitance;
	}

	void SetY(int y)
	{
		y_coord = y;
	}

	void SetT(clock_t T)
	{
		t = T;
	}

	void SetTime(float time)
	{
		redLightTime = time;
	}

	void SetRight(bool right)
	{
		isFromRight = right;
	}

	void SetRedLight(bool tick)
	{
		isRedLight = tick;
	}

	void toggle()
	{
		isRedLight = !isRedLight;

		if (isRedLight)
			t = clock();
	}

	void setTimeatLevel(int lvl) // Set new red light time by new level
	{
		redLightTime = 10 - lvl;
		if (lvl > 10)
			MAX_ENEMIES++;
	}
	void append()
	{
		if (isFromRight)
		{
			switch (type)
			{
			case 0:
				if (inhabitance.empty())
					inhabitance.push_back(new Car(110, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Car(prevXcoord + rand() % 50 + 20, y_coord));
					//inhabitance.push_back(new Car(rand() % 110 + 110, y_coord));
				}

				break;

			case 1:
				if (inhabitance.empty())
					inhabitance.push_back(new Truck(110, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Truck(prevXcoord + (rand() % 50) + 20, y_coord));
					//inhabitance.push_back(new Truck(rand() % 110 + 110, y_coord));
				}

				break;

			case 2:
				if (inhabitance.empty())
					inhabitance.push_back(new Bird(110, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Bird(prevXcoord + (rand() % 50) + 20, y_coord));
					//inhabitance.push_back(new Bird(rand() % 110 + 110, y_coord));
				}

				break;

			case 3:
				if (inhabitance.empty())
					inhabitance.push_back(new Dinosaur(110, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Dinosaur(prevXcoord + (rand() % 50) + 20, y_coord));
					//inhabitance.push_back(new Dinosaur(rand() % 110 + 110, y_coord));
				}

				break;

			default:
				break;
			}
		} else // From Left
		{
			switch (type)
			{
			case 0:
				if (inhabitance.empty())
					inhabitance.push_back(new Car(0, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Car(prevXcoord - (rand() % 50) - 20, y_coord));
					//inhabitance.push_back(new Car(rand() % 110 - 110, y_coord));
				}

				break;

			case 1:
				if (inhabitance.empty())
					inhabitance.push_back(new Truck(0, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Truck(prevXcoord - (rand() % 50) - 20, y_coord));
					//inhabitance.push_back(new Truck(rand() % 110 - 110, y_coord));
				}

				break;

			case 2:
				if (inhabitance.empty())
					inhabitance.push_back(new Bird(0, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Bird(prevXcoord - (rand() % 50) - 20, y_coord));
					//inhabitance.push_back(new Bird(rand() % 110 - 110, y_coord));
				}

				break;

			case 3:
				if (inhabitance.empty())
					inhabitance.push_back(new Dinosaur(0, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Dinosaur(prevXcoord - (rand() % 50) - 20, y_coord));
					//inhabitance.push_back(new Dinosaur(rand() % 110 - 110, y_coord));
				}

				break;

			default:
				break;
			}
		}
	}

	void move()
	{
		if (!isRedLight)
		{
			for (auto& enemy : inhabitance)
			{
				if (isFromRight) // Enemy gets out of row will return to the start
				{
					enemy->move(enemy->getX() - 1, enemy->getY());
					if (enemy->getX() == -20)
						enemy->move(110 + (rand() & 30) + 40, y_coord);
				} else
				{
					enemy->move(enemy->getX() + 1, enemy->getY());
					if (enemy->getX() == 150)
						enemy->move(-(rand() & 30) - 40, y_coord);
				}
			}

			if (rand() % 200 < 5) // Randomize when to turn red light
				toggle();
		} else
		{
			clock_t _t = clock() - t;
			if (((int)_t) / CLOCKS_PER_SEC == redLightTime) // Timer to turn green light
			{
				toggle();
				t = clock();
			}
		}
	}
};
#endif // _ROW

/*
* Red Light
*/