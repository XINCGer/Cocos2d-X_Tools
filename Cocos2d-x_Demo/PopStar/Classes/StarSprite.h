/*
ProjectName: PopStar
Author: ÂíÈýÐ¡»ï¶ù
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/16
*/
#ifndef __STARSPRITE_H__
#define __STARSPRITE_H__
#include "cocos2d.h"
USING_NS_CC;
class StarSprite : public cocos2d::Layer
{
public:
	int type;
	Sprite* star;
	void starDelete();
	static StarSprite* createStar(int type, float x, float y);
	void starInit(int type, float x, float y);
	void moveTo(float dt, int x, int y);
	virtual bool init();
	CREATE_FUNC(StarSprite);
};
#endif