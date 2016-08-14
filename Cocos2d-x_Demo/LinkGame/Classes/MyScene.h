#ifndef __MYWORLD_SCENE_H__
#define __MYWORLD_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
class MyWorld :public cocos2d::Layer
{
public:
	int iniX;
	int id;
	static cocos2d::Scene* createScene();	// 静态函数，用户获取场景对象
	virtual bool init();					// 初始化场景
	void menu(cocos2d::Ref* pSender);
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);
	CREATE_FUNC(MyWorld);					// 这里使用了一个宏
};
#endif

