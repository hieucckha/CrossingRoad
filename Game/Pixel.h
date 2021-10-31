#pragma once
#include "Win32Helper.h"

class Pixel
{
private:
	char content_;
	unsigned char foreground_, background_;

public:
	friend class Scene;
	Pixel()
	{
		content_ = ' ';
		foreground_ = FOREGROUND_WHITE;
		background_ = BACKGROUND_BLACK;
	}

	void setContent(char chr)
	{
		content_ = chr;
	}
	void setForeGround(unsigned char color)
	{
		foreground_ = color;
	}
	void setBackground(unsigned char color)
	{
		background_ = color;
	}
	char& getContent()
	{
		return content_;
	}
	unsigned char getForeground() const
	{
		return foreground_;
	}
	unsigned char getBackground() const
	{
		return background_;
	}
};

