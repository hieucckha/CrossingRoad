#pragma once
#include "Vehicle.h"
#include "Animal.h"
#include "Entity.h"
#include "Row.h"

#include <vector>
#include <deque> 

class Player : public Entity
{
private:
	bool isDead;

	static Sprite* playerSprt;

public:
	// Maybe change this the default location
	Player()
	{
		coord.X = 39;
		coord.Y = 27;
		isDead = false;
		recalBound();
	}

	~Player()
	{
		delete playerSprt;
	}

	void move(int x, int y)
	{
		coord.X = x;
		coord.Y = y;
	}

	void setState(bool state)
	{
		isDead = state;
	}

	int getX() const
	{
		return coord.X;
	}
	int getY() const
	{
		return coord.Y;
	}

	void Up()
	{
		if (coord.Y >= 0)
		{
			if (coord.Y == 27)
				coord.Y -= 4;
			else
				coord.Y -= 5;
		}
	}
	void Left()
	{
		if (coord.X > 3)
		{
			coord.X--;
		}
	}
	void Down()
	{
		if (coord.Y < 28)
		{
			if (coord.Y == 23)
				coord.Y += 4;
			else if (coord.Y != 27)
				coord.Y += 5;
		}
	}
	void Right()
	{
		if (coord.X < 106)
		{
			coord.X++;
		}
	}

	bool isImpact(std::vector<Row*>& listRow) const
	{
		auto playerCoordY = this->getY();
		unsigned int inRow = 0;

		if (playerCoordY == 3 || playerCoordY == 27)
		{
			return false;
		} else
		{
			inRow = (playerCoordY - 3) / 5 - 1;
		}


		Row* row = listRow[inRow];

		unsigned int typeOfEnemy = row->getType();
		std::deque<Entity*> listEnemy = row->GetList();

		for (auto& mem : listEnemy)
		{
			auto coordXEnemy = mem->getX();

			// Enemy -> Player
			if (coordXEnemy < this->getX())
			{
				// Right | Left
				if (coordXEnemy + mem->getBound(1) >= this->getX() - this->getBound(3))
					return true;
				else
					continue;
			}

			if (coordXEnemy == this->getX())
				return true;

			// Player -> Enemy
			if (coordXEnemy > this->getX())
			{
				if (this->getX() + this->getBound(1) >= coordXEnemy - mem->getBound(3))
					return true;
				else
					continue;
			}
		}

		return false;
	}

	bool isAtFinishLine() const
	{
		return (coord.Y <= 5) ? true : false;
	}

	bool isPlayerDead() const
	{
		return !isDead;
	}

	Sprite getSprite(bool isRight = 0) const override
	{
		return *playerSprt;
	}

	SHORT getSpriteHeight() const override
	{
		return playerSprt->getHeight();
	}

	SHORT getSpriteWidth() const override
	{
		return playerSprt->getWidth();
	}
};



