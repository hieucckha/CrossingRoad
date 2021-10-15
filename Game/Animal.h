#pragma once

typedef char(*bufferPtr)[120];

class Animal
{
private:
	int x_, y_;
	char(*Buffer_)[120];

public:
	/// <summary>
	/// Move the coordinate of Animal to x and y, save to Buffer
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

	void virtual drawSprite()
	{
		return;
	}
};

class Bird : public Animal
{
public:
	const char sprite[4][12] = {
		{"     __   "},
		{"    /  7  "}, //pivot "    /  7  "
		{"<()/____7 "}, //           ^
		{" '------\"\""}
	};

	Bird(int x, int y, bufferPtr Buffer = nullptr)
	{
		move(x, y, Buffer);
	}

	void drawSprite() override
	{
		for (int Y = this->getY() - 1, j = 0; Y <= this->getY() + 2; ++Y, ++j) {
			for (int X = this->getX() - 4, i = 0; X <= this->getX() + 5; ++X, ++i) {
				if (X <= 0 || X > 78)
					continue;
				this->getBuffer()[Y][X] = sprite[j][i];
			}
		}
	}
};

class Dinosaur : public Animal
{
public:
	const char sprite[4][14] = {
		{" __          "},
		{"(_ \\_/\\/\\__  "}, //pivot "(_ \\_/\\/\\__  "
		{"  \\   _    \\ "},  //             ^
		{"   |_| |_|'-\\"}
	};
	Dinosaur(int x, int y, bufferPtr Buffer = nullptr)
	{
		move(x, y, Buffer);
	}

	void drawSprite() override
	{
		for (int Y = this->getY() - 1, j = 0; Y <= this->getY() + 2; ++Y, ++j) {
			for (int X = this->getX() - 5, i = 0; X <= this->getX() + 7; ++X, ++i) {
				if (X <= 0 || X > 78)
					continue;
				this->getBuffer()[Y][X] = sprite[j][i];
			}
		}
	}
};
