#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "HRocker.h"
class HelloWorld : public cocos2d::Layer
{
public:
	HRocker* rocker;
	Hero* hero;
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void update(float dt);
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
