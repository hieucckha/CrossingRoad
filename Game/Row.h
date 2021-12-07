#ifndef _ROW
#define _ROW
#pragma once
#include "Animal.h"
#include "Vehicle.h"
#include <Windows.h>
#include <vector> 
#include <ctime>

class Row
{
private:
	int y_coord; // Coordinate Y
	int type; // Type of enemy
	int MAX_ENEMIES; // Max number of enemies on a row
	clock_t t; //Speed
	int speed;
	int _speed;
	int distance;
	int redLightTime; // Red light time
	bool isFromRight; // true if Row from right
	bool isRedLight; // true if Row has red light
	std::vector <Entity*> inhabitance; // list of entities on row

public:
	Row(int y) : y_coord(y) // DEFAULT
	{
		type = (rand() % 4);
		t = 0;
		MAX_ENEMIES = 5;
		redLightTime = 5;
		speed = 4;
		distance = 40;
		_speed = speed;
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
	std::vector <Entity*> GetList() const
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

	void AtLevel(int lvl) // Set new red light time by new level
	{
		static int _lvl = 0;
		if (lvl > 0 && _lvl != lvl)
		{
			if (lvl % 16 == 0) // Lvl.12 24 36... set new values
			{
				MAX_ENEMIES = 6;
				speed =	3;
				redLightTime = 4;
				distance = 40;
			}
			else if (lvl % 3 == 0 && MAX_ENEMIES < 8) // Lvl.3 6 9 increase enemies, decrease distance
			{
				MAX_ENEMIES++;
				distance -= 10;
			}
			else if (lvl % 5 == 0 && speed > 0) // Lvl.5 10 15 decrease stop time
				redLightTime--;
			else if (lvl % 2 == 1 && redLightTime > 3) // Lvl.(prime number) increase speed
				speed--;

			_lvl = lvl;
		}
	}

	void append()
	{
		if (isFromRight)
		{
			switch (type)
			{
			case 0:
				if (inhabitance.empty())
					inhabitance.push_back(new Car(rand() % 110 - 20, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Car(prevXcoord + (rand() % distance) + 20, y_coord));
				}

				break;

			case 1:
				if (inhabitance.empty())
					inhabitance.push_back(new Truck(rand() % 110 - 20, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Truck(prevXcoord + (rand() % distance) + 20, y_coord));
				}

				break;

			case 2:
				if (inhabitance.empty())
					inhabitance.push_back(new Bird(rand() % 110 - 20, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Bird(prevXcoord + (rand() % distance) + 20, y_coord));
				}

				break;

			case 3:
				if (inhabitance.empty())
					inhabitance.push_back(new Dinosaur(rand() % 110 - 20, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Dinosaur(prevXcoord + (rand() % distance) + 20, y_coord));
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
					inhabitance.push_back(new Car(rand() % 110 + 20, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Car(prevXcoord - (rand() % distance) - 20, y_coord));
				}

				break;

			case 1:
				if (inhabitance.empty())
					inhabitance.push_back(new Truck(rand() % 110 + 20, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Truck(prevXcoord - (rand() % distance) - 20, y_coord));
				}

				break;

			case 2:
				if (inhabitance.empty())
					inhabitance.push_back(new Bird(rand() % 110 + 20, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Bird(prevXcoord - (rand() % distance) - 20, y_coord));
				}

				break;

			case 3:
				if (inhabitance.empty())
					inhabitance.push_back(new Dinosaur(rand() % 110 + 20, y_coord));

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Dinosaur(prevXcoord - (rand() % 50) - 20, y_coord));
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
			if (_speed == 0)
			{
				for (auto& enemy : inhabitance)
				{
					if (isFromRight) // Enemy gets out of row will return to the start
					{
						if (enemy->getX() == -20)
							inhabitance.erase(inhabitance.begin());
						else
							enemy->move(enemy->getX() - 1, y_coord);
					}
					else
					{
						if (enemy->getX() == 130)
							inhabitance.erase(inhabitance.begin());
						else
							enemy->move(enemy->getX() + 1, y_coord);
					}
				}

				if (rand() % 200 < 5) // Randomize when to turn red light
					toggle();

				_speed = speed; // Timing to move etity
			}
			else
				_speed--;
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