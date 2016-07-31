#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
	Point prePos;
	b2World *_world;
	b2Body *_body;
	Sprite *ball;
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
