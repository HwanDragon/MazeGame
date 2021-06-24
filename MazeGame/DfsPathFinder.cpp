#include "DfsPathFinder.h"

std::vector<Point*>* DfsPathFinder::find(int** map, int mapSize)
{
	// �湮 ���� Ȯ���� ���� visited 2���� �迭�� �����ϰ� �ʱ�ȭ
	bool** visited = new bool* [mapSize];
	for (int i = 0; i < mapSize; i++)
		visited[i] = new bool[mapSize];

	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
			visited[i][j] = false;

	// ������ ��������
	Point* start;
	bool find = false;
	for (int y = 0; y < mapSize; y++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			if (map[y][x] == MAZE_START)
			{
				start = new Point();
				start->x = x;
				start->y = y;
			}
		}
	}

	// dfs Ž��
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	std::vector<Point*>* results = new std::vector<Point*>();	// �̷� ���� ���
	std::stack<Point*> st;
	st.push(start);
	results->push_back(start);
	visited[start->y][start->x] = true;	// ������ �湮���� true�� üũ
	while (st.empty() == false)
	{
		Point* p = st.top();
		st.pop();

		// results �� ��� �ĺ����� ���� �߰��Ͽ����� ���� ���� ���̸� �������� �߰��� �ĺ����� �����ؾ���
		Point* last = results->back();	// ������ ������Ʈ ������
		while ((last->x != p->x) || (last->y != p->y))
		{
			results->pop_back();
			last = results->back();
		}

		for (int dIndex = 0; dIndex < 4; dIndex++)
		{
			int tempX = dx[dIndex] + p->x;
			int tempY = dy[dIndex] + p->y;
			if (tempX < 0 || tempY < 0 || tempX >= mapSize || tempY >= mapSize)	// �迭�� �ʰ��� ���
				continue;

			if (map[tempY][tempX] == MAZE_WALL)	// �̷��� ���ϰ�� 
				continue;

			if (visited[tempY][tempX] == true)	// �̹� �湮�ߴ� ������ ���
				continue;

			visited[tempY][tempX] = true;
			Point* tempPoint = new Point(tempX, tempY);
			st.push(tempPoint);
			results->push_back(tempPoint);
		}

		if (map[p->y][p->x] == MAZE_DEST)
			break;
	}

	while (st.empty() == false)
	{
		Point* noSearchObject = st.top();
		st.pop();
		results->erase(std::remove(results->begin(), results->end(), noSearchObject));
	}

	// �湮���� �޸� ����
	if (visited != nullptr)
	{
		for (int i = 0; i < mapSize; i++)
			delete visited[i];
	}

	return results;
}