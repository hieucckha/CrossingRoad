#pragma once
#include "../../SceneAndPoint2D/Point2D.h"
//#include "Animal.h"
//#include "Vehicle.h"
#include "../EnemyRow/EnemyRow.h"
//#include "Pixel.h"
#include "../../ConstantAndDefine/Define.h"

#include <vector>

class Player
{
private:
	// At the top left
	Point2D coord_;
	bool state_;

public:
	friend class Player;
	// Maybe change this the default location
	Player() : state_(true)
	{
		coord_.setBoth(52, 37);
	}
	~Player() = default;

	void reset()
	{
		coord_.setBoth(52, 37);
	}
	void setCoord(int x, int y)
	{
		coord_.setBoth(x, y);
	}
	void setStateTrue()
	{
		state_ = true;
	}
	void setStateFalse()
	{
		state_ = false;
	}

	Point2D& getCoord()
	{
		return coord_;
	}
	bool getState()
	{
		return state_;
	}

	void move(DIRECTION_PLAYER direct)
	{
		switch (direct)
		{
		case DIRECTION_PLAYER::LEFT_DIRECTION:
			if (coord_.getX() > MapLeftCol + 1)
				coord_.setX(coord_.getX() - 1);
			break;
		case DIRECTION_PLAYER::TOP_DIRECTION:
			if (coord_.getY() > MapTopRow + 2)
				coord_.setY(coord_.getY() - 5);
			break;
		case DIRECTION_PLAYER::RIGHT_DIRECTION:
			if (coord_.getX() < MapRightCol - 1 - 5)
				coord_.setX(coord_.getX() + 1);
			break;
		case DIRECTION_PLAYER::BOTTOM_DIRECTION:
			if (coord_.getY() < MapBottomRow - 2 - 5)
				coord_.setY(coord_.getY() + 5);
			break;
		default:
			break;
		}
	}
	bool checkCollistion(EnemyRow& enemyRow, int playerRow)
	{
		if (playerRow == 0 || playerRow == 7)
			return false;

		OneRow* oneRow = enemyRow.getListRow()[playerRow - 1];
		for (auto& mem : oneRow->getEnemyList())
		{
			Point2D coord = mem->getCoord();

			// Bird
			if (dynamic_cast<Bird*>(mem) != nullptr)
			{
				// Right
				if (oneRow->getDirection())
				{
					// Enemy -> Player
					if (coord.getX() < coord_.getX())
					{
						if (coord.getX() + 4 >= coord_.getX())
							return true;
					}

					if (coord.getX() == coord_.getX())
						return true;

					// Player -> Enemy
					if (coord.getX() > coord_.getX())
					{
						if (coord_.getX() + 4 >= coord.getX())
							return true;
					}
				// Left
				}
				else
				{
					// Player -> Enemy
					if (coord.getX() > coord_.getX())
					{
						if (coord_.getX() + 4 >= coord.getX())
							return true;
					}

					if (coord.getX() == coord_.getX())
						return true;

					// Enemy -> Player
					if (coord.getX() < coord_.getX())
					{
						if (coord.getX() + 4 >= coord_.getX())
							return true;
					}
				}
			// 
			}
			else
			{
				// Right
				if (oneRow->getDirection())
				{
					// Enemy -> Player
					if (coord.getX() < coord_.getX())
					{
						if (coord.getX() + 11 >= coord_.getX())
							return true;
					}

					if (coord.getX() == coord_.getX())
						return true;

					// Player -> Enemy
					if (coord.getX() > coord_.getX())
					{
						if (coord_.getX() + 4 >= coord.getX())
							return true;
					}
				// Left
				}
				else
				{
					// Player -> Enemy
					if (coord.getX() > coord_.getX())
					{
						if (coord_.getX() + 4 >= coord.getX())
							return true;
					}

					if (coord.getX() == coord_.getX())
						return true;

					// Enemy -> Player
					if (coord.getX() < coord_.getX())
					{
						if (coord.getX() + 11 >= coord_.getX())
							return true;
					}
				}
			}
		}

		return false;
	}
};



