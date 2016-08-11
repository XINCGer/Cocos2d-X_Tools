#include "HelloWorldScene.h"
#include "extensions\cocos-ext.h"
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

	Scale9Sprite* btnNormal = Scale9Sprite::create("button0.png", Rect(0, 0, 200, 200), Rect(50, 50, 100, 100));
	btnNormal->setPreferredSize(Size(500, 300));
	Scale9Sprite* btnPressed = Scale9Sprite::create("button1.png", Rect(0, 0, 200, 200), Rect(50, 50, 100, 100));
	btnPressed->setPreferredSize(Size(500, 300));
	auto* label = Label::create("button", "", 40);
	auto* button = ControlButton::create(label, btnNormal);
	button->setBackgroundSpriteForState(btnNormal, Control::State::NORMAL);
	button->setBackgroundSpriteForState(btnPressed, Control::State::SELECTED);
	button->setPosition(320, 180);
	addChild(button);
	return true;
}
