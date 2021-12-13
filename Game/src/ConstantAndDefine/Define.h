#pragma once

constexpr auto MapLeftCol = 5;
constexpr auto MapTopRow = 0;
constexpr auto MapRightCol = 105;
constexpr auto MapBottomRow = 42;

#define MAXIMUN_ENEMY_ROW 6

enum class DIRECTION_PLAYER
{
	LEFT_DIRECTION, TOP_DIRECTION, RIGHT_DIRECTION, BOTTOM_DIRECTION,
};

static bool g_isPause = false;
static bool g_isHard = false;

