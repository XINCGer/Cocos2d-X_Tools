#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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
    if ( !Layer::init() )
    {
        return false;
    }
    
	auto *m_emitter = new ParticleSystemQuad();
	m_emitter->initWithTotalParticles(900);//900个粒子对象
	m_emitter->setTexture(TextureCache::sharedTextureCache()->addImage("snow1.png"));
	//设置发射粒子的持续时间-1表示一直发射，0没有意义，其他值表示持续时间
	m_emitter->setDuration(-1);
	//设置中心方向,这个店是相对发射点，x正方向为右，y正方向为上
	m_emitter->setGravity(Point(0, -40));
	//设置角度，角度的变化率
	m_emitter->setAngle(0);
	m_emitter->setAngleVar(360);
	//设置径向加速度，径向加速度的变化率
	m_emitter->setRadialAccel(50);
	m_emitter->setRadialAccelVar(0);
	//设置粒子的切向加速度，切向加速度的变化率
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);
	//设置粒子的位置，位置的变化率
	m_emitter->setPosition(Point(640,360));
	m_emitter->setPosVar(Point(640, 0));
	//设置粒子声明，生命的变化率
	m_emitter->setLife(4);
	m_emitter->setLifeVar(2);
	//设置粒子开始的自旋转速度，开始自旋转速度的变化率
	m_emitter->setStartSpin(90);
	m_emitter->setStartSpinVar(120);
	//设置结束的时候的自旋转以及自旋转的变化率
	m_emitter->setEndSpin(90);
	m_emitter->setEndSpinVar(160);
	ccColor4F cc;
	cc.a = 1.0f;
	cc.b = 255.0f;
	cc.g = 255.0f;
	cc.r = 255.0f;
	ccColor4F cc2;
	cc2.a = 0;
	cc2.b = 0;
	cc2.g = 0;
	cc2.r = 0;
	//设置开始的时候的颜色以及颜色的变化率
	m_emitter->setStartColor(cc);
	m_emitter->setStartColorVar(cc2);
	//设置结束的时候的颜色以及颜色的变化率
	m_emitter->setEndColor(cc);
	m_emitter->setEndColorVar(cc2);
	//设置开始时候粒子的大小，以及大小的变化率
	m_emitter->setStartSize(30);
	m_emitter->setStartSizeVar(0);
	//设置粒子结束的时候的大小，以及大小的变化率
	m_emitter->setEndSize(20.0f);
	m_emitter->setEndSizeVar(0);
	//设置每秒钟产生粒子的数目
	m_emitter->setEmissionRate(100);
	addChild(m_emitter);

    return true;
}
