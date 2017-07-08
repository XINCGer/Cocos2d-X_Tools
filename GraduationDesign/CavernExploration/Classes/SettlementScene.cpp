#include "SettlementScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace ui;

Button* to_btn;

Scene* SettlementScene::createScene()
{
	auto scene = Scene::create();
	auto settlement = SettlementScene::create();
	scene->addChild(settlement);
	return scene;
}
bool SettlementScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto* settlementScene = CSLoader::createNode("SettlementScene.csb");
	addChild(settlementScene);

	auto* bg = (ImageView*)settlementScene->getChildByName("background");
	auto* panel1 = (Layout*)bg->getChildByName("Panel_1");
	auto* panel2 = (Layout*)bg->getChildByName("Panel_2");
	auto* chnString = Dictionary::createWithContentsOfFile("chnString.xml");

	to_btn = (Button*)panel2->getChildByName("to_btn");
	to_btn->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto* to_next = TransitionFade::create(1.0f, StartGameScene::createScene());
			Director::getInstance()->replaceScene(to_next);
		}
	});

	auto* back_btn = (Button*)panel1->getChildByName("backToMenu");
	back_btn->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto* to_main = TransitionFade::create(0.5, MainScene::createScene());
			Director::getInstance()->replaceScene(to_main);
		}
	});

	if (UserDefault::sharedUserDefault()->getIntegerForKey("is_next_map") == 1)
	{
		panel1->setVisible(false);
		panel2->setVisible(true);
		auto* mission_text = (Text*)panel2->getChildByName("mission_text");
		int mission_num = UserDefault::sharedUserDefault()->getIntegerForKey("map_mission") + 1;
		UserDefault::sharedUserDefault()->setIntegerForKey("map_mission", mission_num);
		mission_text->setString(String::createWithFormat(((String*)chnString->objectForKey("next_mission"))->getCString(), mission_num)->getCString());
		UserDefault::sharedUserDefault()->setIntegerForKey("is_next_map", 0);
		this->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([&](){
			to_btn->setVisible(true);
		}), NULL));
	}
	else
	{
		panel1->setVisible(true);
		panel2->setVisible(false);

		auto* mon0_img = (ImageView*)panel1->getChildByName("mon1_img");
		auto* mon0_num = (Text*)mon0_img->getChildByName("mon1_num");
		auto* mon0_money = (Text*)mon0_img->getChildByName("mon1_money");
		auto* mon1_img = (ImageView*)panel1->getChildByName("mon2_img");
		auto* mon1_num = (Text*)mon1_img->getChildByName("mon2_num");
		auto* mon1_money = (Text*)mon1_img->getChildByName("mon2_money");
		auto* mon2_img = (ImageView*)panel1->getChildByName("mon3_img");
		auto* mon2_num = (Text*)mon2_img->getChildByName("mon3_num");
		auto* mon2_money = (Text*)mon2_img->getChildByName("mon3_money");
		auto* get_money = (Text*)panel1->getChildByName("get_money");
		auto* finish_text = (Text*)panel1->getChildByName("finish_text");


		mon0_num->setString(String::createWithFormat("x %d", UserDefault::sharedUserDefault()->getIntegerForKey("monstro0_num"))->getCString());
		mon0_money->setString(String::createWithFormat("%d", UserDefault::sharedUserDefault()->getIntegerForKey("monstro0_money"))->getCString());
		mon1_num->setString(String::createWithFormat("x %d", UserDefault::sharedUserDefault()->getIntegerForKey("monstro1_num"))->getCString());
		mon1_money->setString(String::createWithFormat("%d", UserDefault::sharedUserDefault()->getIntegerForKey("monstro1_money"))->getCString());
		mon2_num->setString(String::createWithFormat("x %d", UserDefault::sharedUserDefault()->getIntegerForKey("monstro2_num"))->getCString());
		mon2_money->setString(String::createWithFormat("%d", UserDefault::sharedUserDefault()->getIntegerForKey("monstro2_money"))->getCString());

		int get_money_num = UserDefault::sharedUserDefault()->getIntegerForKey("get_money");
		int all_money = UserDefault::sharedUserDefault()->getIntegerForKey("money");
		CCLOG("get_money=%d self_money=%d all_money=%d", get_money_num, all_money, get_money_num + all_money);

		int hp_lv = UserDefault::sharedUserDefault()->getIntegerForKey("hp_lv");
		int hp = (hp_lv - 1)*(hp_lv - 1) * 5 + 200 - UserDefault::sharedUserDefault()->getIntegerForKey("hp_lost");
		if (hp > 0)
		{
			finish_text->setString(((String*)chnString->objectForKey("win"))->getCString());
		}	
		else
		{
			get_money_num /= 10;
			finish_text->setString(((String*)chnString->objectForKey("fail"))->getCString());
		}
		get_money->setString(String::createWithFormat("+ %d", get_money_num)->getCString());
		UserDefault::sharedUserDefault()->setIntegerForKey("money", get_money_num + all_money);
	}
	return true;
}