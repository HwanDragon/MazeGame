#include "MazeMap.h"
#include <ctime>
/*
* dfs�� �̿��� �̷� ���� �˰��� ����
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
*
* ���� �׸����� ��� ���̰�, �� �� ����ڰ� ������ �� �ִ� Room(��� �Ǵ� ��)�̴�
* �̷� ������ ���ؼ� �� ���� ���� ����� �����ϰ� ���� �վ� �̷θ� ��Ÿ���� �ȴ�.
* ���� �̷ο��� �� �� �����ͼ� ǥ���ϸ� �Ʒ��� ����.
*
* �� �� �� �� ��
* �� �� �� �� ��
* �� �� �� �� ��
* �� �� �� �� ��
* �� �� �� �� ��
*
* �� map size�� 11 �̸� , ���� �ձ� ���� Room�� size�� map size / 2 - 1 �� �ȴ�
* ���� ��ε鿡�� dfs�� �̿��� �����ϰ� ��θ� �վ��ְ�,
* �ش� ������ ���� map�� �ݿ��ϸ� �̷ΰ� �����Ǵ� ���̴�.
*
* ����������
*         ��
* ����������
* ��
* ����������
*         ��
* ����������
* ��
* ����������
*
* ���� dfs Ž�� ������ ���� ���ٸ�, Ž�� ������ ����ϰ�, �ش� ������ map�� �ݿ��ϸ� ����������
*
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
* �� �� �� �� �� �� �� �� �� �� ��
*
*
* ������, �Ϲ����� dfs�� ����ϰ� �Ǹ�, Ž�� ������ �������� �ڽ� �ĺ����� �̸� stack�� �߰��ϱ� ������,
* �̻۸���� �̷ΰ� ������ �ʰԵ�. ����, �̷� Ž�� ������������ ���� �������� Ž���ϴٰ� ���� ���� ���̻� Ž����
* �� ���� ��� ���������� ���ƿͼ� �ٸ� �ĺ����� �ִ��� Ž���Ͽ� �̷θ� �Լ� �����ϴ� ��� ���
*
*/
// �ش� �˰��򿡼� ��ü ���� map�̶� �ϰ�, Room���� ������ ��Ƶа��� maze�� Ī��


void MazeMap::init(int mazeMapSize)
{
	this->mapSize = mazeMapSize;

	if (this->mapSize % 2 == 0)	// �� ũ��� �׻� Ȧ���� ����
		this->mapSize = this->mapSize + 1;

	mazeSize = (mapSize - 1) / 2;
	initMaze();
	createMaze(mazeSize / 2, mazeSize / 2);	// 0, 0�������� �̷λ��� ����
}

void MazeMap::initMaze()
{
	// maze �ʱ�ȭ
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

	// dfs����
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

		// �ĺ��� ���� (��, �Ʒ�, ���� , ������)
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

			int randomIndex = rand() % points.size();	// ���� �ε��� ����
			Point p = points.at(randomIndex);	// �ĺ����� �������� ������
			points.erase(points.begin() + randomIndex);	// ���� �ĺ��� ����
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
					break;	 // ��� �ĺ����� ���� �߰��ϸ� �̷ΰ� �̻ڰ� ������ �ʾ� �ϳ��� �߰� - (1��)
				}
			}
		}

		// ���� �������� �ٴٶ����� ���������� �̵��Ͽ� �ٸ� �ĺ����� ������ �ѹ� �� �����Ѵ�
		// ���������� �̵����� �ʰ� dfs �� �� ��츦 ��������� (1��) �ڵ��� break; �� �ּ� ó���ϰ�, 
		// �Ʒ� �ڵ带 �ּ�ó���ϸ��
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
	// Map �ʱ�ȭ
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
/// �޸� ����
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

	// dfs����
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

		// �ĺ��� ���� (��, �Ʒ�, ���� , ������)
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

			int randomIndex = rand() % points.size();	// ���� �ε��� ����
			Point p = points.at(randomIndex);	// �ĺ����� �������� ������
			points.erase(points.begin() + randomIndex);	// ���� �ĺ��� ����
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