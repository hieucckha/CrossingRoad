#pragma once

class Vehicle
{
private:
	int x_, y_;

public:
	virtual void move(int x, int y);

	int getX() const;

	int getY() const;
};

class Car : public Vehicle
{

};

class Truck : public Vehicle
{

};

