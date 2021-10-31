#pragma once

class Point2D
{
private:
	int x_, y_;

public:
	Point2D() : x_(0), y_(0)
	{}

	Point2D(int x, int y) : x_(0), y_(0)
	{}

	void setX(int x)
	{
		x_ = x;
	}
	void setY(int y)
	{
		y_ = y;
	}
	void setBoth(int x, int y)
	{
		x_ = x;
		y_ = y;
	}

	int getX()
	{
		return x_;
	}
	int getY()
	{
		return y_;
	}
};

