#pragma once
#include "Point2D.h"

class Enemy
{
private:
	Point2D coord_;

public:
	Enemy()
	{
	}
	Enemy(int x, int y)
	{
		coord_.setBoth(x, y);
	}
	virtual ~Enemy() = default;

	void move(int x, int y)
	{
		coord_.setBoth(x, y);
	}

	Point2D& getCoord()
	{
		return coord_;
	}
};

