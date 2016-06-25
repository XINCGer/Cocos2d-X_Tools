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
	// 加入背景
	auto* background = Sprite::create("background.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background);
	// 加入卡牌精灵
	for (int i = 0; i < 5; i++)
	{
		char imageName[15] = { 0 };
		sprintf(imageName, "mycard0%d.png", i);
		myCard[i] = Sprite::create(imageName);
		myCard[i]->setScale(0.26f);
		myCard[i]->setPosition(visibleSize.width*(i+1)/6, visibleSize.height/2);
		this->addChild(myCard[i]);
	}
    // 建立事件监听器
	auto myListener = EventListenerTouchOneByOne::create();
	myListener->setSwallowTouches(true);
	myListener->onTouchBegan = [](Touch* touch, Event* event)
	{
		// 获取事件所绑定的 target
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		// 获取当前点击点所在相对按钮的位置坐标
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		// 点击范围判断检测
		if (rect.containsPoint(locationInNode))
		{
			// 显示当前卡牌精灵的坐标位置
			log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			target->setOpacity(180);
			return true;
		}
		return false;
	};
	myListener->onTouchMoved = [](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		// 显示当前卡牌精灵的坐标位置
		log("sprite move... x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
		// 移动当前卡牌精灵的坐标位置
		target->setPosition(target->getPosition() + touch->getDelta());
	};
	myListener->onTouchEnded = [](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setOpacity(255);
	};
	// 为事件监听器绑定事件
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener, myCard[0]);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener->clone(), myCard[1]);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener->clone(), myCard[2]);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener->clone(), myCard[3]);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener->clone(), myCard[4]);

    return true;
}
