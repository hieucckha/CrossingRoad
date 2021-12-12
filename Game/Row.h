#ifndef _ROW
#define _ROW

#include "Animal.h"
#include "Vehicle.h"

#include <Windows.h>
#include <vector> 
#include <ctime>
#include <random>

class Row
{
private:
	int y_coord; // Coordinate Y
	int type; // Type of enemy
	int MAX_ENEMIES; // Max number of enemies on a row
	clock_t t; // Time
	int speed;  //Speed
	int _speed; //Speed buffer
	int _lvl;
	int distance; // Distance between 2 entities
	int redLightTime; // Red light time
	bool isFromRight; // true if Row from right
	bool isRedLight; // true if Row has red light
	std::vector <Entity*> inhabitance; // list of entities on row

public:
	std::random_device gen;
	Row(int y) : y_coord(y) // DEFAULT
	{
		std::uniform_int_distribution <int> randType(0, 3);
		type = randType(gen); // rand % 4
		t = 0;
		_lvl = 0;
		MAX_ENEMIES = 4;
		redLightTime = 4;
		speed = 10;
		distance = 40;
		_speed = speed;
		std::uniform_int_distribution <int> randSpeed(0, 1);
		isFromRight = randSpeed(gen); // rand % 2
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
		if (lvl > 0 && _lvl != lvl)
		{
			if (lvl % 20 == 0) // Lvl.20 40 60... set new values
			{
				MAX_ENEMIES = 6;
				redLightTime = 4;
				speed = 10;
				distance = 40;
			}
			else if (lvl % 3 == 0 && MAX_ENEMIES < 8) // Lvl.3 6 9 increase enemies, decrease distance
			{
				MAX_ENEMIES++;
				distance -= 10;
			}
			else if (lvl % 2 == 0 && redLightTime > 1) // Lvl.2 4 8 decrease stop time
			{
				redLightTime--;
				speed-= 2;
			}

			_lvl = lvl;
		}
	}

	void append()
	{
		std::uniform_int_distribution <int> randDistance(0, distance);
		std::uniform_int_distribution <int> _randDistance(0, 110);
		if (isFromRight)
		{
			//0: Car
			//1: Truck
			//2: Bird
			//3: Dino
			switch (type)
			{
			case 0:
				if (inhabitance.empty())
				{
					inhabitance.push_back(new Car(_randDistance(gen) - 30, y_coord));
					//inhabitance.push_back(new Car(rand() % 110 - 60, y_coord));
				}

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Car(prevXcoord + randDistance(gen) + 30, y_coord));
				}

				break;

			case 1:
				if (inhabitance.empty())
				{
					inhabitance.push_back(new Truck(_randDistance(gen) - 30, y_coord));
					//inhabitance.push_back(new Truck(rand() % 110 - 60, y_coord));
				}

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Truck(prevXcoord + randDistance(gen) + 30, y_coord));
				}

				break;

			case 2:
				if (inhabitance.empty())
				{
					inhabitance.push_back(new Bird(_randDistance(gen) - 30, y_coord));
					//inhabitance.push_back(new Bird(rand() % 110 - 60, y_coord));
				}

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Bird(prevXcoord + randDistance(gen) + 30, y_coord));
				}

				break;

			case 3:
				if (inhabitance.empty())
				{
					inhabitance.push_back(new Dinosaur(_randDistance(gen) - 30, y_coord));
					//inhabitance.push_back(new Dinosaur(rand() % 110 - 60, y_coord));
				}

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Dinosaur(prevXcoord + randDistance(gen) + 30, y_coord));
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
				{
					inhabitance.push_back(new Car(_randDistance(gen) + 30, y_coord));
					//inhabitance.push_back(new Car(rand() % 110 + 60, y_coord));
				}

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Car(prevXcoord - randDistance(gen) - 30, y_coord));
				}

				break;

			case 1:
				if (inhabitance.empty())
				{
					inhabitance.push_back(new Truck(_randDistance(gen) + 30, y_coord));
					//inhabitance.push_back(new Truck(rand() % 110 + 60, y_coord));
				}

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Truck(prevXcoord - randDistance(gen) - 30, y_coord));
				}

				break;

			case 2:
				if (inhabitance.empty())
				{
					inhabitance.push_back(new Bird(_randDistance(gen) + 30, y_coord));
					//inhabitance.push_back(new Bird(rand() % 110 + 60, y_coord));
				}

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Bird(prevXcoord - randDistance(gen) - 30, y_coord));
				}

				break;

			case 3:
				if (inhabitance.empty())
				{
					inhabitance.push_back(new Dinosaur(_randDistance(gen) + 30, y_coord));
					//inhabitance.push_back(new Dinosaur(rand() % 110 + 60, y_coord));
				}

				if (inhabitance.size() < MAX_ENEMIES)
				{
					int prevXcoord = inhabitance.back()->getX();
					inhabitance.push_back(new Dinosaur(prevXcoord - randDistance(gen) - 30, y_coord));
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

				std::uniform_int_distribution <int> randToggle(0, 200);
				if (randToggle(gen) < 2 && inhabitance.size() >= 4) // Randomize when to turn red light
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