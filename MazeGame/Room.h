#pragma once
#include "Point.h"

class Room
{
public:
	Room()
	{
		current.x = -1;
		current.y = -1;
		visited = false;
		prevRoom = nullptr;
	}
	Point current;	// 현재 방의 위치
	Room* prevRoom;	// 이전방 주소 
	bool visited;	// 방문 했는지 여부 저장
};