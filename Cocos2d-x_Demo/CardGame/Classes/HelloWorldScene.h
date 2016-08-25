#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Pocker.h"
#include "Player.h"
class HelloWorld : public cocos2d::Layer
{
public:
	int rule;
	int id;
	int delay;
	int pockerNumber[54];
	Pocker* pocker[54];
	Player* player[2];
	void initPocker();				// 初始化纸牌序列
	void wanjiaChupai();
	void diannaoChupai();
	void playerChupai(int type);
	void pockerNumSort(int low, int high);		// 纸牌排序
	void testSort(int low, int high);			// 测试纸牌排序的结果	
	void preporePocker(Point position);			// 将纸牌准备好
	void startDeal();
	void chupai(Object* pSender);
	void dealUpdate(float dt);
	virtual void update(float dt);
	static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
