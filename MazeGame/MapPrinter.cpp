#include "MapPrinter.h"

void MapPrinter::clear(int mapSize)
{
	for (int y = 0; y < mapSize; y++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			std::cout << "  ";
		}
		std::cout << "\n";
	}
}

void MapPrinter::print(int** map, int mapSize)
{
	if (map == nullptr)
		return;

	for (int y = 0; y < mapSize; y++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			switch (map[y][x])
			{
			case MAZE_ROAD:
				std::cout << "  ";
				break;
			case MAZE_WALL:
				std::cout << "¡á";
				break;
			case MAZE_DEST:
				std::cout << "¢Ì";
				break;
			case MAZE_START:
				std::cout << "¡Ú";
				break;
			case MAZE_SOLUTION:
				std::cout << "¡Ý";
				break;
			case USER:
				std::cout << "¢À";
				break;
			default:
				break;
			}
		}
		std::cout << "\n";
	}
}