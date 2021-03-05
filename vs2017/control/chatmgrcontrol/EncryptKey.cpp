#include <time.h>
#include <stdlib.h>
#include "EncryptKey.h"
EncryptKey::EncryptKey():m_rand(0)
{
	initialise();
}
//析构函数
EncryptKey::~EncryptKey()
{

}
//初始化
void EncryptKey::initialise()
{
	m_CharList.clear();
	for (int i=0; i<10;++i)
	{
		m_CharList.insert(std::pair<int,char>(i,char(i)+'0'));
	}
	for (int i=10; i<36;++i)
	{
		m_CharList.insert(std::pair<int,char>(i,char(i-10)+'a'));
	}
	m_maxvalue = m_CharList.size();
	srand((unsigned)time(NULL));

}
//生成16位秘钥
std::string EncryptKey::get_key()
{
	std::string key("");
	int			pos = 0;
	char		Temp = 0;

	for (int index = 0; index < 16; ++index)
	{
		pos = rand() % m_maxvalue;
		Temp = m_CharList[pos];
		key += Temp;
	}
	return key;
}
