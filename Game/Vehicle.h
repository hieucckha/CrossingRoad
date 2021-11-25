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
	static Sprite* carSprt;
public:
	Car(int x, int y)
	{
		move(x, y);
		recalBound();
	}

	~Car()
	{
		delete carSprt;
	}

	Sprite getSprite() const override
	{
		return *carSprt;
	}
	SHORT getSpriteHeight() const override
	{
		return carSprt->getHeight();
	}

	SHORT getSpriteWidth() const override
	{
		return carSprt->getWidth();
	}
};

class Truck : public Vehicle
{
private:
	static Sprite* truckSprt;
public:
	Truck(int x, int y)
	{
		move(x, y);
		recalBound();
	}

	~Truck()
	{
		delete truckSprt;
	}

	Sprite getSprite() const override
	{
		return *truckSprt;
	}
	SHORT getSpriteHeight() const override
	{
		return truckSprt->getHeight();
	}

	SHORT getSpriteWidth() const override
	{
		return truckSprt->getWidth();
	}
};

#endif // _VEHICLE