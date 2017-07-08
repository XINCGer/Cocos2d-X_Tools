#include "Monstro.h"

Monstro* Monstro::createMonstro(int type)
{
	Monstro* monstro = new Monstro();
	if (monstro && monstro->init())
	{
		monstro->autorelease();
		monstro->monstroInit(type);
		return monstro;
	}
	CC_SAFE_DELETE(monstro);
	return NULL;
}
bool Monstro::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
void Monstro::monstroInit(int type)
{
	this->type = type;
	monstro_frame = SpriteFrameCache::getInstance();
	monstro_frame->addSpriteFramesWithFile(String::createWithFormat("Monstros/M%dPlist.plist", type)->getCString(), String::createWithFormat("Monstros/M%dPlist.png", type)->getCString());

	monstro = Sprite::create(String::createWithFormat("m%d_start.png", type)->getCString());
	this->addChild(monstro);
}
void Monstro::faceTo(int dirc)
{
	monstro->initWithSpriteFrameName(String::createWithFormat("Monstros/m%d_%d.png", type, dirc*3)->getCString());
}
void Monstro::disappear()
{
	auto* fadeAct = FadeOut::create(0.8f);
	this->monstro->runAction(fadeAct);
}