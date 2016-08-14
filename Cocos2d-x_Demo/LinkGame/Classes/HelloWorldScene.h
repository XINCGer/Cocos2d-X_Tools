#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"
#include "CountDownBar.h"
#define WIDTH 12
#define HEIGHT 9
#define SIZE 40
#define FULLTIME 1000
class HelloWorld : public cocos2d::Layer
{
public:
	int propNum;
	int score;
	bool timeOut;
	int time;
	Point temp;
	TMXLayer* recLayer;
	CardSprite* card[WIDTH][HEIGHT];
	CountDownBar* bar;
	cocos2d::Label* scoreLabel;
	cocos2d::Label* timeLabel;
	cocos2d::Label* propLabel;
	void initBoard();
	bool noCorner(int x1, int y1, int x2, int y2);
	bool oneCorner(int x1, int y1, int x2, int y2);
	bool twoCorner(int x1, int y1, int x2, int y2);
	bool isCanConnection(int x1, int y1, int x2, int y2);
	void prop(cocos2d::Object* pSender);
    static cocos2d::Scene* createScene();
    virtual bool init(); 
	virtual void update(float dt);
    void menuCloseCallback(cocos2d::Ref* pSender);
	virtual bool onTouchBegan(Touch *touch, Event *event);
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
