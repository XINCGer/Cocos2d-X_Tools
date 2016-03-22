#include "HelloWorldScene.h"
#include "tinyxml\tinyxml.h"

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
    if (!Layer::init())
    {
        return false;
    }
    //loadXmlTest1("test1.xml");
    loadXmlTest2("test2.xml");
    return true;
}

void HelloWorld::loadXmlTest1(const char* sPath) {
    TiXmlDocument* xmlDoc = new TiXmlDocument();

    /* 读取XML文件 */
    Data fileData = FileUtils::getInstance()->getDataFromFile(sPath);

    /* 开始解析XML */
    xmlDoc->Parse((const char*)fileData.getBytes());

    /* 获取XML根节点 */
    TiXmlElement* rootElement = xmlDoc->RootElement();

    /* 开始读取XML各个标签 */
    loadXmlEle(rootElement);

    /* 删除对象 */
    delete xmlDoc;
}

void HelloWorld::loadXmlEle(TiXmlElement* rootElement) {
    /* 取得根节点的第一个子标签对象 */
    TiXmlElement* cldElement = rootElement->FirstChildElement();

    /* 打印标签的名字和标签的id属性 */
    log("%s id=%s", cldElement->Value(), cldElement->Attribute("id"));

    /* 再取得标签的第一个子对象 */
    cldElement = cldElement->FirstChildElement();

    /* 打印标签的名字和标签的值 */
    log("%s:%s", cldElement->Value(), cldElement->GetText());
}

void HelloWorld::loadXmlTest2(const char* sPath) {
    TiXmlDocument* xmlDoc = new TiXmlDocument();

    /* 读取XML文件 */
    Data fileData = FileUtils::getInstance()->getDataFromFile(sPath);

    /* 开始解析XML */
    xmlDoc->Parse((const char*)fileData.getBytes());

    /* 获取XML根节点 */
    TiXmlElement* rootElement = xmlDoc->RootElement();

    /* 开始读取XML各个标签 */
    loadXmlEleMMWin(rootElement);

    /* 删除对象 */
    delete xmlDoc;
}

void HelloWorld::loadXmlEleMMWin(TiXmlElement* rootElement) {
    TiXmlElement* cldElement = rootElement->FirstChildElement();

    while (cldElement != NULL) {
        /* 某些节点的内容为空，所以不获取它的内容（但是可能有子节点） */
        if (cldElement->GetText() != NULL) {
            log("%s:%s", cldElement->Value(), cldElement->GetText());
        }
        /* 如果有子节点，则继续解析，并且添加到当前节点的子节点列表 */
        else if (cldElement->FirstChildElement() != NULL) {
            loadXmlEleMMWin(cldElement);
        }

        /* 下一个同级节点 */
        cldElement = cldElement->NextSiblingElement();
    }
}