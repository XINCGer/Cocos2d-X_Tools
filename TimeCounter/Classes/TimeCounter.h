#ifndef TimeCounter_H
#define TimeCounter_H

#include "cocos2d.h"
USING_NS_CC;

class TimeCounter : public Node
{
public:
    CREATE_FUNC(TimeCounter);
    virtual bool init();

    virtual void update(float dt);

    void start();           /* 开始计时 */
    float getfCurTime();    /* 获取当前时间 */

private:
    float m_fTime;
};

#endif