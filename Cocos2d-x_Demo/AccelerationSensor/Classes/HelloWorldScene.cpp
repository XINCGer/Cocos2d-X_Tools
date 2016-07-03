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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	screenWidth = visibleSize.width;
	screenHeight = visibleSize.height;
	scale = 1.0f;
	sprite = Sprite::create("sprite.png");
	sprite->setScale(0.3f);
	sprite->setPosition(screenWidth / 2, screenHeight / 2);
	this->addChild(sprite);
	Device::setAccelerometerEnabled(true);
	auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}
void HelloWorld::onAcceleration(Acceleration* acc, Event* event)
{
	auto point = this->sprite->getPosition();
	if (acc->x < 0 && point.x>0)
	{
		point.x--;
	}
	else if (acc->x > 0 && point.x<this->screenWidth)
	{
		point.x++;
	}

	if (acc->y < 0 && point.x>0)
	{
		point.y--;
	}
	else if (acc->y > 0 && point.y<this->screenHeight)
	{
		point.y++;
	}

	if (acc->z<0 && this->scale>0.1)
	{
		this->scale = this->scale*0.9;
	}
	else if (acc->z>0 && this->scale < 10)
	{
		this->scale = this->scale*1.1;
	}
	this->sprite->setPosition(point);
	this->sprite->setScale(0.3*this->scale);
}