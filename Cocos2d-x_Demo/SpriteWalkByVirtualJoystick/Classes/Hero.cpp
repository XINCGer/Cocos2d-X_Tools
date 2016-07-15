#include "Hero.h"
USING_NS_CC;
Hero* Hero::createHeroSprite(Point position, int direction, const char* name)
{
	Hero* hero = new Hero();
	if (hero && hero->init())
	{
		hero->autorelease();
		hero->heroInit(position, direction, name);
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return NULL;
}
bool Hero::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
void Hero::heroInit(Point position, int direction, const char* name)
{
	this->isRun = false;
	this->position = position;
	sprite = Sprite::create(String::createWithFormat("%s11.png",name)->getCString());
	sprite->setPosition(position);
	addChild(sprite);
	auto* action = createAnimate(1, "stand", 7);
	action->setTag(100);
	sprite->runAction(action);
}
Animate* Hero::createAnimate(int direction, const char *action, int num)
{
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("hero.plist", "hero.png");
	Vector<SpriteFrame*> frameArray;
	for (int i = 1; i <= num; i++)
	{
		auto* frame = m_frameCache->getSpriteFrameByName(String::createWithFormat("%s%d%d.png", action, direction, i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(-1);//表示无限循环播放
	animation->setDelayPerUnit(0.1f);//每两张图片的时间隔，图片数目越少，间隔最小就越小

	//将动画包装成一个动作
	return Animate::create(animation);
}
void Hero::setAction(int direction, const char *action, int num)
{
	sprite->stopActionByTag(100);
	auto* animate = createAnimate(direction, action, num);
	animate->setTag(100);
	sprite->runAction(animate);
}
void Hero::moveTo(float x, float y)
{
	float r = sqrt(x*x + y*y);
	position.x += x / r;
	position.y += y / r;
	sprite->setPosition(position);
}