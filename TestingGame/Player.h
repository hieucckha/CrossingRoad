#pragma once
#include "Vehicle.h"

class Player
{
private:
	int x_, y_;
	bool state_;

public:
	Player() : x_(39), y_(28), state_(true)
	{
	}

	void Up(int x)
	{
		y_--;
	}

	void Left(int x)
	{
		x_--;
	}

	void Down(int x)
	{
		y_++;
	}

	void Right(int x)
	{
		x_++;
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
		return !state_;
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



