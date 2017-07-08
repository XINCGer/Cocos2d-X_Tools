#ifndef __NEWMAP_H__
#define __NEWMAP_H__

#include "cocos2d.h"
#include "MapItem.h"
USING_NS_CC;

#define MAPSIZE 23

class NewMap :public Node
{
public:
	int allNum;
	int maze[MAPSIZE+2][MAPSIZE+2];
	Sprite* map[MAPSIZE+2][MAPSIZE+2];
	void mapInit();
	void makeMaze(int x, int y);
	void makeBorder();
	void moveTo();
	int getMaze(int x,int y);
	static NewMap* createMap();
	virtual bool init();
	CREATE_FUNC(NewMap);
};

#endif