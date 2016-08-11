#ifndef __NINEPATCH_SCENE_H__
#define __NINEPATCH_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
class NinePatch : public Layer
{
public:
	static NinePatch* createPatch(int width, int height, int borderSize, Point position);
	void initPatch(int width, int height, int borderSize, Point position);
	CREATE_FUNC(NinePatch);
};
#endif