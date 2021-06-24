#pragma once
class Point
{
public:
	int x;
	int y;
	Point()
	{
		this->x = -1;
		this->y = -1;
	}

	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};