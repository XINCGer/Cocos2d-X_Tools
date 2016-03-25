#ifndef _EncryptValueInt_H
#define _EncryptValueInt_H


#include "cocos2d.h"
USING_NS_CC;


class EncryptValueInt : public Ref{
public:
	CREATE_FUNC(EncryptValueInt);
	virtual bool init();
	void setValue(int iVlaue);
	int getValue();
private:
	int m_value;
	int m_EncryptKey;
};
#endif 