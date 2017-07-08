#include "InstructScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace ui;

Scene* InstructScene::createScene()
{
	auto scene = Scene::create();
	auto instruct = InstructScene::create();
	scene->addChild(instruct);
	return scene;
}
bool InstructScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto* instructScene = CSLoader::createNode("InstructScene.csb");
	addChild(instructScene);

	auto* bg = (ImageView*)instructScene->getChildByName("background");

	auto* back_btn = (Button*)bg->getChildByName("backToMenu");
	back_btn->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto* to_main = TransitionFade::create(0.5, MainScene::createScene());
			Director::getInstance()->replaceScene(to_main);
		}
	});

	

	return true;
}