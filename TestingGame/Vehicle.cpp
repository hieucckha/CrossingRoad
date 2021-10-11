#include "Vehicle.h"

void Vehicle::move(int x, int y)
{
	x_ = x;
	y_ = y;
}

int Vehicle::getX() const
{
	return x_;
}

int Vehicle::getY() const
{
	return y_;
}
