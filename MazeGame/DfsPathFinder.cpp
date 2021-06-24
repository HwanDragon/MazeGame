#include "DfsPathFinder.h"

std::vector<Point*>* DfsPathFinder::find(int** map, int mapSize)
{
	// 방문 여부 확인을 위해 visited 2차원 배열을 생성하고 초기화
	bool** visited = new bool* [mapSize];
	for (int i = 0; i < mapSize; i++)
		visited[i] = new bool[mapSize];

	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
			visited[i][j] = false;

	// 시작점 가져오기
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

	// dfs 탐색
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	std::vector<Point*>* results = new std::vector<Point*>();	// 미로 순서 기록
	std::stack<Point*> st;
	st.push(start);
	results->push_back(start);
	visited[start->y][start->x] = true;	// 시작점 방문여부 true로 체크
	while (st.empty() == false)
	{
		Point* p = st.top();
		st.pop();

		// results 에 모든 후보지를 전부 추가하였으니 만약 막힌 길이면 그전까지 추가한 후보지를 제거해야함
		Point* last = results->back();	// 마지막 오브젝트 가져옴
		while ((last->x != p->x) || (last->y != p->y))
		{
			results->pop_back();
			last = results->back();
		}

		for (int dIndex = 0; dIndex < 4; dIndex++)
		{
			int tempX = dx[dIndex] + p->x;
			int tempY = dy[dIndex] + p->y;
			if (tempX < 0 || tempY < 0 || tempX >= mapSize || tempY >= mapSize)	// 배열을 초과할 경우
				continue;

			if (map[tempY][tempX] == MAZE_WALL)	// 미로의 벽일경우 
				continue;

			if (visited[tempY][tempX] == true)	// 이미 방문했던 지역일 경우
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

	// 방문여부 메모리 해제
	if (visited != nullptr)
	{
		for (int i = 0; i < mapSize; i++)
			delete visited[i];
	}

	return results;
}