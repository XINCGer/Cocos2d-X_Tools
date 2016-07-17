#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Hero.h"
class HelloWorld : public cocos2d::Layer
{
public:
	int i;
	Hero* hero[2];
    static cocos2d::Scene* createScene();
    virtual bool init();
	void myUpdate(float dt);
	void waiting(float dt);
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
