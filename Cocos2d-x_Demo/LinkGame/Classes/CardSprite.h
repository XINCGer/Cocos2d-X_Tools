#ifndef __CARDSPRITE_H__
#define __CARDSPRITE_H__
#include "cocos2d.h"
USING_NS_CC;
class CardSprite : public cocos2d::Layer
{
public:
	int type;
	Sprite* card;
	void cardDelete();
	static CardSprite* createCardSprite(int type, float x, float y);
	void cardInit(int type, float x, float y);
	virtual bool init();
	CREATE_FUNC(CardSprite);
};
#endif