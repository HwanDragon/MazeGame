#pragma once
#include<iostream>
#include "Constant.h"

class MapPrinter
{
public:
	static void print(int** map, int mapSize);	// 미로 출력
	static void clear(int mapSize);	// 화면 클리어
};