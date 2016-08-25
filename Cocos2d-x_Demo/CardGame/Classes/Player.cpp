#include "Player.h"
USING_NS_CC;
Player::Player(int type)
{
	count = 0;
	t_count = 0;
	this->status = 0;		// 0为默认状态
	this->type = type;
	for (int i = 0; i < 14; i++)
	{
		m_pocker[i] = -1;	// -1标识为空
	}
	for (int i = 0; i < 4; i++)
	{
		t_pocker[i] = -1;
	}
	if (type == 0)
	{
		m_pos = Vec2(35, 45);
	}
	else
	{
		m_pos = Vec2(35, 315);
	}         
}
void Player::addPocker(int id)
{
	if (count <= 14)
	{
		// 玩家持有纸牌的最大数量为14
		m_pocker[count] = id;
		count++;
	}
}
void Player::removePocker(int id)
{
	// 对数组遍历查找等于id的值
	for (int i = 0; i < 14; i++)
	{
		if (m_pocker[i] == id)
		{
			m_pocker[i] = -1;
		}
	}
}
void Player::updatePocker()
{
	for (int i = 1; i < 14; i++)
	{
		// 从m_pocker数组的第2个元素开始遍历
		if (m_pocker[i] >= 0)
		{
			for (int j = 0; j < i; j++)
			{
				if (m_pocker[j] == -1)
				{
					// 如果找到空白的纸牌位
					m_pocker[j] = m_pocker[i];
					m_pocker[i] = -1;
				}
			}
		}
	}
}
void Player::addToHand(int id)
{
	// 判断数组t_pocker是否是满的
	if (t_count >= 0 && t_count < 4)
	{
		t_pocker[t_count] = id;
	}
	t_count++;
}
void Player::cleanHand()
{
	// 训话清除数组t_pocker中的纸牌
	for (int i = 0; i < t_count; i++)
	{
		t_pocker[i] = -1;
	}
	t_count = 0;
}
