#ifndef __SHOPSCENE_H__
#define __SHOPSCENE_H__

#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;

class ShopScene : public cocos2d::Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	static void reGetUI();
	static void refreshMoney(int cost);
	static void refreshUI(int page, int type, bool isCreate);
	CREATE_FUNC(ShopScene);
};

#endif // __SHOPSCENE_H__
