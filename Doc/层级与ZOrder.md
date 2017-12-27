## 层级与ZOrder  

addChild()的顺序会影响层级，使用setLocalZOrder可以动态调整层级。  
先加入Child的 层级较低 会被后加入的覆盖  
层级越低，node节点越在下面，就会被层级更高的node覆盖。
具体可以看下面的代码:  

```C++
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

	auto sprite = Sprite::create("stand11.png");
	auto bg = Sprite::create("bg.jpg");
	auto headBg = Sprite::create("head_bg.png");
	auto head = Sprite::create("head.png");

	//先加入Child的 层级较低 会被后加入的覆盖
	layer->addChild(head);
	layer->addChild(sprite);
	layer->addChild(headBg);
	layer->addChild(bg);

	auto size = Director::getInstance()->getVisibleSize();
	int x = size.width;
	int y = size.height;
	bg->setPosition(x / 2, y / 2);
	headBg->setPosition(x / 2, y / 2);
	head->setPosition(x / 2, y / 2);
	sprite->setPosition(x / 2, y / 2);

	//调整zOrder
	bg->setLocalZOrder(1);
	headBg->setLocalZOrder(2);
	head->setLocalZOrder(3);
	sprite->setLocalZOrder(3);
	
	sprite->runAction(createAnimate("run", "hero.plist", "hero.png", -1, 0.1f, 11, 15));
	 //add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

```
