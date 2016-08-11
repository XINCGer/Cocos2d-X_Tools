#include "SlideBar.h"
USING_NS_CC;
SlideBar* SlideBar::createBar(int size, Point position, int number)
{
	SlideBar* layer = SlideBar::create();
	if (layer)
	{
		layer->barInit(size, position, number);
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
void SlideBar::barInit(int size, Point position, int number)
{
	this->size = size;
	isTouched = false;
	auto* bg = LayerColor::create(Color4B(0, 0, 0, 255), size, 20);
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(position);
	addChild(bg);
	auto* numBar = LayerColor::create(Color4B(233, 0, 1, 255), number, 20);
	numBar->setAnchorPoint(Vec2(0, 0));
	numBar->setPosition(position);
	numBar->setTag(1);
	addChild(numBar);
	auto* bar = Sprite::create("bar.png");
	bar->setPosition(position.x + number, position.y + 10);
	bar->setTag(2);
	addChild(bar);

	auto* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SlideBar::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SlideBar::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SlideBar::onTouchEnded, this);
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
bool SlideBar::onTouchBegan(Touch* touch, Event* event)
{
	Sprite* bar = (Sprite*)getChildByTag(2);
	Point point = touch->getLocation();
	if (bar->boundingBox().containsPoint(point))
	{
		isTouched = true;
		return true;
	}
	return false;
}
void SlideBar::onTouchMoved(Touch* touch, Event* event)
{
	if (!isTouched)
	{
		return;
	}
	auto* numBar = (Sprite*)getChildByTag(1);
	auto* bar = (Sprite*)getChildByTag(2);
	auto point = touch->getLocation();
	if (point.x > numBar->getPositionX() && point.x < numBar->getPositionX() + size)
	{
		bar->setPositionX(point.x);
		numBar->setContentSize(Size(point.x - numBar->getPositionX(), numBar->getContentSize().height));
	}
}
void SlideBar::onTouchEnded(Touch* touch, Event* event)
{
	isTouched = false;
}