#pragma once
#include "Vehicle.h"
#include "Animal.h"
#include "Define.h"

#include <vector>
//#include <ctime>
#include <cstdlib>

class OneRow
{
private:
	std::vector<Enemy*> listEnemy_;
	int type_;

	// True -> Linear
	// False -> Random
	bool linearRandom_;

	// True -> Right
	// False -> Left
	bool direction_;

	bool isRedLight_;
	// How many tick to update
	// The bigger number is longer
	int redLightTime_;
	// How many tick to update
	// The bigger number is slow
	int speed_;
	int currRow_;

public:
	friend class Scene;
	// Speed red light time will be define here
	OneRow(int level, int currRow)
	{
		listEnemy_.resize(0);

		type_ = rand() % 4;
		linearRandom_ = rand() % 2;
		direction_ = rand() % 2;

		isRedLight_ = rand() % 2;

		if (g_isHard)
		{
			speed_ = 1 + 30 - (level - level % 2) / 2;
			// Max 40
			redLightTime_ = 1 + speed_ * (rand() % (160 - level * 4));
		}
		else
		{
			speed_ = 1 + 40 - (level - level % 2) / 2;
			// Max 100
			redLightTime_ = 1 + speed_ * (rand() % (200 - level * 2));
		}

		currRow_ = currRow;
	}
	OneRow(std::vector<Enemy*> listEnemy, int type, bool linearRandom, bool direction, bool isRedLight, int redLightTime, int speed, int currRow)
	{
		listEnemy_ = listEnemy;
		type_ = type;
		linearRandom_ = linearRandom_;
		direction_ = direction;
		isRedLight_ = isRedLight;
		redLightTime_ = redLightTime;
		speed_ = speed;
		currRow_ = currRow;
	}
	~OneRow()
	{
		cleanOneRow();
	}

	void cleanOneRow()
	{
		size_t size = listEnemy_.size();
		for (auto& mem : listEnemy_)
			delete mem;

		for (size_t i = 0; i < size; ++i)
			listEnemy_.pop_back();
	}

	void toggleRedLight()
	{
		isRedLight_ = !isRedLight_;
	}
	void setNewRedLightTime(int level)
	{
		redLightTime_ = 1 + speed_ * (rand() % 200 - level * 2);
	}

	std::vector<Enemy*> getEnemyList()
	{
		return listEnemy_;
	}
	int getType()
	{
		return type_;
	}
	bool getLinearRandom()
	{
		return linearRandom_;
	}
	bool getDirection()
	{
		return direction_;
	}
	bool getIsRedLight()
	{
		return isRedLight_;
	}
	int getRedLightTime()
	{
		return redLightTime_;
	}
	int getSpeed()
	{
		return speed_;
	}
	int getCurrentRow()
	{
		return currRow_;
	}

	void addEnemy()
	{
		// Linear
		if (linearRandom_)
		{
			// Right
			if (direction_)
			{
				switch (type_)
				{
				// Car
				case 0:
					if (listEnemy_.size() == 0)
					{
						listEnemy_.push_back(new Car(MapLeftCol - 1 - 12, 2 + (currRow_ - 1) * 5));
					}
					else
					{
						Point2D coord = listEnemy_.at(listEnemy_.size() - 1)->getCoord();
						listEnemy_.push_back(new Car(coord.getX() - (rand() % 50) - 12, 2 + (currRow_ - 1) * 5));
					}
					break;
				// Truck
				case 1:
					if (listEnemy_.size() == 0)
					{
						listEnemy_.push_back(new Truck(MapLeftCol - 1 - 12, 2 + (currRow_ - 1) * 5));
					}
					else
					{
						Point2D coord = listEnemy_.at(listEnemy_.size() - 1)->getCoord();
						listEnemy_.push_back(new Truck(coord.getX() - (rand() % 50) - 12, 2 + (currRow_ - 1) * 5));
					}
					break;
				// Bird
				case 2:
					if (listEnemy_.size() == 0)
					{
						listEnemy_.push_back(new Bird(MapLeftCol - 1 - 5, 2 + (currRow_ - 1) * 5));
					}
					else
					{
						Point2D coord = listEnemy_.at(listEnemy_.size() - 1)->getCoord();
						listEnemy_.push_back(new Bird(coord.getX() - (rand() % 50) - 5, 2 + (currRow_ - 1) * 5));
					}
					break;
				// Dinosaur
				case 3:
					if (listEnemy_.size() == 0)
					{
						listEnemy_.push_back(new Dinosaur(MapLeftCol - 1 - 12, 2 + (currRow_ - 1) * 5));
					}
					else
					{
						Point2D coord = listEnemy_.at(listEnemy_.size() - 1)->getCoord();
						listEnemy_.push_back(new Dinosaur(coord.getX() - (rand() % 50) - 12, 2 + (currRow_ - 1) * 5));
					}
				default:
					break;
				}
			// Left
			}
			else
			{
				switch (type_)
				{
				// Car
				case 0:
					if (listEnemy_.size() == 0)
					{
						listEnemy_.push_back(new Car(MapRightCol + 1, 2 + (currRow_ - 1) * 5));
					}
					else
					{
						Point2D coord = listEnemy_.at(listEnemy_.size() - 1)->getCoord();
						listEnemy_.push_back(new Car(coord.getX() + 12 + (rand() % 50), 2 + (currRow_ - 1) * 5));
					}
					break;
				// Truck
				case 1:
					if (listEnemy_.size() == 0)
					{
						listEnemy_.push_back(new Truck(MapRightCol + 1, 2 + (currRow_ - 1) * 5));
					}
					else
					{
						Point2D coord = listEnemy_.at(listEnemy_.size() - 1)->getCoord();
						listEnemy_.push_back(new Truck(coord.getX() + 12 + (rand() % 50), 2 + (currRow_ - 1) * 5));
					}
					break;
				// Bird
				case 2:
					if (listEnemy_.size() == 0)
					{
						listEnemy_.push_back(new Bird(MapRightCol + 1, 2 + (currRow_ - 1) * 5));
					}
					else
					{
						Point2D coord = listEnemy_.at(listEnemy_.size() - 1)->getCoord();
						listEnemy_.push_back(new Bird(coord.getX() + 5 + (rand() % 50), 2 + (currRow_ - 1) * 5));
					}
					break;
				// Dinosaur
				case 3:
					if (listEnemy_.size() == 0)
					{
						listEnemy_.push_back(new Dinosaur(MapRightCol + 1, 2 + (currRow_ - 1) * 5));
					}
					else
					{
						Point2D coord = listEnemy_.at(listEnemy_.size() - 1)->getCoord();
						listEnemy_.push_back(new Dinosaur(coord.getX() + 12 + (rand() % 50), 2 + (currRow_ - 1) * 5));
					}
				default:
					break;
				}
			}
		// Random
		}
		else
		{
			// Right
			if (direction_)
			{
				switch (type_)
				{
				// Car
				case 0:
					listEnemy_.push_back(new Car(MapLeftCol + rand() % (MapRightCol - MapLeftCol), 2 + (currRow_ - 1) * 5));
					break;
				// Truck
				case 1:
					listEnemy_.push_back(new Truck(MapLeftCol + rand() % (MapRightCol - MapLeftCol), 2 + (currRow_ - 1) * 5));
					break;
				// Bird
				case 2:
					listEnemy_.push_back(new Bird(MapLeftCol + rand() % (MapRightCol - MapLeftCol), 2 + (currRow_ - 1) * 5));
					break;
				// Dinosaur
				case 3:
					listEnemy_.push_back(new Dinosaur(MapLeftCol + rand() % (MapRightCol - MapLeftCol), 2 + (currRow_ - 1) * 5));
				default:
					break;
				}
			// Left
			}
			else
			{
				switch (type_)
				{
				// Car
				case 0:
					listEnemy_.push_back(new Car(MapLeftCol + rand() % (MapRightCol - MapLeftCol), 2 + (currRow_ - 1) * 5));
					break;
				// Truck
				case 1:
					listEnemy_.push_back(new Truck(MapLeftCol + rand() % (MapRightCol - MapLeftCol), 2 + (currRow_ - 1) * 5));
					break;
				// Bird
				case 2:
					listEnemy_.push_back(new Bird(MapLeftCol + rand() % (MapRightCol - MapLeftCol), 2 + (currRow_ - 1) * 5));
					break;
				// Dinosaur
				case 3:
					listEnemy_.push_back(new Dinosaur(MapLeftCol + rand() % (MapRightCol - MapLeftCol), 2 + (currRow_ - 1) * 5));
				default:
					break;
				}
			}
		}
	}
	void move()
	{
		if (!isRedLight_)
		{
			for (auto& enemy : listEnemy_)
			{
				Point2D coord = enemy->getCoord();
				// Right
				if (direction_)
				{
					if (coord.getX() > MapRightCol)
					{
						int newCoordX = MapLeftCol - (rand() % 30) - 15;
						enemy->move(newCoordX, coord.getY());
					}
					else
					{
						int newCoordX = coord.getX() + 1;
						enemy->move(newCoordX, coord.getY());
					}
				// Left
				}
				else
				{
					if (coord.getX() < MapLeftCol - 13)
					{
						int newCoordX = MapRightCol + (rand() % 30) + 15;
						enemy->move(newCoordX, coord.getY());
					}
					else
					{
						int newCoordX = coord.getX() - 1;
						enemy->move(newCoordX, coord.getY());
					}
				}
			}
		}
	}
};