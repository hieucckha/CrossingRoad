#ifndef _ROW
#define _ROW
#pragma once
#include "Animal.h"
#include "Vehicle.h"

class Row
{
private:
	int x_coord;
	int entitySpeed;
	int reLightTime;
	bool isFromRight;
	bool isRedLight;
	std::vector<Entity*> inhabitance;
public:
	Row(int x)
	{
		x_coord = x;
	}
};
#endif // _ROW