#pragma once

struct Position
{
	Position(float x, float y) : x{ x }, y{ y } {}
	float x, y;
	bool operator==(const Position& rhs)
	{
		return x == rhs.x && y == rhs.y;
	}
};


