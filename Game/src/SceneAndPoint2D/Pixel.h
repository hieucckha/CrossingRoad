#pragma once
#include "../WindowsConsole/Win32Helper.h"

class Pixel
{
public:
	Pixel()
	{
		_content = ' ';
		_bafoGround = BG_BLACK | FG_WHITE;
	}
public:
	unsigned char _content;
	unsigned char _bafoGround;
};

