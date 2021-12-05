#ifndef _VEHICLE
#define _VEHICLE

#include "Entity.h"

class Vehicle : public Entity
{
public:
	/*virtual void move(int x, int y)
	{
		coord.X = x;
		coord.Y = y;;
	}*/
};

class Car : public Vehicle
{
private:
	static Sprite* carSprtRight;
	static Sprite* carSprtLeft;
public:
	Car(int x, int y)
	{
		move(x, y);
		recalBound();
	}

	~Car()
	{
		delete carSprtRight;
		delete carSprtLeft;
	}

	Sprite getSprite(bool isRight = 0) const override
	{
		return (isRight)? *carSprtRight : *carSprtLeft;
	}
	SHORT getSpriteHeight() const override
	{
		return carSprtRight->getHeight();
	}

	SHORT getSpriteWidth() const override
	{
		return carSprtRight->getWidth();
	}
};

class Truck : public Vehicle
{
private:
	static Sprite* truckSprtRight;
	static Sprite* truckSprtLeft;
public:
	Truck(int x, int y)
	{
		move(x, y);
		recalBound();
	}

	~Truck()
	{
		delete truckSprtRight;
		delete truckSprtLeft;
	}

	Sprite getSprite(bool isRight = 0) const override
	{
		return (isRight) ? *truckSprtRight : *truckSprtLeft;
	}
	SHORT getSpriteHeight() const override
	{
		return truckSprtRight->getHeight();
	}

	SHORT getSpriteWidth() const override
	{
		return truckSprtRight->getWidth();
	}
};

#endif // _VEHICLE