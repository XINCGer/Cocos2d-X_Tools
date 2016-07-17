#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	auto* background = LayerColor::create(Color4B(255, 255, 255, 255));
	addChild(background);
	i = 0;
	hero[0] = Hero::createHeroSprite(Vec2(540, 100), 1, "stand");
	addChild(hero[0]);
	hero[1] = Hero::createHeroSprite(Vec2(100, 260), 2, "stand");
	addChild(hero[1]);
	schedule(schedule_selector(HelloWorld::myUpdate), 2.5f);
    return true;
}
void HelloWorld::myUpdate(float dt)
{
	i++;
	if ((i % 2) == 0)
	{
		hero[0]->runAttack(hero[1]);
		hero[1]->waitingAttack();
	}
	else
	{
		hero[1]->runAttack(hero[0]);
		hero[0]->waitingAttack();
	}
}