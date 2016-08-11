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
	auto* switchBG = Sprite::create("background.png");
	auto* switchOn = Sprite::create("on.png");
	auto* switchOff = Sprite::create("off.png");
	auto* switchBar = Sprite::create("button.png");
	auto* on = Label::create("on", "Arial", 36);
	auto* off = Label::create("off", "Arial", 36);
	auto* controlSwitch = ControlSwitch::create(switchBG, switchOn, switchOff, switchBar, on, off);
	controlSwitch->setPosition(320, 180);
	addChild(controlSwitch);
	controlSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::change), Control::EventType::VALUE_CHANGED);
    return true;
}
void HelloWorld::change(Object * pSender, Control::EventType event)
{
	if (event == Control::EventType::VALUE_CHANGED)
	{
		auto* s = (ControlSwitch*)pSender;
		if (s->isOn())
		{
			CCLOG("the switch is on!");
		}
		else
		{
			CCLOG("the switch is off!");
		}
	}
}
