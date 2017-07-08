#ifndef __MONSTRO_H__
#define __MONSTRO_H__

#include "cocos2d.h"
USING_NS_CC;

class Monstro :public Layer
{
public:
	Sprite* monstro;
	SpriteFrameCache* monstro_frame;
	int type;
	void monstroInit(int type);
	static Monstro* createMonstro(int type);
	virtual bool init();
	void faceTo(int dirc);
	void disappear();
	CREATE_FUNC(Monstro);
};

#endif __MONSTRO_H__