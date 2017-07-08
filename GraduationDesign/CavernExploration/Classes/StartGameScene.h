#ifndef __STARTGAMESCENE_H__
#define __STARTGAMESCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "MainScene.h"
#include "SettlementScene.h"

USING_NS_CC;

class StartGameScene : public cocos2d::Scene
{
public:
	SpriteFrameCache* image_frame;
	static cocos2d::Scene* createScene();
	virtual bool init();
	static void showPanelGet();
	static void chgSkillNum(int type);
	static void chgMoney();
	static void chgHPBar(int hint);
	void to_menu(cocos2d::Object* pSender);
	CREATE_FUNC(StartGameScene);
};

#endif // __STARTGAMESCENE_H__
