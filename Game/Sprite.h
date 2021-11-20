#ifndef _SPRITE
#define _SPRITE
#include "Win32Helper.h"
#include <vector>
#include <fstream>
#include <iostream>

class Sprite
{
private:
	std::vector<std::vector<char>> sprt;
public:
	Sprite()
	{
	}

	Sprite(const char* dir)
	{
		//Load sprite
		std::fstream inputSprite(dir, std::ios::in);
		if (inputSprite.is_open())
		{
			int len, wid;
			inputSprite >> len;
			inputSprite.ignore();
			inputSprite >> wid;
			inputSprite.ignore();

			for (int i = 0; i < len; ++i)
			{
				std::vector<char> temp;
				for (int j = 0; j < wid; ++j)
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
			int len, wid;
			inputSprite >> len;
			inputSprite.ignore();
			inputSprite >> wid;
			inputSprite.ignore();

			for (int i = 0; i < len; ++i)
			{
				std::vector<char> temp;
				for (int j = 0; j < wid; ++j)
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
		return sprt.size();
	}

	SHORT getWidth()
	{
		return sprt[0].size();
	}
};

#endif //_SPRITE