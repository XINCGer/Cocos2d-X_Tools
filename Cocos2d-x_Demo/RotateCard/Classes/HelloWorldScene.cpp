#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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
	auto* background = LayerColor::create(ccc4(255, 255, 255, 255));
	addChild(background);
	myCard1 = Sprite::create("mycard01.png");
	myCard2 = Sprite::create("mycard02.png");
	myCard1->setPosition(360, 180);
	myCard1->setScale(0.5f);
	myCard1->setAnchorPoint(Vec2(0.5f, 0.5f));
	addChild(myCard1);
	myCard2->setPosition(360, 180);
	myCard2->setScale(0.5f);
	myCard2->setAnchorPoint(Vec2(0.5f, 0.5f));
	myCard2->setRotation3D(Vec3(0, 82.5f, 0));
	addChild(myCard2);
	auto* rotateby = RotateBy::create(1.5f, Vec3(0, 82.5f, 0));
	auto* callFunc = CallFunc::create(CC_CALLBACK_0(HelloWorld::rotateCard, this));
	auto* sequence = Sequence::create(rotateby, callFunc,NULL);
	myCard1->runAction(sequence);
    return true;
}
void HelloWorld::rotateCard()
{
	auto* rotateby = RotateBy::create(1.5f, Vec3(0, 97.5f, 0));
	myCard2->runAction(rotateby);
}
