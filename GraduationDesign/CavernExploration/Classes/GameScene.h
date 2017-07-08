#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "NewMap.h"
#include "MapItem.h"
#include "Hero.h"
#include "Monstro.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	
	Hero* hero;
	Monstro* monstro[20];
	int monstro_num;
	NewMap* map;
	MapItem* mapItem;
	int maze[MAPSIZE + 2][MAPSIZE + 2];
	
	//--Action
	int x;
	int y;
	int dirc_now;
	bool isMove;
	bool isCanMove;

	//--Fight
	Monstro* monstro_fight;
	SpriteFrameCache* beat_frame;
	Animate* beat_anim;
	String* monstro_info;

	//--Info
	int hp;		//生命值
	int atk;	//攻击力
	int def;	//护盾
	int crp;	//暴击率
	int crt;	//暴击倍数

	static GameScene* createGameScene();
	virtual bool init();
	void gameInit();
	void addWall();
	bool IsCreateMonstro(int monstro_num, int x, int y);
	bool IsCreateSk3(int x, int y);

	//--ActionFunc
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	void heroMove(float dx, float dy);
	void chgMove();
	void bgMoveTo(int dirc);
	bool cqSkill();

	//--InfoFunc
	void showHeroInfo();

	//--FightFunc
	void heroFight();
	void MonstroFight();
	void fight(bool isHero);
	Animate* beatAnim(bool isHero);
	void addBeatAnim(Animate* anim);
	void removeBeatAnim();
	
	CREATE_FUNC(GameScene);
};


#endif