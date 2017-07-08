#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocostudio::timeline;
using namespace ui;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
	auto main = MainScene::create();
	scene->addChild(main);
	return scene;
}
bool MainScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
	
	auto* MainScene = CSLoader::createNode("MainScene.csb");
	addChild(MainScene);

	auto* bg = (ImageView*)MainScene->getChildByName("background");

	auto* start_btn = (Button*)bg->getChildByName("start");
	start_btn->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto* to_ready = TransitionFade::create(0.5, SettlementScene::createScene());
			Director::getInstance()->replaceScene(to_ready);
		}
	});

	auto* shop_btn = (Button*)bg->getChildByName("shop");
	shop_btn->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto* to_shop = TransitionFade::create(0.5, ShopScene::createScene());
			Director::getInstance()->replaceScene(to_shop);
		}
	});

	auto* instruct_btn = (Button*)bg->getChildByName("instruct");
	instruct_btn->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto* to_instruct = TransitionFade::create(0.5, InstructScene::createScene());
			Director::getInstance()->replaceScene(to_instruct);
		}
	});

	auto* exit_btn = (Button*)bg->getChildByName("exit");
	exit_btn->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			exit(-1);
		}
	});

	if (UserDefault::sharedUserDefault()->getIntegerForKey("exist") == 0)
	{
		//基础部分+商店
		UserDefault::sharedUserDefault()->setIntegerForKey("exist", 1); //存在
		UserDefault::sharedUserDefault()->setIntegerForKey("money", 1000); //金币
		UserDefault::sharedUserDefault()->setIntegerForKey("hp_lv", 1); //血量等级
		UserDefault::sharedUserDefault()->setIntegerForKey("atk_lv", 1); //攻击力等级
		UserDefault::sharedUserDefault()->setIntegerForKey("def_lv", 1); //护盾等级
		UserDefault::sharedUserDefault()->setIntegerForKey("hp_ret_lv", 1); //回血量等级
		UserDefault::sharedUserDefault()->setIntegerForKey("crp", 1); //暴击率
		UserDefault::sharedUserDefault()->setIntegerForKey("crt", 100); //暴击倍数/100

		//战斗道具部分
		UserDefault::sharedUserDefault()->setIntegerForKey("hp_skill_num", 10); //血瓶数量
		UserDefault::sharedUserDefault()->setIntegerForKey("cq_skill_num", 10); //穿墙数量
		//计算式： 实际攻击力=攻击力*（暴击倍数/100+1）
		//计算式： 实际受到伤害=受到伤害-护盾 （实际受到伤害>=1）
		/*等级换算公式：
			血量 = (hp_lv - 1)*(hp_lv - 1)*5 + 200
			攻击力 = (atk_lv - 1)*(atk_lv - 1)*2 + 1
			护盾 = (def_lv - 1)*(def_lv - 1)*2
			回血量 = (hp_ret_lv-1)*10 + 50
		*/
	}
	//進入戰鬥恢复戰鬥数值
	UserDefault::sharedUserDefault()->setIntegerForKey("get_money", 0); //战斗中获得的金币
	UserDefault::sharedUserDefault()->setIntegerForKey("hp_lost", 0); //消耗血量
	UserDefault::sharedUserDefault()->setIntegerForKey("lk_skill_num", 1); //离开数量 
	UserDefault::sharedUserDefault()->setIntegerForKey("monstro0_num", 0); //怪物1数量
	UserDefault::sharedUserDefault()->setIntegerForKey("monstro0_money", 0); //怪物1金币
	UserDefault::sharedUserDefault()->setIntegerForKey("monstro1_num", 0); //怪物2数量
	UserDefault::sharedUserDefault()->setIntegerForKey("monstro1_money", 0); //怪物2金币
	UserDefault::sharedUserDefault()->setIntegerForKey("monstro2_num", 0); //怪物3数量
	UserDefault::sharedUserDefault()->setIntegerForKey("monstro2_money", 0); //怪物3金币
	UserDefault::sharedUserDefault()->setIntegerForKey("map_mission", 0); //地图关卡数
	UserDefault::sharedUserDefault()->setIntegerForKey("is_next_map", 1); //是否下一关
	UserDefault::sharedUserDefault()->setIntegerForKey("lk_skill_num", 0); //离开数量 

    return true;
}