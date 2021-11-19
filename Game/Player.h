#pragma once
#include "Vehicle.h"
#include "Animal.h"
#include "Entity.h"

#include <vector>

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
		if (coord.Y >= 0) {
			if (coord.Y == 27)
				coord.Y -= 4;
			else
				coord.Y -= 5;
		}
	}
	void Left()
	{
		if (coord.X > 3) {
			coord.X--;
		}
	}
	void Down()
	{
		if (coord.Y < 28) {
			if (coord.Y == 23)
				coord.Y += 4;
			else if (coord.Y != 27)
				coord.Y += 5;
		}
	}
	void Right()
	{
		if (coord.X < 76) {
			coord.X++;
		}
	}

	bool isImpact(std::vector<Animal*> listAnimal) const
	{
			//Move to Game
	}

	bool isImpact(std::vector<Vehicle*> listVehicle) const
	{
			//Move to Game
	}

	bool isAtFinishLine() const
	{
		return (coord.Y <= 5) ? true : false;
	}

	bool isPlayerDead() const
	{
		return !isDead;
	}

	Sprite getSprite() const override
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



