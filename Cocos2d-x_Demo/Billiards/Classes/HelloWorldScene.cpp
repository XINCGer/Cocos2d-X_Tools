#include "HelloWorldScene.h"
#define SQRT_3 1.7321
#define PTM_RATIO 64
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
	Point ballPos[7] = { Vec2(180,100),
						Vec2(180,450),
						Vec2(180 - 20, 450 + 20*SQRT_3 ),
						Vec2(180 + 20, 450 + 20 * SQRT_3 ),
						Vec2(180 - 40, 450 + 40*SQRT_3 ),
						Vec2(180, 450 + 40*SQRT_3 ),
						Vec2(180 + 40, 450 + 40 * SQRT_3) };
	for (int i = 0; i < 7; i++)
	{
		ball[i] = Sprite::create(String::createWithFormat("ball%d.png", i )->getCString());
		ball[i]->setPosition(ballPos[i]);
		addChild(ball[i]);
	}

	// 创建世界，桌球为平面，没有重力
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	// 刚体
	b2Body *groundBody = _world->CreateBody(&groundBodyDef);
	groundBody->SetType(b2_staticBody);
	// 形状
	b2EdgeShape groundBox;
	// 夹具
	b2FixtureDef boxShapeDef;
	// 为夹具加入形状
	groundBox.Set(b2Vec2(0, 0), b2Vec2(360 / PTM_RATIO, 0));
	groundBody->CreateFixture(&groundBox, 0);
	groundBox.Set(b2Vec2(0, 640 / PTM_RATIO), b2Vec2(360 / PTM_RATIO, 640 / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);
	groundBox.Set(b2Vec2(0, 0), b2Vec2(0, 640 / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);
	groundBox.Set(b2Vec2(360 / PTM_RATIO, 0), b2Vec2(360 / PTM_RATIO, 640 / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);
	boxShapeDef.shape = &groundBox;
	// 加进去七个球
	for (int i = 0; i < 7; i++)
	{
		b2BodyDef ballBodyDef;
		ballBodyDef.type = b2_dynamicBody;
		ballBodyDef.position.Set(ballPos[i].x / PTM_RATIO, ballPos[i].y / PTM_RATIO);
		ballBodyDef.userData = ball[i];
		b2CircleShape circle;
		circle.m_radius = 20.0 / PTM_RATIO;
		_body[i] = _world->CreateBody(&ballBodyDef);
		b2FixtureDef ballShapeDef;
		ballShapeDef.shape = &circle;
		ballShapeDef.density = 1.0f;
		ballShapeDef.friction = 0.5;
		ballShapeDef.restitution = 0.8f;
		_body[i]->CreateFixture(&ballShapeDef);
	}
	auto* dispatcher = Director::getInstance()->getEventDispatcher();
	auto* listener = EventListenerTouchOneByOne::create();
	// 绑定监听事件
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();
    return true;
}
void HelloWorld::update(float dt)
{
	int velocityIterations = 8;
	int positionIterations = 1;
	_world->Step(0.2f, velocityIterations, positionIterations);
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			Sprite *sprite = (CCSprite *)b->GetUserData();
			if (sprite != NULL)
			{
				b2Vec2 bodyPos = b->GetPosition();	// 获取小球对象
				Point pos = ccp(bodyPos.x*PTM_RATIO, bodyPos.y*PTM_RATIO);	// 将小球的坐标转换为box2d的坐标
				float rotation = -1 * CC_RADIANS_TO_DEGREES(b->GetAngle());	//转换角度
				sprite->setPosition(pos);		//设置精灵坐标
				sprite->setRotation(rotation);	//设置精灵角度
			}
		}
	}
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	prePos = touch->getLocation();
	return true;
}
void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	auto position = touch->getLocation();
	float dx = (position.x - prePos.x) / 16;
	float dy = (position.y - prePos.y) / 16;
	b2Vec2 v = _body[0]->GetLinearVelocity();
	v.x += dx;
	v.y += dy;
	_body[0]->SetLinearVelocity(v);
}
