#ifndef _ENTITY
#define _ENTITY
#include "Win32Helper.h"
#include "Sprite.h"
#include <math.h>

class Entity
{
protected:
	COORD coord;
	static Sprite* sprt;

	//Clockwise
	SHORT bound[4];
public:
	Entity()
	{
		coord.X = 0;
		coord.Y = 0;
		sprt = nullptr;
		bound[0] = 0;
		bound[1] = 0;
		bound[2] = 0;
		bound[3] = 0;
	}
	~Entity()
	{
		delete sprt;
	}

	SHORT getX() const
	{
		return coord.X;
	}

	SHORT getY() const
	{
		return coord.Y;
	}

	virtual void move(int x, int y)
	{
		coord.X = x;
		coord.Y = y;
	}

	virtual SHORT getSpriteHeight() const
	{
		return sprt->getHeight();
	}

	virtual SHORT getSpriteWidth() const
	{
		return sprt->getWidth();
	}

	SHORT getBound(int index) const
	{
		return bound[index];
	}

	virtual Sprite getSprite() const 
	{
		return *sprt;
	}

	void recalBound()
	{
		//Clockwise order
		bound[0] = (getSpriteHeight() - 1) / 2;
		bound[1] = floor((getSpriteWidth() - 1) / 2);
		bound[2] = getSpriteHeight() / 2;
		bound[3] = ceil((getSpriteWidth() - 1) / 2);
	}
};

#endif //_ENTITY