/*
ProjectName: PopStar
Author: 马三小伙儿
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/16
*/
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
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	starX = 0;
	starY = 0;
	for (int i = 0; i < WIDTH*HEIGHT; i++)
	{
		holder[i] = -1;
	}
	auto* background = Sprite::create("background.png");
	background->setPosition(180, 320);
	addChild(background);
	addStar();

	listener = EventListenerTouchOneByOne::create();
	// 绑定监听事件
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	scheduleUpdate();
	return true;
}
void HelloWorld::addStar()
{
	srand(unsigned(time(0)));
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			star[x][y] = StarSprite::createStar(rand() % 5 + 1, x, 20);
			addChild(star[x][y]);
			srand(rand()*rand());
		}
	}
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	auto position = touch->getLocation();	// 获取用户点击坐标
	// 判断用户点击是否在“星星”的范围内
	if (position.x < 40 * WIDTH&&position.y < 40 * HEIGHT)
	{
		// 将坐标转换为对应在star数组中的索引
		int x = (int)position.x / 40;
		int y = (int)position.y / 40;
		if ( star[x][y]->type > 0 )
		{
			UDLRDelete(x, y);
			int i = 0;
			while (holder[i] != -1)
			{
				int x = holder[i] % HEIGHT;
				int y = (int)holder[i] / HEIGHT;
				UDLRDelete(x, y);
				i++;
			}
			popStar();
			starDrop();
			starTranslation();
			starMove(1.1f);
			if (isOver())
			{
				exit(-1);
			}
		}
	}
	return false;
}
void HelloWorld::UDLRDelete(int x, int y)
{
	// 依次计算对应点的上、下、左、右、相邻的星星
	int type = star[x][y]->type;
	if (type>0)
	{
		//addToHolder(x, y);
		bool isadd=false;
		if (y + 1 < HEIGHT&&star[x][y + 1]->type == type)
		{	// 上
			addToHolder(x, y + 1);
			isadd = true;
		}
		if (y > 0 && star[x][y - 1]->type == type)
		{	// 下
			addToHolder(x, y - 1);
			isadd = true;
		}
		if (x > 0&&star[x - 1][y]->type == type)
		{
			// 左
			addToHolder(x - 1, y);
			isadd = true;
		}
		if (x + 1 < WIDTH&&star[x + 1][y]->type == type)
		{
			// 右
			addToHolder(x + 1, y);
			isadd = true;
		}
		if (isadd)
		{
			addToHolder(x, y);
		}
	}
}
void HelloWorld::addToHolder(int x, int y)
{
	int i = 0;
	while (holder[i] != -1)
	{
		if ( holder[i] == y * HEIGHT + x )
		{
			break;
		}
		else
		{
			i++;
		}
	}
	holder[i] = y * HEIGHT + x;
}
void HelloWorld::cleanHolder()
{
	int i = 0;
	while (holder[i] != -1)
	{
		holder[i] = -1;
	}
}
void HelloWorld::popStar()
{
	if (holder[1] != -1)
	{
		int i = 0;
		while (holder[i] != -1)
		{
			int x = holder[i] % HEIGHT;
			int y = (int)holder[i] / HEIGHT;
			CCLOG("%d,%d,%d", i, x, y);
			star[x][y]->starDelete();
			i++;
		}
	}
	cleanHolder();
}
void HelloWorld::starDrop()
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 1; y < HEIGHT; y++)
		{
			// 遍历每一个非最底层的星星，看其下方是否存在空白
			for (int i = 0; i < y; i++)
			{
				if (star[x][i]->type == 0)
				{
					auto* temp = star[x][i];
					star[x][i] = star[x][y];
					star[x][y] = temp;
					break;
				}
			}
		}
	}
}
void HelloWorld::starMove(float dt)
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			star[x][y]->moveTo(dt, x, y);
		}
	}
}
void HelloWorld::starTranslation()
{
	for (int x = 1; x < WIDTH; x++)
	{
		for (int i = 0; i < x; i++)
		{
			if (star[i][0]->type == 0)
			{
				for (int y = 0; y < HEIGHT; y++)
				{
					auto* temp = star[x][y];
					star[x][y] = star[i][y];
					star[i][y] = temp;
				}
			}
		}
	}
}
bool HelloWorld::isOver()
{
	bool over = true;
	for (int x = 0; x < WIDTH; x++)
	{
		if (over)
		{
			for (int y = 0; y < HEIGHT; y++)
			{
				int type = star[x][y]->type;
				if (type > 0)
				{
					if (y + 1 < HEIGHT&&star[x][y + 1]->type == type)
					{	// 上
						over = false;
						break;
					}
					if (y > 0 && star[x][y - 1]->type == type)
					{	// 下
						over = false;
						break;
					}
					if (x > 0 && star[x - 1][y]->type == type)
					{
						// 左
						over = false;
						break;
					}
					if (x + 1 < WIDTH&&star[x + 1][y]->type == type)
					{
						// 右
						over = false;
						break;
					}
				}
			}
		}
		else
		{
			break;
		}
	}
	return over;
}
void HelloWorld::update(float dt)
{
	if (starX < WIDTH&&starY<HEIGHT)
	{
		star[starX][starY]->moveTo(0.6f, starX, starY);
		starX++;
	}
	else if (starY<HEIGHT)
	{
		starX = 0;
		starY++;
	}
	else
	{
		unscheduleUpdate();
	}
}