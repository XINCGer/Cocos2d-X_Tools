#include "HelloWorldScene.h"
USING_NS_CC;
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto* background = Sprite::create("background.png");
	background->setPosition(320,180);
	addChild(background);

	HRocker* rocker = HRocker::createHRocker("rocker.png", "rockerBG.png", ccp(100, 100));
	addChild(rocker);
	rocker->startRocker(true);

    return true;
}
