#ifndef  _ANIMATIONUTILS_
#define  _ANIMATIONUTILS_
#include "cocos2d.h"
USING_NS_CC;


class AnimationUtils
{
public:
	static cocos2d::Animate *createAnimate(const char* actionName, const std::string plistName, const std::string textureName, int loopTime, float deltaTime, const int lowBound, const int upBound);
};
#endif
