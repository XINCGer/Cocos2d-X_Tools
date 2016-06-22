#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	void note1(cocos2d::Object* pSender);
	void note2(cocos2d::Object* pSender);
	void note3(cocos2d::Object* pSender);
	void note4(cocos2d::Object* pSender);
	void note5(cocos2d::Object* pSender);
	void note6(cocos2d::Object* pSender);
	void note7(cocos2d::Object* pSender);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
