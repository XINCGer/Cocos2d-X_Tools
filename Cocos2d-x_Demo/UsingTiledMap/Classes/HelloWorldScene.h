#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	cocos2d::Size size;
	cocos2d::Sprite* sprite;
	cocos2d::TMXTiledMap* map;
	cocos2d::TMXLayer* meta;
    static cocos2d::Scene* createScene();
    virtual bool init();
	void up(cocos2d::Object* pSender);
	void right(cocos2d::Object* pSender);
	void left(cocos2d::Object* pSender);
	void down(cocos2d::Object* pSender);
	bool isCanReach(float x, float y);
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
