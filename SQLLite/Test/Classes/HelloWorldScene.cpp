#include "HelloWorldScene.h"
#include "sqlite3.h"
USING_NS_CC;
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	auto* background = LayerColor::create(Color4B(255, 255, 255, 255));
	addChild(background);
	///////////////////////////////////////////////////////////////////
	createDatabase("save");
	return true;
}

/**
 * 创建数据库
 */
sqlite3* HelloWorld::createDatabase(const std::string dbName)
{
	sqlite3 *pdb = NULL;
	std::string path = FileUtils::getInstance()->getWritablePath()+dbName+".db";
	log(path.c_str());;
	std::string sql;
	int result;
	result = sqlite3_open(path.c_str(),&pdb);
	if (result != SQLITE_OK)
	{
		log("Open DataBase Failed!,Error Number:" + result);
		exit(-1);
	}
	return pdb;
}

/*
 * 创建表
 */
void HelloWorld::createTable(const std::string sql,const std::string path)
{
	std::string sql = "create table student(ID integer primary key autoincrement,name text,sex text)";
}



