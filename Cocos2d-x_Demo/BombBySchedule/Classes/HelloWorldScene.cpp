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
    if ( !Layer::init() )
    {
        return false;
    }
	auto* background = LayerColor::create(ccc4(255, 255, 255, 255));
	addChild(background);
	bomb = Sprite::create("bomb.png");
	bomb->setPosition(320, 180);
	addChild(bomb);
	scheduleOnce(schedule_selector(HelloWorld::bang),5.0f);
    return true;
}
void HelloWorld::bang(float dt)
{
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("bang.plist", "bang.png");
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i < 11; i++)
	{	
		auto* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("bang%d.png", i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(1);//表示无限循环播放
	animation->setDelayPerUnit(0.1f);//每两张图片的时间隔，图片数目越少，间隔最小就越小

	//将动画包装成一个动作
	auto* action = Animate::create(animation);
	bomb->runAction(action);
}
