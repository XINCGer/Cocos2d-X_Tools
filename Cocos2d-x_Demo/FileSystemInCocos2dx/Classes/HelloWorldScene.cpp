#include "HelloWorldScene.h"

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
	// 创建一个菜单按钮，用于读取文件中的内容
	auto* background = LayerColor::create(Color4B(255, 255, 255, 255));
	addChild(background);
	auto* readLabel = Label::create("read", "Arial", 56);
	readLabel->setColor(Color3B(0, 0, 0));
	auto* pReadLabel = MenuItemLabel::create(readLabel, this, menu_selector(HelloWorld::readCallback));
	auto* buttonReadLabel = Menu::create(pReadLabel, NULL);
	buttonReadLabel->setPosition(320, 260);
	addChild(buttonReadLabel);
	auto* saveLabel = Label::create("save", "Arial", 56);
	saveLabel->setColor(Color3B(0, 0, 0));
	auto* pSaveLabel = MenuItemLabel::create(saveLabel, this, menu_selector(HelloWorld::saveCallback));
	auto* buttonSaveLabel = Menu::create(pSaveLabel, NULL);
	buttonSaveLabel->setPosition(320, 100);
	addChild(buttonSaveLabel);
    return true;
}
void HelloWorld::readCallback(Ref* pSender)
{
	CCLOG("============================================================");
	std::string path = FileUtils::sharedFileUtils()->getWritablePath()+"test.txt";
	// 输出文件路径
	CCLOG("path = %s", path.c_str());
	// 创建一个文件指针
	FILE* file = fopen(path.c_str(), "r");
	if (file) {
		char* buf;  //要获取的字符串  
		int len;    //获取的长度  
		// 获取文件长度长度
		fseek(file, 0, SEEK_END);   //移到尾部  
		len = ftell(file);          //提取长度  
		rewind(file);               //回归原位  
		CCLOG("count the file content len = %d", len);
		//分配buf空间  
		buf = (char*)malloc(sizeof(char) * len + 1);
		if (!buf) 
		{
			CCLOG("malloc space is not enough.");
		} 
		//读取进的buf，单位大小，长度，文件指针  
		int rLen = fread(buf, sizeof(char), len, file);
		buf[rLen] = '\0';
		CCLOG("has read Length = %d", rLen);
		CCLOG("has read content = %s", buf);
		fclose(file);
		free(buf);
	}
	else
	{
		CCLOG("open file error.");
	}
	CCLOG("============================================================");
}
void HelloWorld::saveCallback(Ref* pSender)
{
	CCLOG("============================================================");
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "test.txt";
	FILE* file = fopen(path.c_str(), "w");
	if (file) 
	{
		char* pContent = "this is a word";
		fputs(pContent, file);
		CCLOG("save file succeed.");
		fclose(file);
	}
	else
	{
		CCLOG("save file error.");
	}
	CCLOG("============================================================");
}
