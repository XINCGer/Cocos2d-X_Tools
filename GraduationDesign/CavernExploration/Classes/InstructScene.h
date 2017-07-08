#ifndef __INSTRUCTSCENE_H__
#define __INSTRUCTSCENE_H__

#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;

class InstructScene : public cocos2d::Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(InstructScene);
};

#endif // __INSTRUCTSCENE_H__
