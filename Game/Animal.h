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
	const char sprite[4][12] = {
		{"     __   "},
		{"    / 7   "},
		{"<()/____7 "},
		{" '------\"\""}
	};
	Bird(int x, int y)
	{
		move(x, y);
	}
};

class Dinosaur : public Animal
{
public:
	const char sprite[4][14] = {
		{" __          "},
		{"(_ \\_/\\/\\__  "},
		{"  \\   _    \\ "},
		{"   |_| |_|'-\\"}
	};
	Dinosaur(int x, int y)
	{
		move(x, y);
	}
};

