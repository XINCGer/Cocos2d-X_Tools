#include "EncryptValueInt.h"

bool EncryptValueInt::init(){
	setValue(0);
	return true;
}

void EncryptValueInt::setValue(int iValue){
	m_value = iValue;
	m_EncryptKey = rand();
	m_value ^= m_EncryptKey;

}

int EncryptValueInt::getValue(){
	return m_value ^= m_EncryptKey;
}