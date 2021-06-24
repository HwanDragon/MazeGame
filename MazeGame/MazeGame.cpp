#include "MazeGame.h"

MazeGame::MazeGame(int** map, int mapSize, Point startPos, Point destPos, Point userPos)
{
	this->map = map;
	this->mapSize = mapSize;
	this->startPos.x = startPos.x;
	this->startPos.y = startPos.y;
	this->destPos.x = destPos.x;
	this->destPos.y = destPos.y;
	this->userPos.x = userPos.x;
	this->userPos.y = userPos.y;
}

bool MazeGame::play()
{
	Point prevPos;
	bool clear = false;
	while (true)
	{
		char c = Keyboard::getKeyboardArrowInput();
		switch (c)
		{
		case LEFT:
			if (isRoad(map, mapSize, userPos.x - 1, userPos.y) == true)
			{
				prevPos.x = userPos.x;
				prevPos.y = userPos.y;
				userPos.x -= 1;
				Cursor::gotoxy(0, 0);
				updateMap(map, userPos, prevPos);
				MapPrinter::print(map, mapSize);
				clear = isFinish(map, mapSize, userPos.x, userPos.y);
			}
			break;
		case RIGHT:
			if (isRoad(map, mapSize, userPos.x + 1, userPos.y) == true)
			{
				prevPos.x = userPos.x;
				prevPos.y = userPos.y;
				userPos.x += 1;
				Cursor::gotoxy(0, 0);
				updateMap(map, userPos, prevPos);
				MapPrinter::print(map, mapSize);
				clear = isFinish(map, mapSize, userPos.x, userPos.y);
			}
			break;
		case UP:
			if (isRoad(map, mapSize, userPos.x, userPos.y - 1) == true)
			{
				prevPos.x = userPos.x;
				prevPos.y = userPos.y;
				userPos.y -= 1;
				Cursor::gotoxy(0, 0);
				updateMap(map, userPos, prevPos);
				MapPrinter::print(map, mapSize);
				clear = isFinish(map, mapSize, userPos.x, userPos.y);
			}
			break;
		case DOWN:
			if (isRoad(map, mapSize, userPos.x, userPos.y + 1) == true)
			{
				prevPos.x = userPos.x;
				prevPos.y = userPos.y;
				userPos.y += 1;
				Cursor::gotoxy(0, 0);
				updateMap(map, userPos, prevPos);
				MapPrinter::print(map, mapSize);
				clear = isFinish(map, mapSize, userPos.x, userPos.y);
			}
			break;
		default:
			break;
		}

		if (clear == true)
			break;
	}

	return true;
}

void MazeGame::updateMap(int** map, Point userPos, Point prevUserPos)
{
	if ((prevUserPos.x == startPos.x) && (prevUserPos.y == startPos.y))
	{
		map[prevUserPos.y][prevUserPos.x] = MAZE_START;
	}
	else
	{
		map[prevUserPos.y][prevUserPos.x] = MAZE_ROAD;
	}

	map[userPos.y][userPos.x] = USER;
}

bool MazeGame::isRoad(int** map, int mapSize, int x, int y)
{
	if (x < 0 || y < 0 || x >= mapSize || y >= mapSize)
		return false;

	if (map[y][x] == MAZE_WALL)
		return false;
	return true;
}

bool MazeGame::isFinish(int** map, int mapSize, int x, int y)
{
	if (x < 0 || y < 0 || x >= mapSize || y >= mapSize)
		return false;

	if ((x == destPos.x) && (y == destPos.y))
		return true;
	return false;
}