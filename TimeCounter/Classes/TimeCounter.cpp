#include "TimeCounter.h"

bool TimeCounter::init()
{
    return true;
}

void TimeCounter::update(float dt)
{
    m_fTime += dt;
}

float TimeCounter::getfCurTime()
{
    return m_fTime;
}

void TimeCounter::start()
{
    m_fTime = 0;

    this->scheduleUpdate();
}

