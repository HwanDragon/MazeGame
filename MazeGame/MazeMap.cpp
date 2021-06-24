#include "MazeMap.h"
#include <ctime>
/*
* dfs를 이용한 미로 생성 알고리즘 설명
* ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■
* ■ □ ■ □ ■ □ ■ □ ■ □ ■
* ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■
* ■ □ ■ □ ■ □ ■ □ ■ □ ■
* ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■
* ■ □ ■ □ ■ □ ■ □ ■ □ ■
* ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■
* ■ □ ■ □ ■ □ ■ □ ■ □ ■
* ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■
* ■ □ ■ □ ■ □ ■ □ ■ □ ■
* ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■
*
* 위의 그림에서 ■는 벽이고, □ 는 사용자가 지나갈 수 있는 Room(통로 또는 방)이다
* 미로 생성을 위해서 □ 에서 다음 □까지 랜덤하게 길을 뚫어 미로를 나타내면 된다.
* 위의 미로에서 □ 만 가져와서 표현하면 아래와 같다.
*
* □ □ □ □ □
* □ □ □ □ □
* □ □ □ □ □
* □ □ □ □ □
* □ □ □ □ □
*
* 즉 map size가 11 이면 , 길을 뚫기 위한 Room의 size는 map size / 2 - 1 이 된다
* 위의 통로들에서 dfs를 이용해 랜덤하게 통로를 뚫어주고,
* 해당 내용을 실제 map에 반영하면 미로가 생성되는 것이다.
*
* □→□→□→□→□
*         ↓
* □←□←□←□←□
* ↓
* □→□→□→□→□
*         ↓
* □←□←□←□←□
* ↓
* □→□→□→□→□
*
* 만약 dfs 탐색 순서가 위와 같다면, 탐색 순서를 기록하고, 해당 내용을 map에 반영하면 다음과같다
*
* ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■
* ■ □ □ □ □ □ □ □ □ □ ■
* ■ ■ ■ ■ ■ ■ ■ ■ ■ □ ■
* ■ □ □ □ □ □ □ □ □ □ ■
* ■ □ ■ ■ ■ ■ ■ ■ ■ ■ ■
* ■ □ □ □ □ □ □ □ □ □ ■
* ■ ■ ■ ■ ■ ■ ■ ■ ■ □ ■
* ■ □ □ □ □ □ □ □ □ □ ■
* ■ □ ■ ■ ■ ■ ■ ■ ■ ■ ■
* ■ □ □ □ □ □ □ □ □ □ ■
* ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■
*
*
* 하지만, 일반적인 dfs를 사용하게 되면, 탐색 지점을 기점으로 자식 후보들을 미리 stack에 추가하기 때문에,
* 이쁜모양의 미로가 나오지 않게됨. 따라서, 미로 탐색 시작지점에서 한쪽 방향으로 탐색하다가 길이 막혀 더이상 탐색할
* 수 없는 경우 이전방으로 돌아와서 다른 후보지가 있는지 탐색하여 미로를 게속 생성하는 방법 사용
*
*/
// 해당 알고리즘에서 전체 맵을 map이라 하고, Room들의 집합을 모아둔것을 maze라 칭함


void MazeMap::init(int mazeMapSize)
{
	this->mapSize = mazeMapSize;

	if (this->mapSize % 2 == 0)	// 맵 크기는 항상 홀수로 맞춤
		this->mapSize = this->mapSize + 1;

	mazeSize = (mapSize - 1) / 2;
	initMaze();
	createMaze(mazeSize / 2, mazeSize / 2);	// 0, 0에서부터 미로생성 시작
}

void MazeMap::initMaze()
{
	// maze 초기화
	maze = new Room * [mazeSize];
	for (int i = 0; i < mazeSize; i++)
		maze[i] = new Room[mazeSize];

	for (int i = 0; i < mazeSize; i++)
	{
		for (int j = 0; j < mazeSize; j++)
		{
			Room temp = maze[i][j];
			temp.visited = false;
			temp.current.y = i;
			temp.current.x = j;
			maze[i][j] = temp;
		}
	}
}

void MazeMap::createMaze(int startX, int startY)
{
	srand(time(NULL));

	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };

	// dfs시작
	Room* r = &maze[startY][startX];
	r->visited = true;
	std::stack<Room*> st;
	st.push(r);
	while (st.empty() == false)
	{
		Room* room = st.top();
		st.pop();
		room->visited = true;
		Point currentPoint = room->current;

		// 후보지 생성 (위, 아래, 왼쪽 , 오른쪽)
		std::vector<Point> points;
		for (int i = 0; i < 4; i++) {
			int x = dx[i] + currentPoint.x;
			int y = dy[i] + currentPoint.y;
			Point tempPoint;
			tempPoint.x = x;
			tempPoint.y = y;
			points.push_back(tempPoint);
		}

		while (true)
		{
			if (points.size() == 0)
				break;

			int randomIndex = rand() % points.size();	// 랜덤 인덱스 생성
			Point p = points.at(randomIndex);	// 후보지는 랜덤으로 꺼내옴
			points.erase(points.begin() + randomIndex);	// 꺼낸 후보지 삭제
			int x = p.x;
			int y = p.y;
			if ((x >= 0) && (y >= 0) && (x < mazeSize) && (y < mazeSize))
			{
				if (maze[y][x].visited == false)
				{
					Room* next = &maze[y][x];
					next->prevRoom = room;
					maze[y][x].visited = true;
					st.push(next);
					break;	 // 모든 후보지를 전부 추가하면 미로가 이쁘게 나오지 않아 하나만 추가 - (1번)
				}
			}
		}

		// 만약 막힌곳에 다다랐으면 이전방으로 이동하여 다른 후보지가 없는지 한번 더 점검한다
		// 이전방으로 이동하지 않고 dfs 를 할 경우를 보고싶으면 (1번) 코드의 break; 를 주석 처리하고, 
		// 아래 코드를 주석처리하면됨
		if (st.empty() == true)
		{
			Room* prev = room->prevRoom;
			if (prev->prevRoom != nullptr)
			{
				createMaze(prev->current.x, prev->current.y);
			}
		}
	}
}

void MazeMap::initMap()
{
	// Map 초기화
	map = new int* [mapSize];
	for (int i = 0; i < mapSize; i++)
		map[i] = new int[mapSize];

	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
			map[i][j] = MAZE_WALL;
}

void MazeMap::createMap()
{
	for (int y = 0; y < mazeSize; y++)
	{
		for (int x = 0; x < mazeSize; x++)
		{
			map[2 * y + 1][2 * x + 1] = MAZE_ROAD;
		}
	}

	for (int y = 0; y < mazeSize; y++)
	{
		for (int x = 0; x < mazeSize; x++)
		{
			Room currentRoom = maze[y][x];
			if (currentRoom.prevRoom == nullptr)
				continue;
			Room* prevRoom = currentRoom.prevRoom;
			int cX = currentRoom.current.x * 2 + 1;
			int cY = currentRoom.current.y * 2 + 1;
			int pX = prevRoom->current.x * 2 + 1;
			int pY = prevRoom->current.y * 2 + 1;

			map[(cY + pY) / 2][(cX + pX) / 2] = MAZE_ROAD;
		}
	}
}

/// <summary>
/// 메모리 해제
/// </summary>
void MazeMap::clear()
{
	if (maze != nullptr)
	{
		for (int i = 0; i < mazeSize; i++)
			delete maze[i];

		delete maze;
	}
}

MazeMap::~MazeMap()
{
	clear();
}

void MazeMap::setMaze(int mazeMapSize)
{
	clear();
	init(mazeMapSize);
	initMap();
	createMap();
}

int** MazeMap::getMap()
{
	return map;
}



/*
void MazeMap::createMaze2(int startX, int startY)
{
	srand(time(NULL));

	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };

	// dfs시작
	Room* r = &maze[startY][startX];
	stack<Room*> st;
	st.push(r);
	while (st.empty() == false)
	{
		Room* room = st.top();
		st.pop();

		if (room->visited == true)
			continue;

		room->visited = true;
		Point currentPoint = room->current;

		// 후보지 생성 (위, 아래, 왼쪽 , 오른쪽)
		vector<Point> points;
		for (int i = 0; i < 4; i++) {
			int x = dx[i] + currentPoint.x;
			int y = dy[i] + currentPoint.y;
			Point tempPoint;
			tempPoint.x = x;
			tempPoint.y = y;
			points.push_back(tempPoint);
		}

		while (true)
		{
			if (points.size() == 0)
				break;

			int randomIndex = rand() % points.size();	// 랜덤 인덱스 생성
			Point p = points.at(randomIndex);	// 후보지는 랜덤으로 꺼내옴
			points.erase(points.begin() + randomIndex);	// 꺼낸 후보지 삭제
			int x = p.x;
			int y = p.y;
			if ((x >= 0) && (y >= 0) && (x < mazeSize) && (y < mazeSize))
			{
				if (maze[y][x].visited == false)
				{
					Room* next = &maze[y][x];
					next->prevRoom = room;
					st.push(next);
				}
			}
		}
	}
}
*/