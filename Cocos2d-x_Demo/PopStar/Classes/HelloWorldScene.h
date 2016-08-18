/*
ProjectName: PopStar
Author: ÂíÈýÐ¡»ï¶ù
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/16
*/
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "StarSprite.h"
USING_NS_CC;
#define HEIGHT 16
#define WIDTH 9
class HelloWorld : public cocos2d::Layer
{
public:
	int starX;
	int starY;
	StarSprite* star[WIDTH][HEIGHT];
	int holder[WIDTH*HEIGHT];
	void addStar();
	void UDLRDelete(int x, int y);
	void addToHolder(int x, int y);
	void popStar();
	void starDrop();
	void starTranslation();
	void starMove(float dt);
	void cleanHolder();
	bool isOver();
	EventListenerTouchOneByOne* listener;
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void update(float dt);
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
