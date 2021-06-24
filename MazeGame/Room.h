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
	Point current;	// ���� ���� ��ġ
	Room* prevRoom;	// ������ �ּ� 
	bool visited;	// �湮 �ߴ��� ���� ����
};