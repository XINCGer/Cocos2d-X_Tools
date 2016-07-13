#ifndef __HERO_H__
#define __HERO_H__
#include "cocos2d.h"
USING_NS_CC;
enum hero_direction
{
	RIGHT_DOWN = 1,
	LEFT_DOWN = 2,
	LEFT_UP = 3,
	RIGHT_UP = 4,
	DOWN = 5,
	LEFT = 6,
	UP = 7,
	RIGHT = 8
};
class Hero :public cocos2d::CCNode
{
public:
	int direction;
	cocos2d::Point position;
	cocos2d::Sprite* sprite;
	void initHeroSprite(int direction,cocos2d::Point position);
	void heroMoveTo(cocos2d::Point position);
	void heroResume();
	int getDirection(cocos2d::Point pos1, cocos2d::Point pos2);
	float getDistance(cocos2d::Point pos1, cocos2d::Point pos2);
	cocos2d::Animate* createAnimate(int direction, const char *action, int num);
	CREATE_FUNC(Hero);
};
#endif