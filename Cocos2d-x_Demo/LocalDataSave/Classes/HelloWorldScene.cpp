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
	auto* background = LayerColor::create(Color4B(255, 255, 255, 255));
	addChild(background);
	auto* readLabel = Label::create("read", "Arial", 56);
	readLabel->setColor(Color3B(0, 0, 0));
	auto* pReadLabel = MenuItemLabel::create(readLabel, this, menu_selector(HelloWorld::readCallback));
	auto* buttonReadLabel = Menu::create(pReadLabel, NULL);
	buttonReadLabel->setPosition(320, 260);
	addChild(buttonReadLabel);
	auto* saveLabel = Label::create("save", "Arial", 56);
	saveLabel->setColor(Color3B(0, 0, 0));
	auto* pSaveLabel = MenuItemLabel::create(saveLabel, this, menu_selector(HelloWorld::saveCallback));
	auto* buttonSaveLabel = Menu::create(pSaveLabel, NULL);
	buttonSaveLabel->setPosition(320, 100);
	addChild(buttonSaveLabel);
	UserDefault::sharedUserDefault()->setBoolForKey("isExisted",false);
    return true;
}
void HelloWorld::readCallback(Ref* pSender)
{
	CCLOG("============================================================");
	CCLOG("reading begin!");
	if (UserDefault::sharedUserDefault()->getBoolForKey("isExisted"))
	{
		int intVar = UserDefault::sharedUserDefault()->getIntegerForKey("int");
		CCLOG("the int is:%d", intVar);
		float floatVar = UserDefault::sharedUserDefault()->getFloatForKey("float");
		CCLOG("the float is:%f", floatVar);
		std::string str = UserDefault::sharedUserDefault()->getStringForKey("string");
		CCLOG("the string is:%s", str);
	}
	else
	{
		CCLOG("not exist!");
	}
	CCLOG("============================================================");
}
void HelloWorld::saveCallback(Ref* pSender)
{
	CCLOG("============================================================");
	CCLOG("save begin!");
	UserDefault::sharedUserDefault()->setIntegerForKey("int", 999);
	UserDefault::sharedUserDefault()->setFloatForKey("float", 3.1415926);
	UserDefault::sharedUserDefault()->setStringForKey("string", "this is a string!");
	UserDefault::sharedUserDefault()->setBoolForKey("isExisted", true);
	CCLOG("saved file path is %s", UserDefault::sharedUserDefault()->getXMLFilePath());
	CCLOG("============================================================");
}
