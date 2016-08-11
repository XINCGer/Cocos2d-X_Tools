#include "HelloWorldScene.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
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
	auto* background = LayerColor::create(Color4B(255, 255, 255, 255));
	addChild(background);
	auto* controler = ControlPotentiometer::create("background.png", "progress.png", "button.png");
	controler->setPosition(290, 130);
	addChild(controler);
	controler->setMinimumValue(0);
	controler->setMaximumValue(100);
	controler->setScale(0.7f);
	controler->setValue(30);
	controler->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::change), Control::EventType::VALUE_CHANGED);
	return true;
}
void HelloWorld::change(CCObject * pSender, Control::EventType event)
{
	auto* controler = (ControlPotentiometer*)pSender;
	float num = controler->getValue();
	CCLOG("the value of controler is:%f", num);
}
