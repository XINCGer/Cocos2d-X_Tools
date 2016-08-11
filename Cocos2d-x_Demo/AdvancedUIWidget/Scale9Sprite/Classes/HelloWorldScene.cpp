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
	Scale9Sprite* bar = Scale9Sprite::create("patch.png",Rect(0,0,200,200),Rect(50,50,100,100));
	bar->setPreferredSize(Size(500, 300));
	bar->setPosition(320, 180);
	addChild(bar);
    return true;
}
