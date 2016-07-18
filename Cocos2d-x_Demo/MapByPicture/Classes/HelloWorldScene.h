#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "HRocker.h"
#include "Hero.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
	Image* image;
	Sprite* background[2];
	HRocker* rocker;
	Hero* hero;
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void update(float dt);
	cocos2d::Color4B getColor(int x,int y);
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
