#include "HelloWorldScene.h"
#include "json\writer.h"
#include "json\reader.h"
#include "json\value.h"

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

    writeJson();
    return true;
}

void HelloWorld::readJson()
{
    Json::Reader reader;
    Json::Value root;

    std::string data = FileUtils::getInstance()->getStringFromFile("test1.json");

    if (reader.parse(data, root, false) == true)
    {
        log("id=%d", root["id"].asInt());
        log("name=%s", root["name"].asCString());
        log("IQ=%f", root["IQ"].asDouble());
    }
}

void HelloWorld::readChildJson()
{
    Json::Reader reader;
    Json::Value root;

    std::string data = FileUtils::getInstance()->getStringFromFile("test2.json");

    if (reader.parse(data, root, false) == true)
    {
        log("id=%d", root["id"].asInt());
        log("name=%s", root["name"].asCString());
        log("IQ=%f", root["IQ"].asDouble());

        log("msg value money=%d", root["msg"]["money"].asInt());
        log("msg value say=%s", root["msg"]["say"].asCString());
    }
}

void HelloWorld::readArrayJson()
{
    Json::Reader reader;
    Json::Value root;

    std::string data = FileUtils::getInstance()->getStringFromFile("test3.json");

    if (reader.parse(data, root, false) == true)
    {
        int iNum = root.size();
        for (int i = 0; i < iNum; i++)
        {
            log("id=%d", root[i]["id"].asInt());
            log("model=%s", root[i]["model"].asCString());
            log("atk=%d", root[i]["atk"].asInt());
        }
    }
}

void HelloWorld::writeJson()
{

    Json::Value root;
    Json::FastWriter writer;

    root["name"] = "Who";
    root["IQ"] = 999;

    std::string json_file = writer.write(root);

    FILE* file = fopen("testWirte.json", "w");
    fprintf(file, json_file.c_str());
    fclose(file);
}
