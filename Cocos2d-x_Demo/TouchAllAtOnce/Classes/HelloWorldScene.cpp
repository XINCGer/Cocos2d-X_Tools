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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto myListener = EventListenerTouchAllAtOnce::create();
	myListener->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event *unused_event)
	{
		for (auto &item : touches)
		{
			auto* sprite = Sprite::create("sprite.png");
			sprite->setPosition(item->getLocation());
			sprite->setOpacity(120);
			sprite->setScale(0.2f);
			this->addChild(sprite);
		}
	};
	myListener->onTouchesMoved = [=](const std::vector<Touch*>& touches, Event *unused_event)
	{
		for (auto &item : touches)
		{
			int id = item->getID();
			auto array = this->getChildren();
			auto sprite = array.at(id);
			auto point = item->getLocation();
			sprite->setPosition(point);
			CCLOG("id=%d\tx=%f\ty=%f",id,point.x,point.y);
		}
	};
	myListener->onTouchesEnded = [=](const std::vector<Touch*>& touches, Event *unused_event)
	{
		for (auto &item : touches)
		{
			int id = item->getID();
			auto array = this->getChildren();
			auto sprite = array.at(id);
			sprite->setOpacity(255);
			auto point = item->getLocation();
			sprite->setPosition(point);
			CCLOG("id=%d\tx=%f\ty=%f", id, point.x, point.y);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener, this);
    return true;
}
