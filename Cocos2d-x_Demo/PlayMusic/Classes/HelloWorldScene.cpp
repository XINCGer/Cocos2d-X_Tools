#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
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
	is_paused = false;
	auto* label_play = Label::create("play", "Arial", 40);
	auto* pLabel_play = MenuItemLabel::create(label_play, this, menu_selector(HelloWorld::play));
	auto* button_play = Menu::create(pLabel_play, NULL);
	button_play->setPosition(160,180);
	addChild(button_play);

	auto* label_pause = Label::create("pause", "Arial", 40);
	auto* pLabel_pause = MenuItemLabel::create(label_pause, this, menu_selector(HelloWorld::pause));
	auto* button_pause = Menu::create(pLabel_pause, NULL);
	button_pause->setPosition(320,180);
	addChild(button_pause);

	auto* label_stop = Label::create("stop", "Arial", 40);
	auto* pLabel_stop = MenuItemLabel::create(label_stop, this, menu_selector(HelloWorld::stop));
	auto* button_stop = Menu::create(pLabel_stop, NULL);
	button_stop->setPosition(480,180);
	addChild(button_stop);
	return true;
}
void HelloWorld::play(cocos2d::Object* pSender)
{
	if (is_paused)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music.mp3");
	}
	is_paused = false;
}
void HelloWorld::stop(cocos2d::Object* pSender)
{
	is_paused = false;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}
void HelloWorld::pause(cocos2d::Object* pSender)
{
	is_paused = true;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}