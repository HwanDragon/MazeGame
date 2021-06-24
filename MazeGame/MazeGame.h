#pragma once
#include "Keyboard.h"
#include "Constant.h"
#include "Cursor.h"
#include "MapPrinter.h"
#include "Point.h"

class MazeGame
{
private:
	void updateMap(int** map, Point userPos, Point prevUserPos);
	bool isRoad(int** map, int mapSize, int x, int y);
	bool isFinish(int** map, int mapSize, int x, int y);
	int** map;
	int mapSize;
	Point startPos;
	Point destPos;
	Point userPos;
public:
	MazeGame(int** map, int mapSize, Point startPos, Point destPos, Point userPos);
	bool play();
};