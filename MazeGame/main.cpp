#pragma once
#include "MazeMap.h"
#include "MapPrinter.h"
#include "DfsPathFinder.h"
#include <iostream>
#include "Constant.h"
#include "Point.h"
#include "Cursor.h"
#include "Keyboard.h"
#include "MazeGame.h"

#define PLAY_GAME 1
using namespace std;

void printPathFind();

int** map;
int mapSize = 15;
Point startPos(1, 0);
Point userPos(startPos.x, startPos.y);
Point destPos(mapSize - 2, mapSize - 1);

int main()
{
	cout << "게임을 하려면 1, 보기만 하려면 2번(if you play game press 1, and if you show play game, press 2) \n";
	int gameMode;
	cin >> gameMode;

	MazeMap* mazeMap = new MazeMap();

	for (int i = 0; i < LAST_STAGE; i++)
	{
		mazeMap->setMaze(mapSize);
		map = mazeMap->getMap();
		userPos.x = startPos.x;
		userPos.y = startPos.y;
		destPos.x = mapSize - 2;
		destPos.y = mapSize - 1;

		map[startPos.y][startPos.x] = USER;
		map[destPos.y][destPos.x] = MAZE_DEST;
		Cursor::gotoxy(0, 0);
		MapPrinter::clear(mapSize);
		Cursor::gotoxy(0, 0);
		MapPrinter::print(map, mapSize);

		MazeGame* mazeGame = new MazeGame(map, mapSize, startPos, destPos, userPos);

		if (gameMode == PLAY_GAME)
			mazeGame->play();
		printPathFind();

		// map 메모리 해제
		for (int mapIndex = 0; mapIndex < mapSize; mapIndex++)
			delete map[mapIndex];

		delete map;

		mapSize += 2;
	}

	return 0;
}

void printPathFind()
{
	map[userPos.y][userPos.x] = MAZE_ROAD;
	map[startPos.y][startPos.x] = MAZE_START;
	map[destPos.y][destPos.x] = MAZE_DEST;

	vector<Point*>* results = DfsPathFinder::find(map, mapSize);

	int size = results->size();
	for (int i = 0; i < size; i++)
	{
		Cursor::gotoxy(0, 0);
		Point* point = results->at(i);
		map[point->y][point->x] = MAZE_SOLUTION;
		delete point;

		MapPrinter::print(map, mapSize);

		if (i == 0)	// 처음 한번만 출력
			cout << "\nMaze Solution";
		Sleep(20);
	}
	delete results;
}