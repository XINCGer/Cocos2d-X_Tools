#include "StartGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace ui;

GameScene* game;
//右上角直接退出控件
Layout* PanelTip;
//上部控件
LoadingBar* hp_bar;
Text* hp_num_text;
Text* money_text_get;
//下部控件
Text* skill_num_1;
Text* skill_num_2;
Text* skill_num_3;
//获得逃离卷轴
Layout* PanelGet;

Scene* StartGameScene::createScene()
{
	auto scene = Scene::create();
	auto startGame = StartGameScene::create();
	scene->addChild(startGame);
	return scene;
}
bool StartGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto* StartGameScene = CSLoader::createNode("StartGameScene.csb");
	addChild(StartGameScene);

	auto* bg = (ImageView*)StartGameScene->getChildByName("background");

	auto* maze = (Layout*)bg->getChildByName("Panel2_maze");
	game = GameScene::createGameScene();
	maze->addChild(game);
	game->setPosition(0, -440);

	//直接退出提示
	PanelTip = (Layout*)bg->getChildByName("Panel4_exit");
	PanelTip->setVisible(false);
	auto* btn_yep = (Button*)PanelTip->getChildByName("btn_yep");
	btn_yep->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			int hp_lv = UserDefault::sharedUserDefault()->getIntegerForKey("hp_lv");
			int hp = (hp_lv - 1)*(hp_lv - 1) * 5 + 200;
			UserDefault::sharedUserDefault()->setIntegerForKey("hp_lost", hp);
			auto* to_settlement = TransitionFade::create(0.5, SettlementScene::createScene());
			Director::getInstance()->replaceScene(to_settlement);
		}
	});
	auto* btn_nope = (Button*)PanelTip->getChildByName("btn_nope");
	btn_nope->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			PanelTip->setVisible(false);
		}
	});

	//下部道具
	auto* Panel_down = (Layout*)bg->getChildByName("Panel3_down");
	auto* skill_1 = (Button*)Panel_down->getChildByName("skill_1");
	skill_num_1 = (Text*)skill_1->getChildByName("skill_num_1");
	auto* skill_2 = (Button*)Panel_down->getChildByName("skill_2");
	skill_num_2 = (Text*)skill_2->getChildByName("skill_num_2");
	auto* skill_3 = (Button*)Panel_down->getChildByName("skill_3");
	skill_num_3 = (Text*)skill_3->getChildByName("skill_num_3");
	chgSkillNum(1);
	chgSkillNum(2);
	chgSkillNum(3);
	skill_1->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (UserDefault::sharedUserDefault()->getIntegerForKey("hp_skill_num") > 0)
			{
				int hp_ret_lv = UserDefault::sharedUserDefault()->getIntegerForKey("hp_ret_lv");
				int hp_ret = -((hp_ret_lv - 1) * 10 + 50);
				UserDefault::sharedUserDefault()->setIntegerForKey("hp_skill_num", UserDefault::sharedUserDefault()->getIntegerForKey("hp_skill_num") - 1);
				chgHPBar(hp_ret);
				chgSkillNum(1);
			}
		}
	});
	skill_2->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (UserDefault::sharedUserDefault()->getIntegerForKey("cq_skill_num") > 0)
			{
				if (game->cqSkill())
				{
					UserDefault::sharedUserDefault()->setIntegerForKey("cq_skill_num", UserDefault::sharedUserDefault()->getIntegerForKey("cq_skill_num") - 1);
					chgSkillNum(2);
				}
			}
		}
	});
	skill_3->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (UserDefault::sharedUserDefault()->getIntegerForKey("lk_skill_num") > 0)
			{
				auto* to_settlement = TransitionFade::create(0.5, SettlementScene::createScene());
				Director::getInstance()->replaceScene(to_settlement);
			}
		}
	});

	//上部信息
	auto* panel_up = (Layout*)bg->getChildByName("Panel1_up");
	auto* menu_btn = (Button*)panel_up->getChildByName("menu_btn");
	menu_btn->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			PanelTip->setVisible(true);
		}
	});
	//获取逃离卷轴
	PanelGet = (Layout*)bg->getChildByName("Panel5_getSk3");
	auto* getSK3_btn = (Button*)PanelGet->getChildByName("getSK3_btn");
	getSK3_btn->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			PanelGet->setVisible(false);
		}
	});
	//生命条
	auto* hp_part = (ImageView*)panel_up->getChildByName("Image_1");
	hp_bar = (LoadingBar*)hp_part->getChildByName("hp_bar");
	hp_num_text = (Text*)hp_part->getChildByName("hp_num");
	//攻击力
	auto* atk_num_text = (Text*)panel_up->getChildByName("atk_num");
	//护盾
	auto* def_num_text = (Text*)panel_up->getChildByName("def_num");

	//攻击力
	int atk_lv = UserDefault::sharedUserDefault()->getIntegerForKey("atk_lv");
	int atk = (atk_lv - 1)*(atk_lv - 1) * 2 + 1;
	CCLOG("atk_num_text is %s", String::createWithFormat("%d", atk)->getCString());
	atk_num_text->setText(String::createWithFormat("%d", atk)->getCString());
	//护盾
	int def_lv = UserDefault::sharedUserDefault()->getIntegerForKey("def_lv");
	int def = (def_lv - 1)*(def_lv - 1) * 2;
	CCLOG("def_num_text is %s", String::createWithFormat("%d", def)->getCString());
	def_num_text->setText(String::createWithFormat("%d", def)->getCString());
	//金币
	money_text_get = (Text*)panel_up->getChildByName("money_text");
	chgMoney();
	chgHPBar(0);
	return true;
}
void StartGameScene::chgSkillNum(int type)
{
	if (type == 1)
		skill_num_1->setText(String::createWithFormat("%d", UserDefault::sharedUserDefault()->getIntegerForKey("hp_skill_num"))->getCString());
	if (type == 2)
		skill_num_2->setText(String::createWithFormat("%d", UserDefault::sharedUserDefault()->getIntegerForKey("cq_skill_num"))->getCString());
	if (type == 3)
		skill_num_3->setText(String::createWithFormat("%d", UserDefault::sharedUserDefault()->getIntegerForKey("lk_skill_num"))->getCString());
}

void StartGameScene::chgMoney()
{
	money_text_get->setText(String::createWithFormat("%d", UserDefault::sharedUserDefault()->getIntegerForKey("get_money"))->getCString());
}

void StartGameScene::chgHPBar(int hint)
{
	CCLOG("hero was hunt by %d hp", hint);
	int hp_lv = UserDefault::sharedUserDefault()->getIntegerForKey("hp_lv");
	int hp_all = (hp_lv - 1)*(hp_lv - 1) * 20 + 200;
	int hp_lost = UserDefault::sharedUserDefault()->getIntegerForKey("hp_lost");
	hp_lost += hint;
	if (hp_lost < 0)
		hp_lost = 0;
	UserDefault::sharedUserDefault()->setIntegerForKey("hp_lost", hp_lost);
	int hp_now = hp_all - hp_lost;
	CCLOG("hp_num_text is %s", String::createWithFormat("%d/%d", hp_now, hp_all)->getCString());
	hp_num_text->setText(String::createWithFormat("%d/%d", hp_now, hp_all)->getCString());
	hp_bar->setPercent((float)hp_now / (float)hp_all*100);
}
void StartGameScene::showPanelGet()
{
	PanelGet->setVisible(true);
	chgSkillNum(3);
}

