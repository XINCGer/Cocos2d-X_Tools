#include "ShopScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace ui;

//背景图
ImageView* bg;
//属性部分
Text* attr_1;
Text* attr_2;
Text* attr_3;
Text* attr_4;
Text* attr_num_1;
Text* attr_num_2;
Text* attr_num_3;
Text* attr_num_4;
Text* money_text_cost;
//按钮数值
Text* up_1;
Text* cost_1;
Text* lv_1;
Text* up_2;
Text* cost_2;
Text* lv_2;
Text* up_3;
Text* cost_3;
Text* lv_3;
Text* up_4;
Text* cost_4;
Text* lv_4;
//每页商品数量
int item_nums[4] = { 4, 2, 0, 0 };
int page_now;

Scene* ShopScene::createScene()
{
	auto scene = Scene::create();
	auto shop = ShopScene::create();
	scene->addChild(shop);
	return scene;
}
bool ShopScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto* ShopScene = CSLoader::createNode("ShopScene.csb");
	addChild(ShopScene);

	bg = (ImageView*)ShopScene->getChildByName("background");
	auto* panel2 = (Layout*)bg->getChildByName("Panel_2");
	panel2->setVisible(false);

	auto* back_btn = (Button*)bg->getChildByName("backToMenu");
	back_btn->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto* to_main = TransitionFade::create(0.5, MainScene::createScene());
			Director::getInstance()->replaceScene(to_main);
		}
	});

	auto* btn_page1 = (Button*)bg->getChildByName("btn_page1");
	btn_page1->setBright(false);
	btn_page1->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto* panel1 = (Layout*)bg->getChildByName("Panel_1");
			auto* panel2 = (Layout*)bg->getChildByName("Panel_2");
			panel1->setVisible(true);
			panel2->setVisible(false);
			auto* btn_page1 = (Button*)bg->getChildByName("btn_page1");
			auto* btn_page2 = (Button*)bg->getChildByName("btn_page2");
			btn_page1->setBright(false);
			btn_page2->setBright(true);
			page_now = 1;
			reGetUI();
			for (int i = 1; i <= 4; i++)
			{
				if (i <= item_nums[page_now - 1])
					refreshUI(page_now, i, true);
			}
		}
	});
	auto* btn_page2 = (Button*)bg->getChildByName("btn_page2");
	btn_page2->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto* panel1 = (Layout*)bg->getChildByName("Panel_1");
			auto* panel2 = (Layout*)bg->getChildByName("Panel_2");
			panel1->setVisible(false);
			panel2->setVisible(true);
			auto* btn_page1 = (Button*)bg->getChildByName("btn_page1");
			auto* btn_page2 = (Button*)bg->getChildByName("btn_page2");
			btn_page1->setBright(true);
			btn_page2->setBright(false);
			page_now = 2;
			reGetUI();
			for (int i = 1; i <= 4; i++)
			{
				if (i <= item_nums[page_now - 1])
					refreshUI(page_now, i, true);
			}
		}
	});

	attr_1 = (Text*)bg->getChildByName("attr_1");
	attr_2 = (Text*)bg->getChildByName("attr_2");
	attr_3 = (Text*)bg->getChildByName("attr_3");
	attr_4 = (Text*)bg->getChildByName("attr_4");
	attr_num_1 = (Text*)bg->getChildByName("attr_num_1");
	attr_num_2 = (Text*)bg->getChildByName("attr_num_2");
	attr_num_3 = (Text*)bg->getChildByName("attr_num_3");
	attr_num_4 = (Text*)bg->getChildByName("attr_num_4");
	money_text_cost = (Text*)bg->getChildByName("money_text");
	money_text_cost->setText(String::createWithFormat("%d", UserDefault::sharedUserDefault()->getIntegerForKey("money"))->getCString());

	page_now = 1;
	reGetUI();

	refreshUI(page_now, 1, true);
	refreshUI(page_now, 2, true);
	refreshUI(page_now, 3, true);
	refreshUI(page_now, 4, true);

	return true;
}

void ShopScene::reGetUI()
{
	auto* Panel = (Layout*)bg->getChildByName(String::createWithFormat("Panel_%d", page_now)->getCString());
	auto* Button_1 = (Button*)Panel->getChildByName("Button_1");
	up_1 = (Text*)Button_1->getChildByName("up_1");
	cost_1 = (Text*)Button_1->getChildByName("cost_1");
	lv_1 = (Text*)Button_1->getChildByName("lv_1");
	auto* Button_2 = (Button*)Panel->getChildByName("Button_2");
	up_2 = (Text*)Button_2->getChildByName("up_2");
	cost_2 = (Text*)Button_2->getChildByName("cost_2");
	lv_2 = (Text*)Button_2->getChildByName("lv_2");
	auto* Button_3 = (Button*)Panel->getChildByName("Button_3");
	up_3 = (Text*)Button_3->getChildByName("up_3");
	cost_3 = (Text*)Button_3->getChildByName("cost_3");
	lv_3 = (Text*)Button_3->getChildByName("lv_3");
	auto* Button_4 = (Button*)Panel->getChildByName("Button_4");
	up_4 = (Text*)Button_4->getChildByName("up_4");
	cost_4 = (Text*)Button_4->getChildByName("cost_4");
	lv_4 = (Text*)Button_4->getChildByName("lv_4");

	//按钮点击事件
	Button_1->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (page_now == 1)
				if (UserDefault::sharedUserDefault()->getIntegerForKey("hp_lv") * 50 <= UserDefault::sharedUserDefault()->getIntegerForKey("money"))
				{
					UserDefault::sharedUserDefault()->setIntegerForKey("hp_lv", UserDefault::sharedUserDefault()->getIntegerForKey("hp_lv") + 1);
					refreshUI(1, 1, false);
				}	
			if (page_now == 2)
				if (50 <= UserDefault::sharedUserDefault()->getIntegerForKey("money"))
				{
					UserDefault::sharedUserDefault()->setIntegerForKey("hp_skill_num", UserDefault::sharedUserDefault()->getIntegerForKey("hp_skill_num") + 1);
					refreshUI(2, 1, false);
				}
		}
	});
	Button_2->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (page_now == 1)
				if (UserDefault::sharedUserDefault()->getIntegerForKey("atk_lv") * 50 <= UserDefault::sharedUserDefault()->getIntegerForKey("money"))
				{
					UserDefault::sharedUserDefault()->setIntegerForKey("atk_lv", UserDefault::sharedUserDefault()->getIntegerForKey("atk_lv") + 1);
					refreshUI(1, 2, false);
				}
			if (page_now == 2)
				if (100 <= UserDefault::sharedUserDefault()->getIntegerForKey("money"))
				{
					UserDefault::sharedUserDefault()->setIntegerForKey("cq_skill_num", UserDefault::sharedUserDefault()->getIntegerForKey("cq_skill_num") + 1);
					refreshUI(2, 2, false);
				}
		}
	});
	Button_3->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (page_now == 1)
				if (UserDefault::sharedUserDefault()->getIntegerForKey("def_lv") * 50 <= UserDefault::sharedUserDefault()->getIntegerForKey("money"))
				{
					UserDefault::sharedUserDefault()->setIntegerForKey("def_lv", UserDefault::sharedUserDefault()->getIntegerForKey("def_lv") + 1);
					refreshUI(1, 3, false);
				}
		}
	});
	Button_4->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (page_now == 1)
				if (UserDefault::sharedUserDefault()->getIntegerForKey("hp_ret_lv") * 50 <= UserDefault::sharedUserDefault()->getIntegerForKey("money"))
				{
					UserDefault::sharedUserDefault()->setIntegerForKey("hp_ret_lv", UserDefault::sharedUserDefault()->getIntegerForKey("hp_ret_lv") + 1);
					refreshUI(1, 4, false);
				}
		}
	});
	//是否显示
	for (int i = 1; i <= 4; i++)
	{
		auto* attr_text = (Text*)bg->getChildByName(String::createWithFormat("attr_%d", i)->getCString());
		auto* attr_num_text = (Text*)bg->getChildByName(String::createWithFormat("attr_num_%d", i)->getCString());
		auto* Button_panel = (Text*)Panel->getChildByName(String::createWithFormat("Button_%d", i)->getCString());
		if (i <= item_nums[page_now - 1])
		{
			attr_text->setVisible(true);
			attr_num_text->setVisible(true);
			Button_panel->setVisible(true);
		}
		else
		{
			attr_text->setVisible(false);
			attr_num_text->setVisible(false);
			Button_panel->setVisible(false);
		}
	}
}

void ShopScene::refreshMoney(int cost)
{
	int money_old = UserDefault::sharedUserDefault()->getIntegerForKey("money");
	int money_new = money_old - cost;
	UserDefault::sharedUserDefault()->setIntegerForKey("money", money_new);
	money_text_cost->setText(String::createWithFormat("%d", money_new)->getCString());
}

void ShopScene::refreshUI(int page, int type, bool isCreate)
{
	auto* chnString = Dictionary::createWithContentsOfFile("chnString.xml");
	CCLOG("refreshUI page=%d type=%d", page, type);
	if ((page == 1) && (type == 1)) //生命值
	{
		int hp_lv = UserDefault::sharedUserDefault()->getIntegerForKey("hp_lv");
		int hp_all = (hp_lv - 1)*(hp_lv - 1) * 5 + 200;
		attr_1->setText(((String*)chnString->objectForKey("hp"))->getCString());
		attr_num_1->setText(String::createWithFormat("%d", hp_all)->getCString());
		up_1->setText(String::createWithFormat(((String*)chnString->objectForKey("hp_up"))->getCString(), ((hp_lv*hp_lv * 5 + 200) - hp_all))->getCString());
		cost_1->setText(String::createWithFormat(((String*)chnString->objectForKey("cost"))->getCString(), (hp_lv * 50))->getCString());
		lv_1->setText(String::createWithFormat("%d", hp_lv)->getCString());
		if (!isCreate)
			refreshMoney(hp_lv * 50);
	}
	if ((page == 1) && (type == 2)) //攻击力
	{
		int atk_lv = UserDefault::sharedUserDefault()->getIntegerForKey("atk_lv");
		int atk = (atk_lv - 1)*(atk_lv - 1) * 2 + 1;
		attr_2->setText(((String*)chnString->objectForKey("atk"))->getCString());
		attr_num_2->setText(String::createWithFormat("%d", atk)->getCString());
		up_2->setText(String::createWithFormat(((String*)chnString->objectForKey("atk_up"))->getCString(), (atk_lv*atk_lv * 2 + 1) - atk)->getCString());
		cost_2->setText(String::createWithFormat(((String*)chnString->objectForKey("cost"))->getCString(), atk_lv * 50)->getCString());
		lv_2->setText(String::createWithFormat("%d", atk_lv)->getCString());
		if (!isCreate)
			refreshMoney(atk_lv * 50);
	}
	if ((page == 1) && (type == 3)) //护盾
	{
		int def_lv = UserDefault::sharedUserDefault()->getIntegerForKey("def_lv");
		int def = (def_lv - 1)*(def_lv - 1) * 2;
		attr_3->setText(((String*)chnString->objectForKey("def"))->getCString());
		attr_num_3->setText(String::createWithFormat("%d", def)->getCString());
		up_3->setText(String::createWithFormat(((String*)chnString->objectForKey("def_up"))->getCString(), (def_lv*def_lv * 2) - def)->getCString());
		cost_3->setText(String::createWithFormat(((String*)chnString->objectForKey("cost"))->getCString(), def_lv * 50)->getCString());
		lv_3->setText(String::createWithFormat("%d", def_lv)->getCString());
		if (!isCreate)
			refreshMoney(def_lv * 50);
	}
	if ((page == 1) && (type == 4)) //回血量
	{
		int hp_ret_lv = UserDefault::sharedUserDefault()->getIntegerForKey("hp_ret_lv");
		int hp_ret = (hp_ret_lv - 1) * 10 + 50;
		attr_4->setText(((String*)chnString->objectForKey("hp_ret"))->getCString());
		attr_num_4->setText(String::createWithFormat("%d", hp_ret)->getCString());
		up_4->setText(String::createWithFormat(((String*)chnString->objectForKey("hp_ret_up"))->getCString(), (hp_ret_lv * 10 + 50) - hp_ret)->getCString());
		cost_4->setText(String::createWithFormat(((String*)chnString->objectForKey("cost"))->getCString(), hp_ret_lv * 50)->getCString());
		lv_4->setText(String::createWithFormat("%d", hp_ret_lv)->getCString());
		if (!isCreate)
			refreshMoney(hp_ret_lv * 50);
	}
	if ((page == 2) && (type == 1)) //血瓶数
	{
		int hp_num = UserDefault::sharedUserDefault()->getIntegerForKey("hp_skill_num");
		attr_1->setText(((String*)chnString->objectForKey("xp"))->getCString());
		attr_num_1->setText(String::createWithFormat("%d", hp_num)->getCString());
		up_1->setText(((String*)chnString->objectForKey("xp_up"))->getCString());
		cost_1->setText(String::createWithFormat(((String*)chnString->objectForKey("cost"))->getCString(), 50)->getCString());
		lv_1->setText(String::createWithFormat("%d", hp_num)->getCString());
		if (!isCreate)
			refreshMoney(50);
	}
	if ((page == 2) && (type == 2)) //穿墙数
	{
		int cq_num = UserDefault::sharedUserDefault()->getIntegerForKey("cq_skill_num");
		attr_2->setText(((String*)chnString->objectForKey("cq"))->getCString());
		attr_num_2->setText(String::createWithFormat("%d", cq_num)->getCString());
		up_2->setText(((String*)chnString->objectForKey("cq_up"))->getCString());
		cost_2->setText(String::createWithFormat(((String*)chnString->objectForKey("cost"))->getCString(), 100)->getCString());
		lv_2->setText(String::createWithFormat("%d", cq_num)->getCString());
		if (!isCreate)
			refreshMoney(100);
	}
}