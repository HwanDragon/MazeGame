#pragma once
#include <vector>
#include <stack>
#include "Point.h"
#include "Constant.h"

class DfsPathFinder
{
public:
	static std::vector<Point*>* find(int** map, int mapSize);
};