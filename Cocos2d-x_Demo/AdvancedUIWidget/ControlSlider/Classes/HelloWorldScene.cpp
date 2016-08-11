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
	auto* slider = ControlSlider::create("background.png", "progress.png", "bar.png");
	slider->setPosition(320, 180);
	addChild(slider);
	slider->setMaximumValue(100);
	slider->setMinimumValue(0);
	slider->setValue(30);
    return true;
}
