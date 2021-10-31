#pragma once
#include "Point2D.h"
#include "Enemy.h"

class Car : public Enemy
{
private:

public:
	Car() : Enemy()
	{
	}
	Car(int x, int y) : Enemy(x, y)
	{
	}
};

class Truck : public Enemy
{
private:

public:
	Truck()
	{
	}
	Truck(int x, int y) : Enemy(x, y)
	{
	}
};