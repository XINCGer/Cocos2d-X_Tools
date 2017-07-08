#ifndef __WALL_H__
#define __WALL_H__

#include "cocos2d.h"
#include "Monstro.h"
USING_NS_CC;

class MapItem :public Node
{
public:
	int type;
	Sprite* mapItem;
	void addWallImg(int type, float x, float y);
	void addMonstorImg(int tag, int type, float x, float y);
	void addSK3Img(float x, float y);
	static MapItem* createWall();
	virtual bool init();
	CREATE_FUNC(MapItem);
};

#endif