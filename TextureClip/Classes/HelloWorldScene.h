#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	//创建一个ClipNode的工具方法，参数:底图路径,遮罩路径,裁剪的模式,alpah阈值
	static cocos2d::ClippingNode* createTextureClip(const std::string& imagePath, const std::string& maskPath, const bool inverted, const float alphaThreshold);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
