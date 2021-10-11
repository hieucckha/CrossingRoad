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
	const char sprite[4][16] = {
	{"     _____    "},
	{"___ /__|__\___"},
	{"|      |     `|"},
	{"`(o)------(o)'"},
	};

	Car(int x, int y)
	{
		move(x, y);
	}
};

class Truck : public Vehicle
{
public:
	const char sprite[4][24] = {
	{" ____________________ "},
	{"|___|_____|____|_|___\\"},
	{"|              | |    \\"},
	{"`--(o)(o)--------(o)--'"},
	};
	Truck(int x, int y)
	{
		move(x, y);
	}
};

