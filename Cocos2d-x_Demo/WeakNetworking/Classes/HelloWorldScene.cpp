#include "HelloWorldScene.h"
#include "curl\include\win32\curl\curl.h"
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
	curl_global_init(CURL_GLOBAL_ALL);
	CURL* curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.hao123.com/");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, info_output);
	CURLcode success = curl_easy_perform(curl);
	curl_global_cleanup();
    return true;
}
size_t HelloWorld::info_output(void* buffer, size_t size, size_t nmemb, void *userp)
{
	CCLOG("============================================================");
	CCLOG("%s", buffer);
	CCLOG("============================================================");
	return 0;
}

/*
	//GET方式
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.xxx.com/article.php?id=123&type=5");
	//POST方式
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.xx.com/article.php");
	curl_easy_setopt(curl, CURLOPT_POST, true);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "ad=123&type=5");
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
*/
