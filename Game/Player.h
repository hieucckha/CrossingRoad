#pragma once
#include "Vehicle.h"
#include "Animal.h"

#include <vector>

class Player
{
private:
	int x_, y_;
	bool m_State;

public:

	// Maybe change this the default location
	Player() : x_(39), y_(28), m_State(true)
	{

	}

	void move(int x, int y)
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

	void Up(int x)
	{
		if (y_ >= 0)
			y_--;
	}
	void Left(int x)
	{
		if (x_ >= 0)
			x_--;
	}
	void Down(int x)
	{
		if (y_ < 30)
			y_++;
	}
	void Right(int x)
	{
		if (x_ < 80)
			x_++;
	}

	bool isImpact(std::vector<Animal*> listAnimal) const
	{
		for (size_t i = 0; i < listAnimal.size(); ++i)
		{
			if (listAnimal[i]->getX() == this->x_ && listAnimal[i]->getY() == this->y_)
				return true;
		}

		return false;
	}

	bool isImpact(std::vector<Vehicle*> listVehicle) const
	{
		for (size_t i = 0; i < listVehicle.size(); ++i)
		{
			if (listVehicle[i]->getX() == this->x_ && listVehicle[i]->getY() == this->y_)
				return true;
		}

		return false;
	}

	bool isFinish() const
	{
		if (y_ == 3)
		{
			return true;
		}

		return false;
	}

	bool isDead() const
	{
		return !m_State;
	}

};



