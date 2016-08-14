#include "CountDownBar.h"
USING_NS_CC;
#define BARBG_WIDTH 80
#define BARBG_HEIGHT 20
CountDownBar* CountDownBar::createCountDownBar(Point position, int size)
{
	CountDownBar* bar = new CountDownBar();
	if (bar && bar->init())
	{
		bar->autorelease();
		bar->countDownBarInit(position, size);
		return bar;
	}
	CC_SAFE_DELETE(bar);
	return NULL;
}
bool CountDownBar::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
void CountDownBar::countDownBarInit(cocos2d::Point position, int size)
{
	barBG = Sprite::create("barBG.png");
	barBG->setAnchorPoint(Vec2(0, 1));
	barBG->setScaleX((float)size / BARBG_WIDTH);
	barBG->setPosition(position);
	addChild(barBG);
	countDownBar = Sprite::create("bar.png");
	countDownBar->setAnchorPoint(Vec2(0, 0));
	countDownBar->setPosition(0, 0);
	barBG->addChild(countDownBar);
}
void CountDownBar::barUpdate(int timeNow, int timeFull)
{
	countDownBar->setScaleX((float)timeNow / timeFull);
}