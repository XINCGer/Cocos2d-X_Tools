#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
USING_NS_CC;

class Hero :public Layer
{
public:
	Sprite* hero;
	SpriteFrameCache* hero_frame;
	void heroInit();
	static Hero* createHero();
	virtual bool init();
	void moveTo(int dirc);
	Animate* moveAct(int dirc);
	void faceTo(int dirc);
	void disappear();
	CREATE_FUNC(Hero);
};

#endif