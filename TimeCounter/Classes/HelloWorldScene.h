#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "TimeCounter.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(HelloWorld);

    void logic(float dt);
    void doSomething(float dt);

private:
    TimeCounter* m_timeCounter;
};

#endif // __HELLOWORLD_SCENE_H__
