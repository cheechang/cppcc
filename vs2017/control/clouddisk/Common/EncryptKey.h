#pragma once
#include <string>
#include <map>
//PC�����16λ��Կ�����㷨ͷ�ļ�����
class EncryptKey
{
public:
	EncryptKey();
	virtual ~EncryptKey();
	void initialise();
	std::string get_key();
private:
	int					m_rand;
	int					m_maxvalue;
	std::map<int, char> m_CharList;
};