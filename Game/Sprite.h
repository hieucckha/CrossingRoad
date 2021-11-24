#ifndef _SPRITE
#define _SPRITE
#include "Win32Helper.h"
#include <vector>
#include <fstream>
#include <iostream>

class Sprite
{
private:
	int height, width;
	std::vector<std::vector<char>> sprt;
public:
	Sprite()
	{
		height = width = 0;
	}

	Sprite(const char* dir)
	{
		//Load sprite
		std::fstream inputSprite(dir, std::ios::in);
		if (inputSprite.is_open())
		{
			int height, width;
			inputSprite >> height;
			inputSprite.ignore();
			inputSprite >> width;
			inputSprite.ignore();

			for (int i = 0; i < height; ++i)
			{
				std::vector<char> temp;
				for (int j = 0; j < width; ++j)
				{
					char chr;
					inputSprite.get(chr);
					temp.push_back(chr);
				}
				inputSprite.ignore();
				sprt.push_back(temp);
			}

			inputSprite.close();
		}

		height = sprt.size();
		width = sprt[0].size();
	}
	~Sprite()
	{

	}

	std::vector<char> operator[](int index)
	{
		return sprt[index];
	}

	void openFile(const char* dir)
	{
		//Load sprite
		std::fstream inputSprite(dir, std::ios::in);
		if (inputSprite.is_open())
		{
			int height, width;
			inputSprite >> height;
			inputSprite.ignore();
			inputSprite >> width;
			inputSprite.ignore();

			for (int i = 0; i < height; ++i)
			{
				std::vector<char> temp;
				for (int j = 0; j < width; ++j)
				{
					char chr;
					inputSprite.get(chr);
					temp.push_back(chr);
				}
				inputSprite.ignore();
				sprt.push_back(temp);
			}

			inputSprite.close();
		}
	}

	SHORT getHeight()
	{
		return height;
	}

	SHORT getWidth()
	{
		return width;
	}
};

#endif //_SPRITE