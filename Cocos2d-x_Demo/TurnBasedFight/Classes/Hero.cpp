#include "Hero.h"
USING_NS_CC;
Hero* Hero::createHeroSprite(Point position, int direction, const char* action)
{
	Hero* hero = new Hero();
	if (hero && hero->init())
	{
		hero->autorelease();
		hero->heroInit(position, direction, action);
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
void Hero::heroInit(Point position, int direction, const char* action)
{
	this->position = position;
	this->direction = direction;
	auto* m_frameCache = SpriteFrameCache::getInstance();
	m_frameCache->addSpriteFramesWithFile("hero.plist", "hero.png");
	sprite = Sprite::createWithSpriteFrameName(String::createWithFormat("%s%d1.png",action,direction)->getCString());
	sprite->setPosition(position);
	addChild(sprite);
	auto* animate = createAnimate(direction, action, 8,-1);
	sprite->runAction(animate);
}
Animate* Hero::createAnimate(int direction, const char *action, int num,int time)
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
	animation->setLoops(time);//表示无限循环播放
	animation->setDelayPerUnit(0.1f);//每两张图片的时间隔，图片数目越少，间隔最小就越小
	//将动画包装成一个动作
	return Animate::create(animation);
}
void Hero::runAttack(Hero* enemy)
{
	sprite->stopAllActions();
	Point target;
	if (enemy->direction == 1)
	{
		target = Vec2(enemy->position.x - 20, enemy->position.y + 30);
	}
	else
	{
		target = Vec2(enemy->position.x + 20, enemy->position.y+10);
	}
	auto* moveto = MoveTo::create(0.5f, target);
	auto* run = createAnimate(direction, "run", 5,1);
	auto* spawn = Spawn::create(moveto, run, NULL);
	auto* callFunc = CallFunc::create(CC_CALLBACK_0(Hero::doAttack, this));
	auto* sequence = Sequence::create(spawn, callFunc, NULL);
	sprite->runAction(sequence);
}
void Hero::doAttack()
{
	auto* animate = createAnimate(direction, "attack", 14, 1);
	auto* callFunc = CallFunc::create(CC_CALLBACK_0(Hero::runBack, this));
	auto* sequence = Sequence::create(animate, callFunc, NULL);
	sprite->runAction(sequence);
}
void Hero::runBack()
{
	sprite->stopAllActions();
	auto* back = createAnimate(direction, "back", 5, 1);
	auto* moveto = MoveTo::create(0.5f, position);
	auto* spawn = Spawn::create(back, moveto, NULL);
	auto* callFunc = CallFunc::create(CC_CALLBACK_0(Hero::doStand, this));
	auto* sequence = Sequence::create(spawn, callFunc, NULL);
	sprite->runAction(sequence);
}
void Hero::doStand()
{
	sprite->stopAllActions();
	auto* animate = createAnimate(direction, "stand", 8, -1);
	sprite->runAction(animate);
}
void Hero::waitingAttack()
{
	scheduleOnce(schedule_selector(Hero::beAttacked), 1.1f);
}
void Hero::beAttacked(float dt)
{
	sprite->stopAllActions();
	auto* animate = createAnimate(direction, "underatt", 2, 1);
	auto* callFunc = CallFunc::create(CC_CALLBACK_0(Hero::waiting, this));
	auto* sequence = Sequence::create(animate, callFunc, NULL);
	sprite->runAction(sequence);
}
void Hero::waiting()
{
	scheduleOnce(schedule_selector(Hero::waitingUpdate), 0.5f);
}
void Hero::waitingUpdate(float dt)
{
	doStand();
}