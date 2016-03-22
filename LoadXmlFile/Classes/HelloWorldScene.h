#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class TiXmlElement;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(HelloWorld);

private:
    void loadXmlTest1(const char* sPath);           // XML读取测试1，Hello TinyXML
    void loadXmlEle(TiXmlElement* rootElement);     //读取普通的XML配置文件

    
    void loadXmlTest2(const char* sPath);           // XML读取测试2，读取MM控件的XML
    void loadXmlEleMMWin(TiXmlElement* rootElement);//读取MM控件的XML配置文件
};

#endif // __HELLOWORLD_SCENE_H__
