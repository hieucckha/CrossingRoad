#pragma once
#include "OneRow.h"
#include "Define.h"

#include <vector>
class EnemyRow
{
private:
	std::vector<OneRow*> listRow_;
public:
	EnemyRow()
	{
		init(0);
	}
	~EnemyRow()
	{
		cleanRow();
	}

	// how many enemy on row
	// will be gen here!
	void init(int level)
	{
		for (int i = 2; i < MAXIMUN_ENEMY_ROW + 2; ++i)
			listRow_.push_back(new OneRow(level, i));

		for (auto& mem : listRow_)
		{
			// Push ... enemy on one row
			if (g_isHard)
			{
				// 4 + each 3 level increase one
				for (int i = 0; i < 4 + (level - level % 3) / 3; ++i)
					mem->addEnemy();
			}
			else
			{
				// 3 + each 5 level increase one
				for (int i = 0; i < 3 + (level - level % 5) / 5; ++i)
					mem->addEnemy();
			}
		}
	}
	void cleanRow()
	{
		size_t size = listRow_.size();
		for (auto& mem : listRow_)
			delete mem;

		for (size_t i = 0; i < size; ++i)
			listRow_.pop_back();
	}

	std::vector<OneRow*>& getListRow()
	{
		return listRow_;
	}
	// Index of listRow_ not the index of row on picture
	void update(int tick, int playerRow, int index, int level)
	{
		if (tick % listRow_[index]->getRedLightTime() == 0)
		{
			listRow_[index]->toggleRedLight();
			listRow_[index]->setNewRedLightTime(level);
		}
		if (tick % listRow_[index]->getSpeed() == 0)
		{
			listRow_[index]->move();
		}
	}
	void setLevel(int level)
	{
		cleanRow();
		init(level);
	}
};

