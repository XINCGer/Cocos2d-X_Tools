#ifndef __HERO_SCENE_H__
#define __HERO_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
class Hero : public Layer
{
public:
	bool isRun;
	int direction;
	Point position;
	Sprite* sprite;
	static Hero* createHeroSprite(Point position, int direction, const char* name);
	void heroInit(Point position, int direction, const char* name);
	virtual bool init();
	Animate* createAnimate(int direction, const char *action, int num);
	void setAction(int direction, const char *action, int num);
	void moveTo(float x,float y);
	CREATE_FUNC(Hero);
};
#endif