#include "HelloWorldScene.h"
#include "tinyxml2\tinyxml2.h"
USING_NS_CC;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	std::string filename = "test.xml";
	tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
	tinyxml2::XMLDeclaration *pDel = pDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	pDoc->LinkEndChild(pDel);
	//添加根节点xmlRoot
	tinyxml2::XMLElement *rootElement = pDoc->NewElement("xmlRoot");
	// 为节点设置属性
	rootElement->SetAttribute("version", "1.0");
	pDoc->LinkEndChild(rootElement);
	// 加入注释
	tinyxml2::XMLComment *commentElement = pDoc->NewComment("this is xml comment");
	// 将commentElement加入到节点中
	rootElement->LinkEndChild(commentElement);
	// 循环为节点element加入子节点
	for (int i = 0; i < 20; i++)
	{
		tinyxml2::XMLElement *myElement = pDoc->NewElement("node");
		myElement->SetAttribute("id", i);
		myElement->SetAttribute("type", "cocos2d");
		rootElement->LinkEndChild(myElement);
	}
	pDoc->SaveFile(filename.c_str());
	pDoc->Print();
	delete pDoc;
    return true;
}