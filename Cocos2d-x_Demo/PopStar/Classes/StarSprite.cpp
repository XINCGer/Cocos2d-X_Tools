/*
ProjectName: PopStar
Author: 马三小伙儿
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/16
*/
#include "StarSprite.h"
#include "cocos2d.h"
USING_NS_CC;
StarSprite* StarSprite::createStar(int type, float x, float y)
{
	// 该方法为套用模板
	StarSprite* star = new StarSprite();
	if (star && star->init())
	{
		star->autorelease();
		star->starInit(type, x, y);
		return star;
	}
	CC_SAFE_DELETE(star);
	return NULL;
}
bool StarSprite::init()
{	//套用模板
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
void StarSprite::starInit(int type, float x, float y)
{
	this->type = type;
	star = Sprite::create(String::createWithFormat("card%d.png",type)->getCString());
	star->setPosition(20 + 40 * x, 20 + 40 * y);
	addChild(star);
}
void StarSprite::starDelete()
{
	this->type = 0;
	auto texture = Director::getInstance()->getTextureCache()->addImage("card0.png");
	auto frame = SpriteFrame::create("card0.png", Rect(0, 0, 40, 40));
	star->setDisplayFrame(frame);
}
void StarSprite::moveTo(float dt, int x, int y)
{
	this->star->stopAllActions();
	auto* move = MoveTo::create(dt, Vec3(20 + 40 * x, 20 + 40 * y, 0));
	this->star->runAction(move);
}