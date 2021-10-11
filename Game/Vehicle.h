#pragma once

class Vehicle
{
private:
	int x_, y_;

public:
	virtual void move(int x, int y)
	{
		x_ = x;
		y_ = y;
	}

	int getX() const
	{
		return x_;
	}

	int getY() const
	{
		return y_;
	}

};

class Car : public Vehicle
{
public:
	Car(int x, int y)
	{
		move(x, y);
	}
};

class Truck : public Vehicle
{
public:
	Truck(int x, int y)
	{
		move(x, y);
	}
};

