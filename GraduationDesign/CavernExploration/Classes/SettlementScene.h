#ifndef __SETTLEMENTSCENE_H__
#define __SETTLEMENTSCENE_H__

#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;

class SettlementScene : public cocos2d::Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SettlementScene);
};

#endif // __SETTLEMENTSCENE_H__
