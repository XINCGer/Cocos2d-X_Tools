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
	if (!Layer::init())
	{
		return false;
	}
	curl_global_init(CURL_GLOBAL_ALL);	//对CURL的全局变量进行初始化
	CURL* curl = curl_easy_init();
	//首先使用GET方法发送数据
	curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/Test/test.php?username=admin&password=123456");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, info_output_get);		//设置回调函数用以处理获取到的信息
	CURLcode success = curl_easy_perform(curl);		//返回HTTP请求的状态
	//然后使用POST方法发送数据
	curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/Test/test.php");
	curl_easy_setopt(curl, CURLOPT_POST, true);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "username=admin&password=123456");
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, info_output_post);		//设置回调函数用以处理获取到的信息
	success = curl_easy_perform(curl);		//返回HTTP请求的状态
	curl_global_cleanup();			//清除CURL全局变量
	return true;
}
size_t HelloWorld::info_output_get(void* buffer, size_t size, size_t nmemb, void *userp)
{
	CCLOG("===========================GET METHOD============================");
	CCLOG("%s", buffer);
	CCLOG("============================================================");
	return 0;
}


size_t HelloWorld::info_output_post(void* buffer, size_t size, size_t nmemb, void *userp)
{
	CCLOG("============================POST METHOD=========================");
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
