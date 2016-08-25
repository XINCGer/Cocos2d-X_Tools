#include "Pocker.h"
USING_NS_CC;
Pocker* Pocker::createPocker(int number, Point position, bool isFont)
{
	Pocker* pocker = Pocker::create();
	if (pocker)
	{
		pocker->initPocker(number, position, isFont);
		return pocker;
	}
	CC_SAFE_DELETE(pocker);
	return NULL;
}
void Pocker::initPocker(int number, Point position, bool isFont)
{
	this->isSelected = false;
	this->number = number;
	// 创建卡牌正面
	card = Sprite::create(String::createWithFormat("%d.jpg",number)->getCString());
	card->setScale(0.4f);
	card->setPosition(position);
	addChild(card);
	// 卡牌背面
	back = Sprite::create("card.png");
	auto cardSize = card->getContentSize();
	back->setPosition(cardSize.width / 2, cardSize.height / 2);
	// 根据参数isFont来判断显示纸牌的正面还是背面
	if (!isFont)
	{
		isActive = false;
	}
	else
	{
		back->setOpacity(0);
		this->isActive = true;
	}
	card->addChild(back);

	// 触摸事件的绑定
	listener = EventListenerTouchOneByOne::create();//创建单点触摸事件监听器
	listener->onTouchBegan = CC_CALLBACK_2(Pocker::onTouchBegan, this);//触摸开始
	listener->setSwallowTouches(true);//不向下吞并触摸
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
bool Pocker::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	auto point = pTouch->getLocation();
	auto position = this->card->getPosition();
	// 判断是哪一张纸牌被点击
	if (point.x > position.x - CARDX&&point.x<position.x + CARDX&&point.y>position.y - CARDY&&point.y < position.y + CARDY)
	{
		// 确保当前纸牌为正面显示
		if (this->isActive)
		{
			// 判断纸牌接下来进行的操作
			if (this->isSelected)
			{
				this->card->setPositionY(position.y - 10);
				this->isSelected = false;
			}
			else
			{
				this->card->setPositionY(position.y + 10);
				this->isSelected = true;
			}
		}
	}
	return false;
}
void Pocker::setTouchPriority(int num){
	_eventDispatcher->setPriority(listener, num);
}
void Pocker::showLast()
{
	if (isActive)
	{
		back->setOpacity(255);
		this->isActive = false;
	}
}
void Pocker::showFont()
{
	if (!isActive)
	{
		back->setOpacity(0);
		this->isActive = true;
	}
}
void Pocker::moveTo(Point des, float time)
{
	auto* moveto = MoveTo::create(time,Vec3(des.x,des.y,card->getPositionZ()));
	card->runAction(moveto);
}