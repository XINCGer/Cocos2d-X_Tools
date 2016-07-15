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
	auto* background = LayerColor::create(Color4B(165, 210, 210, 255));
	addChild(background);
	//auto* background = Sprite::create("background.png");
	//background->setPosition(320, 180);
	//addChild(background);

	hero = Hero::createHeroSprite(Vec2(320, 180), 1, "stand");
	addChild(hero);

	rocker = HRocker::createHRocker("rocker.png", "rockerBG.png", ccp(100, 100));
	addChild(rocker);
	rocker->startRocker(true);

	scheduleUpdate();
    return true;
}
void HelloWorld::update(float dt)
{
	if (rocker->isCanMove == true)
	{
		if (hero->isRun == false)
		{
			hero->isRun = true;
			hero->direction = rocker->direction;
			hero->setAction(hero->direction, "run", 8);
		}
		else if (hero->isRun == true)
		{
			if (hero->direction != rocker->direction)
			{
				hero->direction = rocker->direction;
				hero->setAction(hero->direction, "run", 8);
			}
		}
		hero->moveTo(rocker->dx, rocker->dy);
	}
	else if (hero->isRun==true&&rocker->isCanMove==false)
	{
		hero->isRun = false;
		hero->setAction(hero->direction, "stand", 7);
	}
}
