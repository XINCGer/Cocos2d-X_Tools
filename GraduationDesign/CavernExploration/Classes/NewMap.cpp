#include "NewMap.h"

NewMap* NewMap::createMap()
{
	NewMap* map = new NewMap();
	if (map && map->init())
	{
		map->autorelease();
		map->mapInit();
		return map;
	}
	CC_SAFE_DELETE(map);
	return NULL;
}
bool NewMap::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}
void NewMap::mapInit()
{	
	allNum = 0; //
	while (allNum < 99)
	{
		memset(maze, 0, sizeof(maze));
		allNum = 0;
		makeBorder();
	}
}

//设置外边框
void NewMap::makeBorder()
{
	for (int i = 0; i < MAPSIZE; i++)
	{
		maze[0][i] = 1;
		maze[i][0] = 1;
		maze[MAPSIZE-1][i] = 1;
		maze[i][MAPSIZE-1] = 1;
	}
	maze[2][1] = 1;
	maze[MAPSIZE - 3][MAPSIZE - 2] = 1;
	srand((unsigned)time(NULL));
	makeMaze(rand() % MAPSIZE / 2 + 1, rand() % MAPSIZE / 2 + 1);
}
//设置里面的迷宫
void NewMap::makeMaze(int x, int y)
{
	int d[4][2] = { 1, 0, 0, 1, -1, 0, 0, -1 };
	int zx = x * 2;
	int zy = y * 2;
	int next, turn, i;
	maze[zx][zy] = 1;
	turn = rand() % 2 ? 1 : 3;
	for (i = 0, next = rand() % 4; i < 4; i++, next = (next + turn) % 4)
	{
		if (maze[zx + 2 * d[next][0]][zy + 2 * d[next][1]] == 0)
		{
			allNum++;
			if ((zx + d[next][0] > MAPSIZE)||(zy + d[next][1] > MAPSIZE))
			{
				break;
			}
			maze[zx + d[next][0]][zy + d[next][1]] = 1;
			makeMaze(x + d[next][0], y + d[next][1]);
		}
	}
}
int NewMap::getMaze(int x,int y)
{
	return maze[x][y];
}