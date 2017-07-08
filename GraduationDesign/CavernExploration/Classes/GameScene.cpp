#include "GameScene.h"
#include "StartGameScene.h"

//穿墙方向值
int cq_dirc[4][2] = { { 2, 0 }, { 0, -2 }, { -2, 0 }, { 0, 2 } };
//怪物属性 [type][lv][attrs] --0生命值--1攻击力--2获得金币--
int MONSTROATTR[3][5][3] =
{
	{ { 5, 3, 10 }, { 7, 3, 12 }, { 10, 5, 15 }, { 20, 8, 20 }, { 30, 15, 30 } },
	{ { 3, 5, 10 }, { 3, 7, 12 }, { 5, 10, 15 }, { 8, 20, 20 }, { 15, 30, 30 } },
	{ { 5, 5, 10 }, { 7, 7, 12 }, { 10, 10, 15 }, { 20, 20, 20 }, { 30, 30, 30 } },
};
//怪物层数配置 [mission][type]
int MONSTRONUM[10][3] = {
	{ 4, 4, 2 },
	{ 4, 4, 2 },
	{ 4, 4, 2 },
	{ 5, 4, 2 },
	{ 5, 5, 3 },
	{ 5, 5, 3 },
	{ 6, 5, 3 },
	{ 6, 6, 3 },
	{ 6, 6, 4 },
	{ 6, 6, 5 },
};
//人物属性
int atk;
int def;

GameScene* GameScene::createGameScene()
{
	GameScene* game = new GameScene();
	if (game && game->init())
	{
		game->autorelease();
		game->gameInit();
		return game;
	}
	CC_SAFE_DELETE(game);
	return NULL;
}
bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	map = NewMap::createMap();	//生成地图数组
	mapItem = MapItem::createWall();
	addChild(mapItem);

	for (int i = 0; i < MAPSIZE; i++)	//获取地图
	{
		for (int j = 0; j < MAPSIZE; j++)
		{
			maze[i][j] = map->getMaze(i, j);
		}
	}
	maze[2][0] = maze[MAPSIZE - 3][MAPSIZE - 1] = 0;	//出入口修改

	addWall(); //地图图片
	addChild(map);

	hero = Hero::createHero();	//创建英雄
	addChild(hero);
	dirc_now = 3;

	srand(time(0));
	
	bool noHaveSk3 = true;
	while (noHaveSk3)
	{
		int x_sk3 = random(12, MAPSIZE - 2);
		int y_sk3 = random(12, MAPSIZE - 2);
		if (IsCreateSk3(x_sk3, y_sk3))
		{
			mapItem->addSK3Img(x_sk3, y_sk3);
			noHaveSk3 = false;
		}
	}
	

	int map_mossion = UserDefault::sharedUserDefault()->getIntegerForKey("map_mission");
	for (int i = 0; i < 3; i++)
	{
		monstro_num = 0;  //敌人 已存在敌人数量
		while (monstro_num < MONSTRONUM[map_mossion][i])
		{
			int type_tag = i + 2 + monstro_num * 3; //tag
			int x = random(2, MAPSIZE-2);
			int y = random(2, MAPSIZE-2);
			if (GameScene::IsCreateMonstro(type_tag, x, y))
			{
				CCLOG("monstro num=%d x=%d y=%d state=%d", monstro_num, x, y, maze[y][x]);
				mapItem->addMonstorImg(type_tag, i, x, y);
				monstro_num++;
			}
		}
	}

	auto* dispather = Director::getInstance()->getEventDispatcher();
	auto* listener = EventListenerTouchOneByOne::create();

	isMove = false; //是否在移动 防止没有运动完成时发生下一个运动

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	dispather->addEventListenerWithSceneGraphPriority(listener, this);

	//打印地图
	for (int i = 0; i < MAPSIZE; i++)
	{
		CCLOG("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
			maze[i][0], maze[i][1], maze[i][2], maze[i][3], maze[i][4], maze[i][5],
			maze[i][6], maze[i][7], maze[i][8], maze[i][9], maze[i][10], maze[i][11],
			maze[i][12], maze[i][13], maze[i][14], maze[i][15], maze[i][16], maze[i][17],
			maze[i][18], maze[i][19], maze[i][20], maze[i][21], maze[i][22]);
	}
	//战斗资源加载
	beat_frame = SpriteFrameCache::getInstance();
	beat_frame->addSpriteFramesWithFile("hitAnim/BeatPlist.plist", "hitAnim/BeatPlist.png");
	//人物属性加载
	int atk_lv = UserDefault::sharedUserDefault()->getIntegerForKey("atk_lv");
	atk = (atk_lv - 1)*(atk_lv - 1) * 2 + 1;
	int def_lv = UserDefault::sharedUserDefault()->getIntegerForKey("def_lv");
	def = (def_lv - 1)*(def_lv - 1) * 2;

	return true;
}
void GameScene::gameInit()
{
	return;
}
void GameScene::showHeroInfo()
{
	
}
bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	this->x = touch->getLocation().x;
	this->y = touch->getLocation().y;
	return true;
}
void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{

}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	float dx = touch->getLocation().x;
	float dy = touch->getLocation().y;

	int hx = (hero->hero->getPositionX() - mapItem->getPositionX());	//当前英雄所在位置
	int hy = (hero->hero->getPositionY() - mapItem->getPositionY());

	int hi = MAPSIZE - 1 - (hy + 20) / 40;	//当前英雄所在坐标
	int hj = (hx + 20) / 40;

	CCLOG("this is maze[%d][%d]", hi, hj);
	CCLOG("and the state of this maze is %d", maze[hi][hj]);
	CCLOG("now position is %d %d", hero->hero->getPositionX(), hero->hero->getPositionY());

	isCanMove = false;	//移动方向的下一个位置是否可以去

	//方向   0-下   1-左   2-上   3-右
	if (!(fabs(dy - y) < 100 && fabs(dx - x) < 100))	//判断方向
	{
		if (!isMove)
		{
			isMove = true;
			if ((dy < y) && (((dy - y) / (dx - x) > 1) || ((dy - y) / (dx - x) < -1)))
			{
				CCLOG("0--D");
				dirc_now = 0;
				hi++;
			}
			if ((dx < x) && ((dy - y) / (dx - x) >= -1) && ((dy - y) / (dx - x) <= 1))
			{
				CCLOG("1--L");
				dirc_now = 1;
				hj--;
			}
			if ((dy > y) && (((dy - y) / (dx - x) > 1) || ((dy - y) / (dx - x) < -1)))
			{
				CCLOG("2--U");
				dirc_now = 2;
				hi--;
			}
			if ((dx > x) && ((dy - y) / (dx - x) >= -1) && ((dy - y) / (dx - x) <= 1))
			{
				CCLOG("3--R");
				dirc_now = 3;
				hj++;
			}
			CCLOG("move to maze[%d][%d]", hi, hj);
			CCLOG("and the state of the new maze is %d", maze[hi][hj]);
			//可行走
			if (maze[hi][hj] == 1)
			{
				if ((hi == 16 && dirc_now == 0) || (hj == 5 && dirc_now == 1) || (hi == 5 && dirc_now == 2) || (hj == 17 && dirc_now == 3))
					bgMoveTo(dirc_now);
				else
				{
					if ((hi < 6 || hi>15) && (hj < 6 || hj>16))
						hero->Hero::moveTo(dirc_now);
					else
					{
						if ((hi >= 6 && hi <= 15) && (hj < 6 || hj>16) && (dirc_now == 1 || dirc_now == 3))
							hero->Hero::moveTo(dirc_now);
						else
						{
							if ((hi < 6 || hi>15) && (hj >= 6 && hj <= 16) && (dirc_now == 0 || dirc_now == 2))
								hero->Hero::moveTo(dirc_now);
							else
								bgMoveTo(dirc_now);
						}
					}
				}
				//出口
				if ((hi == MAPSIZE - 3) && (hj == MAPSIZE - 2))
				{
					isMove = true;
					hero->Hero::disappear();
					this->runAction(Sequence::create(DelayTime::create(0.8f), CallFunc::create([&](){
						if (UserDefault::sharedUserDefault()->getIntegerForKey("map_mission") == 10)
							UserDefault::sharedUserDefault()->setIntegerForKey("is_next_map", 0); //最后一层
						else
							UserDefault::sharedUserDefault()->setIntegerForKey("is_next_map", 1); //进入下一关
						auto* to_settlement = TransitionFade::create(1.0f, SettlementScene::createScene());
						Director::getInstance()->replaceScene(to_settlement);
					}), NULL));
				}
				auto* callFunc1 = DelayTime::create(0.8f);
				auto* callFunc2 = CallFunc::create(CC_CALLBACK_0(GameScene::chgMove, this));
				auto* cm = Sequence::create(callFunc1, callFunc2, NULL);
				this->runAction(cm);
			}
			//墙
			if (maze[hi][hj] == 0)
			{
				isMove = false;
				hero->Hero::faceTo(dirc_now);
			}
			//进入战斗
			if ((maze[hi][hj] >= 2)&&(maze[hi][hj]!=200))
			{
				isMove = true;
				hero->Hero::faceTo(dirc_now);
				monstro_fight = (Monstro*)mapItem->getChildByTag(maze[hi][hj]);
				CCLOG("------monstro %d%d %d %f %f", hi, hj, maze[hi][hj], monstro_fight->getPositionX(), monstro_fight->getPositionY());
				CCLOG("---------hero %f %f", hero->getPositionX(), hero->getPositionY());
				monstro_fight->faceTo((dirc_now + 2) % 4);
				//怪物信息
				UserDefault::sharedUserDefault()->setIntegerForKey("monstro_hp", MONSTROATTR[monstro_fight->type][0][0]);
				CCLOG("monstro info is hp=%d atk=%d getMoney=%d", MONSTROATTR[monstro_fight->type][0][0], MONSTROATTR[monstro_fight->type][0][1], MONSTROATTR[monstro_fight->type][0][2]);
				heroFight();
				maze[hi][hj] = 1;
			}
			//获取逃离卷轴
			if (maze[hi][hj] == 200)
			{
				isMove = false;
				maze[hi][hj] = 1;
				UserDefault::sharedUserDefault()->setIntegerForKey("lk_skill_num", 1);
				mapItem->removeChildByTag(200);
				StartGameScene::showPanelGet();
			}
		}
		else
		{
			CCLOG("now state of isMove is TRUE");
		}
	}
}
void GameScene::addWall()
{
	for (int i = 1; i < MAPSIZE - 1; i++) //y
	{
		for (int j = 1; j < MAPSIZE - 1; j++) //x
		{
			if (maze[i][j] == 0)
			{
				if ((maze[i + 1][j] == 1) && (i + 1 != 0))
				{
					mapItem->addWallImg(6, i, j);
				}
				else
				{
					mapItem->addWallImg(5, i, j);
				}
			}
			else
			{
				mapItem->addWallImg(4, i, j);
				if ((maze[i][j - 1] == 0) || (maze[i - 1][j] == 0))
				{
					mapItem->addWallImg(1, i, j);
					if (maze[i][j - 1] != 0)
					{
						mapItem->addWallImg(2, i, j);
					}
					if (maze[i - 1][j] != 0)
					{
						mapItem->addWallImg(3, i, j);
					}
				}
			}
		}
	}
	//入口
	mapItem->addWallImg(0, 2, 1);
	//出口
	mapItem->addWallImg(7, MAPSIZE - 3, MAPSIZE - 2);
}
void GameScene::chgMove()
{
	isMove = false;
}
void GameScene::bgMoveTo(int dirc)
{
	int mx = mapItem->getPositionX();
	int my = mapItem->getPositionY();

	if (dirc == 0)
		my += 40;
	if (dirc == 1)
		mx += 40;
	if (dirc == 2)
		my -= 40;
	if (dirc == 3)
		mx -= 40;

	auto* bgMoveAct = MoveTo::create(0.8f, Vec2(mx, my));
	auto* heroMoveAct = hero->Hero::moveAct(dirc);

	hero->hero->runAction(heroMoveAct);
	mapItem->runAction(bgMoveAct);
}

bool GameScene::cqSkill()
{
	int hx = (hero->hero->getPositionX() - mapItem->getPositionX());	//当前英雄所在位置
	int hy = (hero->hero->getPositionY() - mapItem->getPositionY());
	int hi = MAPSIZE - 1 - (hy + 20) / 40;	//当前英雄所在坐标
	int hj = (hx + 20) / 40;
	int hi_to = hi + cq_dirc[dirc_now][0];
	int hj_to = hj + cq_dirc[dirc_now][1];
	CCLOG("from maze[%d][%d]=%d to maze[%d][%d]=%d and dirc=%d", hi, hj, maze[hi][hj], hi_to, hj_to, maze[hi_to][hj_to], dirc_now);
	if ((!isMove) && (maze[hi_to][hj_to] == 1) && (hi_to > 0) && (hi_to < (MAPSIZE - 2)) && (hj_to>0) && (hj_to < (MAPSIZE - 2)))
	{
		if ((hi_to == 16 && dirc_now == 0) || (hj_to == 5 && dirc_now == 1) || (hi_to == 5 && dirc_now == 2) || (hj_to == 17 && dirc_now == 3))
		{
			mapItem->setPositionX(mapItem->getPositionX() - cq_dirc[dirc_now][1] * 40);
			mapItem->setPositionY(mapItem->getPositionY() + cq_dirc[dirc_now][0] * 40);
		}
		else
		{
			if ((hi_to < 6 || hi_to>15) && (hj_to < 6 || hj_to>16))
			{
				hero->hero->setPositionX(hero->hero->getPositionX() + cq_dirc[dirc_now][1] * 40);
				hero->hero->setPositionY(hero->hero->getPositionY() - cq_dirc[dirc_now][0] * 40);
			}
			else
			{
				if ((hi_to >= 6 && hi_to <= 15) && (hj_to < 6 || hj_to>16) && (dirc_now == 1 || dirc_now == 3))
				{
					hero->hero->setPositionX(hero->hero->getPositionX() + cq_dirc[dirc_now][1] * 40);
					hero->hero->setPositionY(hero->hero->getPositionY() - cq_dirc[dirc_now][0] * 40);
				}
				else
				{
					if ((hi_to < 6 || hi_to>15) && (hj_to >= 6 && hj_to <= 16) && (dirc_now == 0 || dirc_now == 2))
					{
						hero->hero->setPositionX(hero->hero->getPositionX() + cq_dirc[dirc_now][1] * 40);
						hero->hero->setPositionY(hero->hero->getPositionY() - cq_dirc[dirc_now][0] * 40);
					}
					else
					{
						mapItem->setPositionX(mapItem->getPositionX() - cq_dirc[dirc_now][1] * 40);
						mapItem->setPositionY(mapItem->getPositionY() + cq_dirc[dirc_now][0] * 40);
					}
				}
			}
		}
		//特殊情况 临界点时要回退一格
		if (((hj_to == 4) && (dirc_now == 1)) || (hj_to == 6) && (dirc_now == 3))
		{
			hero->hero->setPositionX(hero->hero->getPositionX() + 40);
			mapItem->setPositionX(mapItem->getPositionX() + 40);
		}
		if (((hj_to == 16) && (dirc_now == 1)) || (hj_to == 18) && (dirc_now == 3))
		{
			hero->hero->setPositionX(hero->hero->getPositionX() - 40);
			mapItem->setPositionX(mapItem->getPositionX() - 40);
		}
		if (((hi_to == 6) && (dirc_now == 0)) || (hi_to == 4) && (dirc_now == 2))
		{
			hero->hero->setPositionY(hero->hero->getPositionY() - 40);
			mapItem->setPositionY(mapItem->getPositionY() - 40);
		}
		if (((hi_to == 17) && (dirc_now == 0)) || (hi_to == 15) && (dirc_now == 2))
		{
			hero->hero->setPositionY(hero->hero->getPositionY() + 40);
			mapItem->setPositionY(mapItem->getPositionY() + 40);
		}
		return true;
	}
	return false;
}

bool GameScene::IsCreateMonstro(int monstro_num, int x, int y)
{
	if ((maze[y][x] == 1) && (x > 0) && (x < (MAPSIZE - 2)) && (y>0) && (y < (MAPSIZE - 2)))
	{
		maze[y][x] = monstro_num;
		return true;
	}
	else
		return false;
}

void GameScene::heroFight()
{
	UserDefault::sharedUserDefault()->setIntegerForKey("monstro_hp", UserDefault::sharedUserDefault()->getIntegerForKey("monstro_hp") - atk);
	this->runAction(Sequence::create(CallFunc::create([&](){fight(true); }), DelayTime::create(1.0f), CallFunc::create([&](){
		int monstro_hp = UserDefault::sharedUserDefault()->getIntegerForKey("monstro_hp");
		if (monstro_hp > 0)
		{
			CCLOG("mosntro hp=%d", monstro_hp);
			MonstroFight();
		}
		else
		{
			UserDefault::sharedUserDefault()->setIntegerForKey("get_money", UserDefault::sharedUserDefault()->getIntegerForKey("get_money") + MONSTROATTR[monstro_fight->type][0][2]);
			int monstro_num = UserDefault::sharedUserDefault()->getIntegerForKey(String::createWithFormat("monstro%d_num", monstro_fight->type)->getCString()) + 1;
			UserDefault::sharedUserDefault()->setIntegerForKey(String::createWithFormat("monstro%d_num", monstro_fight->type)->getCString(), monstro_num);
			int monstro_money = UserDefault::sharedUserDefault()->getIntegerForKey(String::createWithFormat("monstro%d_money", monstro_fight->type)->getCString()) + MONSTROATTR[monstro_fight->type][0][2];
			UserDefault::sharedUserDefault()->setIntegerForKey(String::createWithFormat("monstro%d_money", monstro_fight->type)->getCString(), monstro_money);
			StartGameScene::chgMoney();
			monstro_fight->disappear();
			isMove = false;
		}
	}), NULL));
}

void GameScene::MonstroFight()
{
	this->runAction(Sequence::create(CallFunc::create([&](){fight(false); }), DelayTime::create(1.0f), CallFunc::create([&](){heroFight(); }), NULL));
	int monstro_atk = MONSTROATTR[monstro_fight->type][0][1];
	int beHint = monstro_atk - def;
	if (beHint < 1)
		beHint = 1;
	CCLOG("hero is heat by %d", beHint);
	StartGameScene::chgHPBar(beHint);
}

void GameScene::fight(bool isHero)
{
	CallFunc* callFunc;
	Sequence* beAct;
	Node* beatSprite;
	if (isHero)
	{
		auto* beat_anim = beatAnim(true);
		auto* beatSprite = hero->hero->getChildByTag(100);
		beatSprite->runAction(beat_anim);
		callFunc = CallFunc::create([&](){ hero->hero->removeChildByTag(100); });
		monstro_fight->runAction(Sequence::create(MoveBy::create(0.3f, Vec2(-cq_dirc[(dirc_now + 2) % 4][1], cq_dirc[(dirc_now + 2) % 4][0])), MoveBy::create(0.3f, Vec2(-cq_dirc[dirc_now][1], cq_dirc[dirc_now][0])), NULL));
	}
	else
	{
		auto* beat_anim = beatAnim(false);
		auto* beatSprite = monstro_fight->monstro->getChildByTag(100);
		beatSprite->runAction(beat_anim);
		callFunc = CallFunc::create([&](){ monstro_fight->monstro->removeChildByTag(100); });
		hero->runAction(Sequence::create(MoveBy::create(0.3f, Vec2(-cq_dirc[dirc_now][1], cq_dirc[dirc_now][0])), MoveBy::create(0.3f, Vec2(-cq_dirc[(dirc_now + 2) % 4][1], cq_dirc[(dirc_now + 2) % 4][0])), NULL));
	}
	this->runAction(Sequence::create(DelayTime::create(0.4f), callFunc, NULL));
}

Animate* GameScene::beatAnim(bool isHero)
{
	Vector<SpriteFrame*> frameArray;
	for (int i = 0; i < 6; i++)
	{
		auto* frame = beat_frame->getSpriteFrameByName(String::createWithFormat("hitAnim/beat%d.png", i)->getCString());
		frameArray.pushBack(frame);
	}
	Animation* anim = Animation::createWithSpriteFrames(frameArray);
	anim->setDelayPerUnit(0.05f);
	auto* animAct = Animate::create(anim);
	auto* beatSprite = Sprite::create("beat0.png");
	beatSprite->setTag(100);
	if (isHero)
	{
		beatSprite->setPosition(5 + cq_dirc[dirc_now][1] * 12, 20 - cq_dirc[dirc_now][0] * 10);
		beatSprite->setRotation(dirc_now * 90 - 90);
		hero->hero->addChild(beatSprite);
	}
	else
	{
		beatSprite->setPosition(5 + cq_dirc[(dirc_now + 2) % 4][1] * 12, 20 - cq_dirc[(dirc_now + 2) % 4][0] * 10);
		beatSprite->setRotation(dirc_now * 90 + 90);
		monstro_fight->monstro->addChild(beatSprite);
	}
	return animAct;
}

bool GameScene::IsCreateSk3(int x, int y)
{
	if ((maze[y][x] == 1) && (x > 12) && (x < (MAPSIZE - 2)) && (y > 12) && (y < (MAPSIZE - 2)))
	{
		maze[y][x] = 200;
		return true;
	}
	else
		return false;
}