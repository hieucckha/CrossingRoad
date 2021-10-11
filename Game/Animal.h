#pragma once

class Animal
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

class Bird : public Animal
{
public:
	Bird(int x, int y)
	{
		move(x, y);
	}
};

class Dinosaur : public Animal
{
public:
	Dinosaur(int x, int y)
	{
		move(x, y);
	}
};

