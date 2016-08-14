#include "MyScene.h"
USING_NS_CC;
Scene* MyWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = MyWorld::create();
	scene->addChild(layer);
	return scene;
}
bool MyWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setAnchorPoint(Vec2(0.5f, 0.5f));
	id = 0;
	auto* bg0 = Sprite::create("bg0.png");
	bg0->setTag(0);
	bg0->setPosition(320, 180);
	addChild(bg0);
	auto* pButton0 = MenuItemImage::create("select1.png",
		"select2.png",
		this,
		menu_selector(MyWorld::menu));
	auto* button0 = Menu::create(pButton0, NULL);
	button0->setPosition(320, 140);
	bg0->addChild(button0);
	auto* bg1 = Sprite::create("bg1.png");
	bg1->setTag(1);
	bg1->setPosition(320+640, 180);
	addChild(bg1);
	auto* pButton1 = MenuItemImage::create("select1.png",
		"select2.png",
		this,
		menu_selector(MyWorld::menu));
	auto* button1 = Menu::create(pButton1, NULL);
	button1->setPosition(320, 140);
	bg1->addChild(button1);
	auto* bg2 = Sprite::create("bg2.png");
	bg2->setTag(2);
	bg2->setPosition(320-640, 180);
	addChild(bg2);
	auto* pButton2 = MenuItemImage::create("select1.png",
		"select2.png",
		this,
		menu_selector(MyWorld::menu));
	auto* button2 = Menu::create(pButton2, NULL);
	button2->setPosition(320, 140);
	bg2->addChild(button2);

	auto* dispatcher = Director::getInstance()->getEventDispatcher();
	auto* listener = EventListenerTouchOneByOne::create();				// 创建监听器
	listener->onTouchBegan = CC_CALLBACK_2(MyWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MyWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MyWorld::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}
void MyWorld::menu(Ref* pSender)
{
	UserDefault::sharedUserDefault()->setIntegerForKey("id", id);
	Director::sharedDirector()->replaceScene(HelloWorld::createScene());
}
bool MyWorld::onTouchBegan(Touch *touch, Event *event)
{
	iniX = (int)touch->getLocation().x;
	// 将三个场景摆正位置
	auto* bg1 = (Sprite*)getChildByTag(id);
	auto* bg2 = (Sprite*)getChildByTag((id + 1) % 3);
	auto* bg0 = (Sprite*)getChildByTag((id + 2) % 3);
	bg1->setPosition(320, 180);
	bg2->setPosition(960, 180);
	bg0->setPosition(-320, 180);
	return true;
}
void MyWorld::onTouchMoved(Touch *touch, Event *event)
{
	int posX = (int)touch->getLocation().x;
	auto* bg1 = (Sprite*)getChildByTag(id);
	auto* bg2 = (Sprite*)getChildByTag((id + 1) % 3);
	auto* bg0 = (Sprite*)getChildByTag((id + 2) % 3);
	int dx = posX - iniX;
	CCLOG("%d-%d=%d", posX, iniX, dx);
	bg0->setPositionX(bg0->getPositionX() + dx);
	bg1->setPositionX(bg1->getPositionX() + dx);
	bg2->setPositionX(bg2->getPositionX() + dx);
}
void MyWorld::onTouchEnded(Touch *touch, Event *event)
{
	int posX = (int)touch->getLocation().x;
	int dx = posX - iniX;
	auto* bg1 = (Sprite*)getChildByTag(id);
	auto* bg2 = (Sprite*)getChildByTag((id + 1) % 3);
	auto* bg0 = (Sprite*)getChildByTag((id + 2) % 3);
	if (dx > 320)
	{
		bg2->setPositionX(bg0->getPositionX() - 640);
		auto* move0 = MoveTo::create(0.1f, Vec2(320, 180));
		auto* move1 = MoveTo::create(0.1f, Vec2(960 , 180));
		auto* move2 = MoveTo::create(0.1f, Vec2(-320 , 180));
		id = (id + 1) % 3;
	}
	else if (dx < -320)
	{
		bg0->setPositionX(bg2->getPositionX() + 640);
		auto* move0 = MoveTo::create(0.1f, Vec2(960, 180));
		auto* move1 = MoveTo::create(0.1f, Vec2(320, 180));
		auto* move2 = MoveTo::create(0.1f, Vec2(-320, 180));
		id = (id + 2) % 3;
	}
	else
	{
		auto* move0 = MoveTo::create(0.1f, Vec2(-320, 180));
		auto* move1 = MoveTo::create(0.1f, Vec2(320, 180));
		auto* move2 = MoveTo::create(0.1f, Vec2(960, 180));
	}
}