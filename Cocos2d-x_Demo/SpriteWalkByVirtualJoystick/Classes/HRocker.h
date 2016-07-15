#ifndef __HROCKER_H__
#define __HROCKER_H__
#include "cocos2d.h"  
using namespace cocos2d;
enum hero_direction
{
	RIGHT_DOWN = 1,
	LEFT_DOWN = 2,
	LEFT_UP = 3,
	RIGHT_UP = 4,
	DOWN = 5,
	LEFT = 6,
	UP = 7,
	RIGHT = 8
};
#define PI 3.1415926
//枚举型：用于标识摇杆与摇杆的背景  
typedef enum{
	tag_rocker,
	tag_rockerBG,
}tagForHRocker;
class HRocker : public Layer
{
public:
	float dx;
	float dy;
	int direction;
	//是否可操作摇杆  
	bool isCanMove;
	//创建摇杆，摇杆图片，摇杆背景图片，起始坐标  
	static HRocker* createHRocker(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//启动摇杆  
	void startRocker(bool _isStopOther);
	//停止摇杆  
	void stopRocker();
private:
	EventListenerTouchOneByOne* listener;
	void rockerInit(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//得到半径为r的圆周运动上一个角度应对应的x,y坐标  
	Point getAnglePosition(float r, float angle);
	//得到摇杆与用户触屏点的角度  
	float getRad(Point pos1, Point pos2);
	//摇杆背景的坐标  
	Point rockerBGPosition;
	//摇杆背景的半径  
	float rockerBGR;
	//触屏事件  
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	CREATE_FUNC(HRocker);
};

#endif  