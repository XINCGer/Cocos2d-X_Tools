#ifndef _POCKER_SCENE_H_
#define _POCKER_SCENE_H_
#include "cocos2d.h"
#define CARDX 20
#define CARDY 30
USING_NS_CC;
class Pocker : public Layer
{
public:
	int number;
	Sprite* card;
	Sprite* back;
	bool isSelected;
	bool isActive;
	EventListenerTouchOneByOne* listener;
	static Pocker* createPocker(int number, Point position, bool isFont);
	void initPocker(int number, Point position, bool isFont);
	void showFont();
	void showLast();
	void moveTo(Point des, float time);
	void setTouchPriority(int num);
	virtual bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	CREATE_FUNC(Pocker);
};
#endif
