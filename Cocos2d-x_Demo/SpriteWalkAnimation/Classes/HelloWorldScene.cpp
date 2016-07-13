#include "HelloWorldScene.h"

USING_NS_CC;

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
    if ( !Layer::init() )
    {
        return false;
    }
	auto* background = LayerColor::create(ccc4(255, 255, 255, 255));
	addChild(background);
	hero = new Hero();
	hero->initHeroSprite(1, Vec2(320, 180));
	addChild(hero);

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}
bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	hero->getDirection(hero->position,touch->getLocation());
	hero->heroMoveTo(touch->getLocation());
	return false;
}
