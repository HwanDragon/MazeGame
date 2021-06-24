#pragma once
#include "Room.h"
#include "Constant.h"
#include<stack>
#include<vector>
#include<iostream>

class MazeMap
{
private:
	int mazeSize;	// ¹Ì·Î Å©±â
	int mapSize;
	int** map;	// ¸Ê
	Room** maze;

	void init(int mazeMapSize);
	void initMaze();
	void initMap();
	void createMaze(int startX, int startY);
	//void createMaze2(int startX, int startY);
	void createMap();
	void clear();
public:
	virtual ~MazeMap();
	void setMaze(int mazeMapSize);
	int** getMap();
};