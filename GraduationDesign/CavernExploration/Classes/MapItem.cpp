#include "MapItem.h"

MapItem* MapItem::createWall()
{
	MapItem* mapItem = new MapItem();
	if (mapItem && mapItem->init())
	{
		mapItem->autorelease();
		return mapItem;
	}
	CC_SAFE_DELETE(mapItem);
	return NULL;
}
bool MapItem::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}
void MapItem::addWallImg(int type, float y, float x) //生成墙图片
{
	this->type = type;
	mapItem = Sprite::create(String::createWithFormat("wall%d.png", type)->getCString());
	mapItem->setPosition(40 * x - 20, 860 - 40 * y);
	addChild(mapItem);
}

void MapItem::addMonstorImg(int tag, int type, float x, float y) //生成敌人图片
{
	CCLOG("monstro create at %f, %f and tag=%d, type=%d", x, y, tag, type);
	this->type = type;
	auto* monstro = Monstro::createMonstro(type);
	monstro->setTag(tag);
	monstro->setPosition(40 * x - 20, 860 - 40 * y);
	addChild(monstro);
}
void MapItem::addSK3Img(float x, float y)
{
	CCLOG("SK3 create at %f %f", x, y);
	auto* sk3Item = Sprite::create("skill3_map.png");
	sk3Item->setTag(200);
	sk3Item->setPosition(40 * x - 20, 860 - 40 * y);
	addChild(sk3Item);
}