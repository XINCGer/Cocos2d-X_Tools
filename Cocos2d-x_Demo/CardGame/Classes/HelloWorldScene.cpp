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
    if ( !Layer::init() )
    {
        return false;
    }
	rule = 0;
	id = 0;
	auto* background = Sprite::create("background.png");
	background->setPosition(320, 180);
	addChild(background);

	player[0] = new Player(0);
	player[1] = new Player(1);

	this->preporePocker(Vec2(30,180));
	startDeal();
    return true;
}
void HelloWorld::initPocker()
{
	// 对纸牌序列按数字顺序进行初始化
	for (int i = 0; i < 54; i++)
	{
		pockerNumber[i] = i;
	}
	// 按照顺序从最开始 随机将纸牌交换以得到一组随机的纸牌数字序列
	// 使用当前时间生成随机数种子
	srand(unsigned(time(0)));
	for (int i = 0; i < 54; i++)
	{
		// 生成一个从0到53的随机数
		int num = (rand()*rand()) % 54;
		// 将两个元素互相交换
		int temp = pockerNumber[i];
		pockerNumber[i] = pockerNumber[num];
		pockerNumber[num] = temp;
		CCLOG("pock[%d]=%d", i, pockerNumber[i]);
		// 重新定义种子
		srand(rand());
	}
	//pockerNumSort(0, 54);
}
void HelloWorld::pockerNumSort(int low, int high)
{
	for (int i = low; i < high; i++)
	{
		// 外层循环
		for (int j = low; j < high; j++)
		{
			if (pockerNumber[j] < 52 && pockerNumber[j + 1] < 52)
			{
				// 两个都是王，正常进行比较
				int num1 = pockerNumber[j] % 13;
				int num2 = pockerNumber[j + 1] % 13;
				// 先比较牌的数值
				if (num1 > num2)
				{
					int t = pockerNumber[j];
					pockerNumber[j] = pockerNumber[j + 1];
					pockerNumber[j + 1] = t;
				}
				else if (num1 == num2)
				{
					// 如果数值相同再比较花色
					int type1 = pockerNumber[j] / 13;
					int type2 = pockerNumber[j + 1] / 13;
					if (type1 > type2)
					{
						int t = pockerNumber[j];
						pockerNumber[j] = pockerNumber[j + 1];
						pockerNumber[j + 1] = t;
					}
				}
			}
			if (pockerNumber[j] > 51 && pockerNumber[j + 1] > 51)
			{
				// 两张牌分别是大小王，故直接对两张牌进行赋值即可
				pockerNumber[j] = 52;
				pockerNumber[j + 1] = 53;
			}
			else
			{
				// 一张是王，一张是普通牌
				if (pockerNumber[j] > 51)
				{
					// 此时需要交换顺序
					int t = pockerNumber[j];
					pockerNumber[j] = pockerNumber[j + 1];
					pockerNumber[j + 1] = t;
				}
				// 由于正常纸牌的面值一定比大小王要小，故当pockerNumber[j+1]>51时不需要交换顺序
			}
		}
	}
	testSort(0, 54);
}
void HelloWorld::testSort(int low, int high)
{
	for (int i = low; i < high; i++)
	{
		int pocker = pockerNumber[i];
		int num = pocker % 13;
		int type = pocker / 13;
		CCLOG("the pocker[%d] is %d, the number is %d and type is %d", i, pocker, num, type);
	}
}
void HelloWorld::preporePocker(Point position)
{
	initPocker();
	pockerNumSort(0, 13);
	pockerNumSort(14, 27);
	for (int i = 0; i < 28; i++)
	{
		pocker[i] = Pocker::createPocker(pockerNumber[i], Vec2(position.x + 12 * i, position.y), false);
		int tag = pocker[i]->number;
		pocker[i]->setTag(tag);
		addChild(pocker[i]);
	}
}
void HelloWorld::startDeal()
{
	// 创建定时器
	schedule(schedule_selector(HelloWorld::dealUpdate), 0.2f);
}
void HelloWorld::dealUpdate(float dt)
{
	// id取值为0~13时给玩家发牌
	if (id < 14)
	{
		pocker[27 - id]->moveTo(Vec2(35 + 44 * id, 45), 0.2f);
		pocker[27 - id]->showFont();				// 显示正面
		player[0]->addPocker(27 - id);
		id++;
	}
	else if (id < 28)
	{	// 给“电脑”发牌
		pocker[27 - id]->moveTo(Vec2(35 + 44 * (id - 14), 315), 0.2f);
		player[1]->addPocker(27 - id);
		id++;
	}
	else
	{
		// 当id取值大于等于28时，说明发牌完成则取消定时器
		unschedule(schedule_selector(HelloWorld::dealUpdate));
		// 加入两个菜单按钮
		auto* pButton1 = MenuItemImage::create("fangqi1.png",
			"fangqi2.png",
			this,
			menu_selector(HelloWorld::chupai));
		auto* button1 = Menu::create(pButton1, NULL);
		button1->setPosition(250, 120);
		addChild(button1);
		auto* pButton2 = MenuItemImage::create("chupai1.png",
			"chupai2.png",
			this,
			menu_selector(HelloWorld::chupai));
		auto* button2 = Menu::create(pButton2, NULL);
		button2->setPosition(390, 120);
		addChild(button2);

		delay = 30;
		scheduleUpdate();
		player[0]->status = 1;
	}
}
void HelloWorld::chupai(Object* pSender)
{
	/**
	//diannaoChupai();
	用于对Player类中的方法进行测试
	for (int i = 0; i < 14; i++)
	{
		int id = player[0]->m_pocker[i];	// 获取纸牌的索引
		if (id != -1)
		{
			int number = pocker[id]->number;
			int value = number % 13;
			int type = number / 13;
			CCLOG("this is the %dth pocker,the value is %d and the type is %d...", i + 1, value, type);
		}
	}
	CCLOG("===================="); // 这是一条华丽的分割线
	for (int i = 0; i < 14; i++)
	{
		int id = player[0]->m_pocker[i];	// 获取纸牌的索引
		if (pocker[id]->isSelected)
		{
			// 如果纸牌被选中，则移除
			player[0]->removePocker(id);
		}
		if (player[0]->m_pocker[i] != -1)
		{
			int number = pocker[id]->number;
			int value = number % 13;
			int type = number / 13;
			CCLOG("this is the %dth pocker,the value is %d and the type is %d...", i + 1, value, type);
		}
	}
	CCLOG("===================="); // 这是一条华丽的分割线
	player[0]->updatePocker();
	for (int i = 0; i < 14; i++)
	{
		int id = player[0]->m_pocker[i];	// 获取纸牌的索引
		if (id != -1)
		{
			int number = pocker[id]->number;
			int value = number % 13;
			int type = number / 13;
			CCLOG("this is the %dth pocker,the value is %d and the type is %d...", i + 1, value, type);
		}
	}
	**/
	/**没有规则判断的玩家出牌
	//当status的值为1时，表示可以出牌
	if (player[0]->status == 1&& delay==0)
	{
		playerChupai(0);
		// 轮到电脑出牌，则
		if (player[0]->status == 0)
		{
			// 如果status被修改为0，说明发生了修改则说明可以换电脑出牌
			player[1]->status = 1;
			delay = 200;
		}
	}
	**/
	bool isChupai = false;
	// 先判断是否允许玩家出牌
	if (player[0]->status == 1 && delay == 0)
	{
		// 再判断当前的规则rule，如果rule=0则表示电脑放弃出牌
		if (rule==0)
		{
			// 可任意出牌
			isChupai = true;
		}
		else if (rule == 1)
		{
			// 需要按照电脑之前出牌的顺序出牌，首先明确电脑出了几张牌
			int count = player[1]->t_count;
			if (player[0]->t_count == count)
			{
				// 首先确认数目是相同的，再确定值是否相同
				if (count == 1)
				{
					// 只出一张牌
					int number0 = pocker[player[1]->t_pocker[0]]->number;
					int number1 = pocker[player[0]->t_pocker[0]]->number;
					if (number0 % 13 < number1 % 13 || number1 > 51)
					{
						isChupai = true;
					}
				}
				else if (count == 2)
				{
					int number0 = pocker[player[1]->t_pocker[0]]->number;
					int number1 = pocker[player[0]->t_pocker[0]]->number;
					int number2 = pocker[player[0]->t_pocker[1]]->number;
					if (number1 % 13 == number2 % 13 && number1 % 13 > number0 % 13)
					{
						isChupai = true;
					}
				}
				else if (count == 3)
				{
					int number0 = pocker[player[1]->t_pocker[0]]->number;
					int number1 = pocker[player[0]->t_pocker[0]]->number;
					int number2 = pocker[player[0]->t_pocker[1]]->number;
					int number3 = pocker[player[0]->t_pocker[2]]->number;
					if (number1 % 13 == number2 % 13 && number3 % 13 == number2 % 13 && number1 % 13 > number0 % 13)
					{
						isChupai = true;
					}
				}
				else if (count == 4)
				{
					int number0 = pocker[player[1]->t_pocker[0]]->number;
					int number1 = pocker[player[0]->t_pocker[0]]->number;
					int number2 = pocker[player[0]->t_pocker[1]]->number;
					int number3 = pocker[player[0]->t_pocker[2]]->number;
					int number4 = pocker[player[0]->t_pocker[3]]->number;
					if (number1 % 13 == number2 % 13 && number3 % 13 == number2 % 13 && number3 % 13 == number4 % 13 && number1 % 13 > number0 % 13)
					{
						isChupai = true;
					}
				}
			}
		}
		// 如果经过判断可以出牌
		if (isChupai)
		{
			playerChupai(0);
			if (player[0]->status == 0)
			{
				// 如果status被修改为0，说明发生了修改则说明可以换电脑出牌
				player[1]->status = 1;
				delay = 200;
				rule = 0;
			}
		}
		else
		{
			for (int i = 0; i < 14; i++)
			{
				int id = player[0]->m_pocker[i];
				if (pocker[id]->isSelected)
				{
					pocker[id]->card->setPositionY(pocker[id]->card->getPositionY() - 10);
				}
			}
		}
	}
}
void HelloWorld::diannaoChupai()
{
	// 默认取第一张牌，之后会在此处补上用于判断出哪些纸牌的算法
	if (player[1]->m_pocker[0] != -1)
	{
		// m_pocker[0] != -1说明玩家手中仍有纸牌，将其选中
		int id = player[1]->m_pocker[0];
		pocker[id]->isSelected = true;
	}
	playerChupai(1);
	/**
	bool isChupai = false;
	if (rule == 1)
	{
		// rule=1则随便出一张牌
		int id = rand() % (player[1]->count);
		if (id != -1)
		{
			pocker[id]->isSelected = true;
			isChupai = true;
		}
	}
	else if (rule == 0)
	{
		// 根据出牌数量进行分类
		if (player[0]->t_count == 1)
		{
			// 出牌数量为1
			for (int i = 0; i < 14; i++)
			{
				int id0 = player[1]->m_pocker[27 - i];
				if (id0 != -1 && player[0]->t_pocker[0]!=-1)
				{
					int number0 = pocker[player[0]->t_pocker[0]]->number;
					int number1 = pocker[id0]->number;
					if (number1 % 13>number0 % 13)
					{
						pocker[id0]->isSelected = true;
						isChupai = true;
						break;
					}
				}
			}
		}
		else if (player[0]->t_count == 2)
		{
			// 出牌数量为2
			for (int i = 0; i < 13; i++)
			{
				int id0 = player[1]->m_pocker[0];
				int number0 = pocker[id0]->number;
				int id1 = player[1]->m_pocker[27 - i];
				int number1 = pocker[id1]->number;
				int id2 = player[1]->m_pocker[27 - i - 1];
				int number2 = pocker[id2]->number;
				if (number2 % 13 == number1 % 13 && number0 % 13 < number2 % 13)
				{
					pocker[id1]->isSelected = true;
					pocker[id2]->isSelected = true;
					isChupai = true;
					break;
				}
			}
		}
		else if (player[0]->t_count == 3)
		{
			// 出牌数量为3
			for (int i = 0; i < 12; i++)
			{
				int id0 = player[1]->m_pocker[0];
				int number0 = pocker[id0]->number;
				int id1 = player[1]->m_pocker[27 - i];
				int number1 = pocker[id1]->number;
				int id2 = player[1]->m_pocker[27 - i - 1];
				int number2 = pocker[id2]->number;
				int id3 = player[1]->m_pocker[27 - i - 2];
				int number3 = pocker[id3]->number;
				if (number2 % 13 == number1 % 13 && number2 % 13 == number3 % 13 && number0 % 13 < number2 % 13)
				{
					pocker[id1]->isSelected = true;
					pocker[id2]->isSelected = true;
					pocker[id3]->isSelected = true;
					isChupai = true;
					break;
				}
			}
		}
		else
		{
			// 出牌数量为4
			for (int i = 0; i < 11; i++)
			{
				int id0 = player[1]->m_pocker[0];
				int number0 = pocker[id0]->number;
				int id1 = player[1]->m_pocker[27 - i];
				int number1 = pocker[id1]->number;
				int id2 = player[1]->m_pocker[27 - i - 1];
				int number2 = pocker[id2]->number;
				int id3 = player[1]->m_pocker[27 - i - 2];
				int number3 = pocker[id3]->number;
				int id4 = player[1]->m_pocker[27 - i - 3];
				int number4 = pocker[id4]->number;
				if (number2 % 13 == number1 % 13 && number2 % 13 == number3 % 13 && number4 % 13 == number3 % 13 && number0 % 13 < number2 % 13)
				{
					pocker[id1]->isSelected = true;
					pocker[id2]->isSelected = true;
					pocker[id3]->isSelected = true;
					pocker[id4]->isSelected = true;
					isChupai = true;
					break;
				}
			}
		}
	}
	if (isChupai)
	{
		playerChupai(1);
		if (player[1]->status == 0)
		{
			player[0]->status = 1;
			delay = 200;
			rule = 1;
		}
	}
	else
	{
		CCLOG("fangqi");
		player[1]->status = 0;
		player[0]->status = 1;
		rule = 0;
	}
	**/
}
void HelloWorld::playerChupai(int type)
{
	int d = 0;
	// 将被玩家选中的纸牌移除
	for (int i = 0; i < 14; i++)
	{
		int id = player[type]->m_pocker[i];
		// 确认纸牌是有效的
		if (id != -1)
		{
			CCLOG("%d:%d", i, id);
			if (pocker[id]->isSelected)
			{
				// 循环运行到这里说明确实发生了出牌的操作，可以认为出牌是有效的，将status置为0
				player[type]->status = 0;
				CCLOG("is chupai now........");
				if (type == 1)
				{
					// 由于电脑的纸牌显示的是背面，先通过方法showFont来将其翻过来
					pocker[id]->showFont();
				}
				// 纸牌移动
				pocker[id]->moveTo(Vec2(400 + 45 * d, 180), 1.2f);
				player[type]->removePocker(id);
				player[type]->addToHand(id);
				d++;			// 计数器加一
			}
		}
	}
	// 整理玩家手中的纸牌
	player[type]->updatePocker();
	for (int i = 0; i < 14; i++)
	{
		int id = player[type]->m_pocker[i];
		if (id != -1)
		{
			// 纸牌是有效的，开始位移
			auto pos = Vec2(player[type]->m_pos.x + 44 * i, player[type]->m_pos.y);
			pocker[id]->moveTo(pos, 1.3f);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		int id0 = player[0]->t_pocker[i];
		int id1 = player[0]->t_pocker[i];
		if (id0 != -1)
		{
			pocker[id0]->card->setOpacity(0);
		}
		if (id1 != -1)
		{
			pocker[id1]->card->setOpacity(0);
		}
	}
	//player[(type + 1) % 2]->cleanHand();
}
void HelloWorld::update(float dt)
{
	if (delay > 0)
	{
		CCLOG("%fwaiting......", dt);
		delay--;
	}
	else
	{
		if (player[1]->status == 1)
		{
			// 等于1，表示已经为出牌状态，出牌
			diannaoChupai();
			// 根据player[1]的status属性判断是否成功出牌，如果是则更换玩家出牌
			if (player[1]->status == 0)
			{
				player[0]->status = 1;
				delay = 200;
			}
		}
	}
}
void HelloWorld::wanjiaChupai()
{
	int d = 0;
	// 将被玩家选中的纸牌移除
	for (int i = 0; i < 14; i++)
	{
		int id = player[0]->m_pocker[i];
		// 确认纸牌是有效的
		if (id != -1)
		{
			CCLOG("%d:%d", i, id);
			if (pocker[id]->isSelected)
			{
				// 循环运行到这里说明确实发生了出牌的操作，可以认为出牌是有效的，将status置为0
				player[0]->status = 0;
				player[0]->addToHand(id);
				CCLOG("is chupai now........");
				// 纸牌移动
				pocker[id]->moveTo(Vec2(400 + 45 * d, 180), 1.2f);
				player[0]->removePocker(id);
				d++;			// 计数器加一
			}
		}
	}
	// 整理玩家手中的纸牌
	player[0]->updatePocker();
	for (int i = 0; i < 14; i++)
	{
		int id = player[0]->m_pocker[i];
		if (id != -1)
		{
			// 纸牌是有效的，开始位移
			auto pos = Vec2(player[0]->m_pos.x + 44 * i, player[0]->m_pos.y);
			pocker[id]->moveTo(pos, 1.3f);
		}
	}
}
