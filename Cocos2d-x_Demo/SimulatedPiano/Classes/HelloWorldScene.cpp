#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
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
	for (int i = 1; i <= 7; i++)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(String::createWithFormat("%d.mp3",i)->getCString());
	}
	auto* pButton1 = MenuItemImage::create("button1.png",
		"button2.png",
		this,
		menu_selector(HelloWorld::note1));
	auto* button1 = Menu::create(pButton1, NULL);
	button1->setPosition(50, 180);
	addChild(button1);

	auto* pButton2 = MenuItemImage::create("button1.png",
		"button2.png",
		this,
		menu_selector(HelloWorld::note2));
	auto* button2 = Menu::create(pButton2, NULL);
	button2->setPosition(50+90*1, 180);
	addChild(button2);

	auto* pButton3 = MenuItemImage::create("button1.png",
		"button2.png",
		this,
		menu_selector(HelloWorld::note3));
	auto* button3 = Menu::create(pButton3, NULL);
	button3->setPosition(50 + 90 * 2, 180);
	addChild(button3);

	auto* pButton4 = MenuItemImage::create("button1.png",
		"button2.png",
		this,
		menu_selector(HelloWorld::note4));
	auto* button4 = Menu::create(pButton4, NULL);
	button4->setPosition(50 + 90 * 3, 180);
	addChild(button4);

	auto* pButton5 = MenuItemImage::create("button1.png",
		"button2.png",
		this,
		menu_selector(HelloWorld::note5));
	auto* button5 = Menu::create(pButton5, NULL);
	button5->setPosition(50 + 90 * 4, 180);
	addChild(button5);

	auto* pButton6 = MenuItemImage::create("button1.png",
		"button2.png",
		this,
		menu_selector(HelloWorld::note6));
	auto* button6 = Menu::create(pButton6, NULL);
	button6->setPosition(50 + 90 * 5, 180);
	addChild(button6);

	auto* pButton7 = MenuItemImage::create("button1.png",
		"button2.png",
		this,
		menu_selector(HelloWorld::note7));
	auto* button7 = Menu::create(pButton7, NULL);
	button7->setPosition(50 + 90 * 6, 180);
	addChild(button7);
    return true;
}
void HelloWorld::note1(cocos2d::Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("1.mp3");
}
void HelloWorld::note2(cocos2d::Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("2.mp3");
}
void HelloWorld::note3(cocos2d::Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("3.mp3");
}
void HelloWorld::note4(cocos2d::Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("4.mp3");
}
void HelloWorld::note5(cocos2d::Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("5.mp3");
}
void HelloWorld::note6(cocos2d::Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("6.mp3");
}
void HelloWorld::note7(cocos2d::Object* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("7.mp3");
}
