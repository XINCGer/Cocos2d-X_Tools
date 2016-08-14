#ifndef __COUNTDOWNBAR_SCENE_H__
#define __COUNTDOWNBAR_SCENE_H__

#include "cocos2d.h"

class CountDownBar : public cocos2d::Layer
{
public:
	cocos2d::Sprite* barBG;
	cocos2d::Sprite* countDownBar;
	void barUpdate(int timeNow,int timeFull);
	static CountDownBar* createCountDownBar(cocos2d::Point position, int size);
	void countDownBarInit(cocos2d::Point position, int size);
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(CountDownBar);
};

#endif // __COUNTDOWNBAR_SCENE_H__