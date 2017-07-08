#include "Hero.h"

Hero* Hero::createHero()
{
	Hero* hero = new Hero();
	if (hero && hero->init())
	{
		hero->autorelease();
		hero->heroInit();
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
void Hero::heroInit()
{
	hero = Sprite::create("hero_start.png");
	hero->setPosition(20, 780);  //起点
	//hero->setPosition(780, 60);  //终点左面位置
	this->addChild(hero);

	hero_frame = SpriteFrameCache::getInstance();
	hero_frame->addSpriteFramesWithFile("heroMove/HeroMovePlist.plist", "heroMove/HeroMovePlist.png");
}
void Hero::moveTo(int dirc)
{
	int x = hero->getPositionX();
	int y = hero->getPositionY();

	CCLOG("Hero is %d %d", x, y);

	if (dirc == 0)
		y -= 40;
	if (dirc == 1)
		x -= 40;
	if (dirc == 2)
		y += 40;
	if (dirc == 3)
		x += 40;

	CCLOG("And hero will be %d %d", x, y);

	auto* moveAct = MoveTo::create(0.8, Vec2(x, y));
	
	auto* action = Spawn::create(moveAct, Hero::moveAct(dirc), NULL);

	this->hero->runAction(action);
}
void Hero::faceTo(int dirc)
{
	if (dirc == 0)
		hero->initWithSpriteFrameName("heroMove/move0.png");
	if (dirc == 1)
		hero->initWithSpriteFrameName("heroMove/move4.png");
	if (dirc == 2)
		hero->initWithSpriteFrameName("heroMove/move8.png");
	if (dirc == 3)
		hero->initWithSpriteFrameName("heroMove/move12.png");
}
void Hero::disappear()
{
	Vector<SpriteFrame*> frameArray;
	for (int i = 12; i < 16; i++)
	{
		auto* frame = hero_frame->getSpriteFrameByName(String::createWithFormat("heroMove/move%d.png", i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* anim = Animation::createWithSpriteFrames(frameArray);
	anim->setDelayPerUnit(0.2f);
	auto* animAct = Animate::create(anim);

	auto* fadeAct = FadeOut::create(0.8f);

	auto* action = Sequence::create(animAct, fadeAct, NULL);

	this->hero->runAction(action);
}
Animate* Hero::moveAct(int dirc)
{
	Vector<SpriteFrame*> frameArray;
	for (int i = dirc * 4; i < (dirc * 4 + 4); i++)
	{
		auto* frame = hero_frame->getSpriteFrameByName(String::createWithFormat("heroMove/move%d.png", i)->getCString());
		frameArray.pushBack(frame);
	}
	auto* frame = hero_frame->getSpriteFrameByName(String::createWithFormat("heroMove/move%d.png", dirc * 4)->getCString());
	frameArray.pushBack(frame);

	Animation* anim = Animation::createWithSpriteFrames(frameArray);
	anim->setDelayPerUnit(0.2f);
	return Animate::create(anim);
}