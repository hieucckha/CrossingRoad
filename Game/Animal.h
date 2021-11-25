#ifndef _ANIMAL
#define _ANIMAL
#include "Entity.h"
#include "Sprite.h"

class Animal : public Entity
{
public:
	/*virtual void move(int x, int y)
	{
		coord.X = x;
		coord.Y = y;
	}*/
};

class Bird : public Animal
{
private:
	static Sprite* birdSprt;
public:
	Bird(int x, int y)
	{
		move(x, y);
		recalBound();
	}

	~Bird()
	{
		delete birdSprt;
	}

	Sprite getSprite() const override
	{
		return *birdSprt;
	}
	SHORT getSpriteHeight() const override
	{
		return birdSprt->getHeight();
	}

	SHORT getSpriteWidth() const override
	{
		return birdSprt->getWidth();
	}
};

class Dinosaur : public Animal
{
private:
	static Sprite* dinoSprt;
public:
	Dinosaur(int x, int y)
	{
		move(x, y);
		recalBound();
	}

	~Dinosaur()
	{
		delete dinoSprt;
	}

	Sprite getSprite() const override
	{
		return *dinoSprt;
	}
	SHORT getSpriteHeight() const override
	{
		return dinoSprt->getHeight();
	}

	SHORT getSpriteWidth() const override
	{
		return dinoSprt->getWidth();
	}
};
#endif // _ANIMAL