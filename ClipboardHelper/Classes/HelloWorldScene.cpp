#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

//#if(CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
#include "platform/android/jni/JniHelper.h"
//#endif

USING_NS_CC;
using namespace cocos2d::ui;
//using namespace cocostudio::timeline;

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
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto textField = TextField::create();
	textField->setPosition(Point(visibleSize.width / 3, visibleSize.height / 2 + 50));
	//textField->setText("Input Some Content Here");


	auto buttonCopy = Button::create("button.png");
	buttonCopy->setTitleText("Copy");
	buttonCopy->setPosition(Point(visibleSize.width / 3 * 2, visibleSize.height / 2 + 50));
	buttonCopy->addTouchEventListener([textField](Ref *pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::ENDED == type) {

			JniMethodInfo jniMethodInfo;
			if (JniHelper::getStaticMethodInfo(jniMethodInfo, "org/cocos2dx/lib/Cocos2dxHelper", "copyToClipboard", "()V"))
			{
				jstring jname = jniMethodInfo.env->NewStringUTF(textField->getString());
				jniMethodInfo.env->CallStaticVoidMethod(jniMethodInfo.classID,jniMethodInfo.methodID,jname);
			}
		}
	});

	auto buttonPaste = Button::create("button.png");
	buttonPaste->setTitleText("Paste");
	buttonPaste->setPosition(Point(visibleSize.width / 3 * 2, visibleSize.height / 2 - 50));
	buttonPaste->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (Widget::TouchEventType::ENDED == type) {
			JniMethodInfo jniMethodInfo;
			if (JniHelper::getStaticMethodInfo(jniMethodInfo, "org/cocos2dx/lib/Cocos2dxHelper", "copyFromClipboard", "()V"))
			{
				jniMethodInfo.env->CallStaticStringMethod()
			}
		}
	});

	auto text = Text::create();
	text->setPosition(Point(visibleSize.width / 3, visibleSize.height / 2 - 50));

	auto colorLayer = LayerColor::create(Color4B(238, 187, 119, 255),visibleSize.width,visibleSize.height);
	colorLayer->setPosition(0,0);

	addChild(colorLayer);
	addChild(buttonCopy);
	addChild(buttonPaste);
	addChild(text);
	addChild(textField);

	return true;
}
