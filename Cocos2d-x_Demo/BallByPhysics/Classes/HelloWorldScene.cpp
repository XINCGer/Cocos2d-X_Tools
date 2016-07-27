#include "HelloWorldScene.h"
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
	ball = Sprite::create("ball.png");
	ball->setPosition(320, 300);
	addChild(ball);
	b2Vec2 gravity;					// 创建重力
	gravity.Set(0.0f, -2.0f);	// 定义重力参数
	world = new b2World(gravity);		// 生成世界对象
	world->SetAllowSleeping(true);			//允许休眠
	world->SetContinuousPhysics(true);		//设置检测连续碰撞
	b2BodyDef groundBodyDef;		// 定义刚体
	groundBodyDef.position.Set(0, 0);	// 设置左下角为坐标原点
	//根据钢体的描述创建钢体对象
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	groundBody->SetType(b2_staticBody);
	b2EdgeShape groundBox;		//定义地面盒形状
	//2个点确定一条线，以下分别设置了屏幕的4个边
	groundBox.Set(b2Vec2(0, 0), b2Vec2(640, 0));
	groundBody->CreateFixture(&groundBox, 0);
	groundBox.Set(b2Vec2(0, 360), b2Vec2(640, 360));
	groundBody->CreateFixture(&groundBox, 0);
	groundBox.Set(b2Vec2(0,360), b2Vec2(0, 0));
	groundBody->CreateFixture(&groundBox, 0);
	groundBox.Set(b2Vec2(640, 360), b2Vec2(640, 0));
	groundBody->CreateFixture(&groundBox, 0);
	b2BodyDef bodyDef;				// 定义动态刚体
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(320, 300);
	b2Body *ballbody = world->CreateBody(&bodyDef);
	ballbody->SetUserData(ball);
	ballbody->SetActive(true);
	//给这个动态钢体创建盒子形状
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 0.5f);
	b2FixtureDef fixtureDef;			//为该钢体定义夹具
	fixtureDef.shape = &dynamicBox;		//绑定物体的形状
	fixtureDef.density = 0.2f;			//密度
	fixtureDef.restitution = 0.9f;		//弹性系数
	fixtureDef.friction = 0.1f;			//摩擦力
	ballbody->CreateFixture(&fixtureDef);	//在刚体的夹具工厂中创建夹具
	this->scheduleUpdate();
    return true;
}
void HelloWorld::update(float dt)
{
	int velocityIterations = 8;
	int positionIterations = 1;
	//时间定义成固定的，如果用dt的话，会随着帧率的变化而变化
	world->Step(0.2f, velocityIterations, positionIterations);
	//枚举世界中的所有物体，找出有userdata的物体，强制转化为精灵
	for (b2Body *b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			Sprite *sprite = (CCSprite *)b->GetUserData();
			if (sprite != NULL)
			{
				b2Vec2 bodyPos = b->GetPosition();	// 获取小球对象
				Point pos = ccp(bodyPos.x, bodyPos.y);	// 将小球的坐标转换为box2d的坐标
				float32 rotation = -1 * CC_RADIANS_TO_DEGREES(b->GetAngle());		//转换角度
				sprite->setPosition(pos);		//设置精灵坐标
				sprite->setRotation(rotation);	//设置精灵角度
			}
		}
	}
}
