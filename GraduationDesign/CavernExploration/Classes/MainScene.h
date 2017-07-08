#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "cocos2d.h"
#include "StartGameScene.h"
#include "ShopScene.h"
#include "InstructScene.h"
#include "GameScene.h"
USING_NS_CC;

class MainScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(MainScene);
};

#endif // __MAINSCENE_H__
