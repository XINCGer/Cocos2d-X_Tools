#include  "AnimationUtils.h"
USING_NS_CC;


Animate* AnimationUtils::createAnimate(const char* actionName, const std::string plistName, const std::string textureName, int loopTime = -1, float deltaTime = 0.1f, const int lowBound = 0, const int upBound = 0)
{
	auto * frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(plistName, textureName);
	Vector<SpriteFrame *> frameArray;
	for (int i = lowBound; i <= upBound; i++)
	{
		auto* spriteFrame = frameCache->getSpriteFrameByName(String::createWithFormat("%s%d.png", actionName, i)->getCString());
		frameArray.pushBack(spriteFrame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(loopTime);
	animation->setDelayPerUnit(deltaTime);

	return Animate::create(animation);
}
