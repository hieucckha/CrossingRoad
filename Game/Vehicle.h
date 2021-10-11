#pragma once

typedef char(*bufferPtr)[120];

class Vehicle
{
private:
	int x_, y_;
	bufferPtr Buffer_;

public:
	/// <summary>
	/// Move the coordinate of Vehicle to x and y, save to Buffer
	/// </summary>
	/// <param name="x">: Coordinate x</param>
	/// <param name="y">: Coordinate y</param>
	/// <param name="Buffer">: Buffer pointer</param>
	virtual void move(int x, int y, bufferPtr Buffer)
	{
		x_ = x;
		y_ = y;
		Buffer_ = Buffer;
	}

	int getX() const
	{
		return x_;
	}

	int getY() const
	{
		return y_;
	}

	bufferPtr getBuffer()
	{
		return Buffer_;
	}

	void draw();
};

class Car : public Vehicle
{
public:
	const char sprite[4][16] = {
	{"     _____    "},
	{" ___/__|__\\___ "}, //pivot " ___/__|__\\___ "
	{"|      |     `|"},  //              ^
	{"`(o)------(o)'"},
	};

	Car(int x, int y, bufferPtr Buffer = nullptr)
	{
		move(x, y, Buffer);
	}

	void drawSprite()
	{
		for (int Y = this->getY() - 1, j = 0; Y <= this->getY() + 2; ++Y, ++j) {
			for (int X = this->getX() - 7, i = 0; X <= this->getX() + 7; ++X, ++i) {
				this->getBuffer()[Y][X] = sprite[j][i];
			}
		}
	}
};

class Truck : public Vehicle
{
public:
	const char sprite[4][24] = {
	{" ____________________  "},
	{"|___|_____|____|_|___\\ "}, //pivot "|___|_____|____|_|___\\ "
	{"|              | |    \\"}, //                 ^
	{"`--(o)(o)--------(o)--'"},
	};

	Truck(int x, int y, bufferPtr Buffer = nullptr)
	{
		move(x, y, Buffer);
	}

	void drawSprite()
	{
		for (int Y = this->getY() - 1, j = 0; Y <= this->getY() + 2; ++Y, ++j) {
			for (int X = this->getX() - 10, i = 0; X <= this->getX() + 12; ++X, ++i) {
				this->getBuffer()[Y][X] = sprite[j][i];
			}
		}
	}
};

inline void Vehicle::draw()
{
	{
		if (y_ == 17)
		{
			Truck truck(x_, y_, Buffer_);
			truck.drawSprite();
		}
		else if (y_ == 22)
		{
			Car car(x_, y_, Buffer_);
			car.drawSprite();
		}
	}
}