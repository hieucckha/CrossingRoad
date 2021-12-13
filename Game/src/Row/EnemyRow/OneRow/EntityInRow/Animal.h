#pragma once
#include "Enemy.h"

class Bird : public Enemy
{
private:

public:
	Bird() : Enemy()
	{
	}
	Bird(int x, int y) : Enemy(x, y)
	{
	}
};

class Dinosaur : public Enemy
{
private:

public:
	Dinosaur()
	{
	}
	Dinosaur(int x, int y) : Enemy(x, y)
	{
	}
};