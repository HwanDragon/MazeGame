#pragma once
#include<iostream>
#include "Constant.h"

class MapPrinter
{
public:
	static void print(int** map, int mapSize);	// �̷� ���
	static void clear(int mapSize);	// ȭ�� Ŭ����
};