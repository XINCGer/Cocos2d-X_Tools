#include "HelloWorldScene.h"
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
	auto* background = LayerColor::create(Color4B(255, 255, 255, 255));
	addChild(background);
	auto* bar1 = SlideBar::createBar(580, Vec2(40, 110), 200);
	addChild(bar1);
	auto* bar2 = SlideBar::createBar(200, Vec2(80, 270), 200);
	addChild(bar2);
    return true;
}
