#ifndef _PLAYER_OBJECT_H_
#define _PLAYER_OBJECT_H_
#include "cocos2d.h"
#include "Pocker.h"
USING_NS_CC;
class Player :public Object
{
public:
	int count;								// 玩家手中的纸牌数目
	int t_count;
	Point m_pos;							// 纸牌初始位置
	Player(int type);						// 使用构造方法初始化玩家类
	void updatePocker();					// 更新玩家手中的纸牌
	int m_pocker[14];						// 保存玩家手中的纸牌
	int t_pocker[4];						// 保存玩家出了哪些牌
	int type;								// 定义玩家类型，0为玩家1为电脑
	int status;								// 标识玩家当前状态
	void addPocker(int id);					// 加入一张纸牌
	void removePocker(int id);		 		// 移除一张纸牌
	void addToHand(int id);					// 将一张纸牌那在手中
	void cleanHand();						// 清空手中的纸牌
};
#endif