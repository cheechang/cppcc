#include <time.h>
#include <stdlib.h>
#include "EncryptKey.h"
EncryptKey::EncryptKey() :m_rand(0)
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
	std::map<int,char> CharList;
	/*{ 
		{0, '0'}, {1, '1'}, {2, '2'}, {3, '3'}, {4, '4'}, {5, '5'}, {6, '6'},
		{7, '7'}, { 8, '8' }, { 9, '9' }, { 10, 'a' }, { 11, 'b' }, { 12, 'c' }, { 13, 'd' },
		{14, 'e' },{15, 'f' }, { 16, 'g' }, { 17, 'h' }, { 18, 'i' }, { 19, 'j' }, { 20, 'k' },
		{21, 'l' }, {22, 'm' }, { 23, 'n' }, { 24, 'o' }, { 25, 'p' }, { 26, 'q' }, { 27, 'r' },
		{28, 's' }, {29, 't' }, { 30, 'u' }, { 31, 'v' }, { 32, 'w' }, { 33, 'x' }, { 34, 'y' }, { 35, 'z' }};*/
		{
			CharList[0]='0';CharList[1]='1';CharList[2]='2';CharList[3]='3';CharList[4]='4';
			CharList[5]='5';CharList[6]='6';CharList[7]='7';CharList[8]='8';CharList[9]='9';
			CharList[10]='a';CharList[11]='b';CharList[12]='c';CharList[13]='d';CharList[14]='e';
			CharList[15]='f';CharList[16]='g';CharList[17]='h';CharList[18]='i';CharList[19]='j';
			CharList[20]='k';CharList[21]='l';CharList[22]='m';CharList[23]='n';CharList[24]='o';
			CharList[25]='p';CharList[26]='q';CharList[27]='r';CharList[28]='s';CharList[29]='t';
			CharList[30]='u';CharList[31]='v';CharList[32]='w';CharList[33]='x';CharList[34]='y';CharList[35]='z';
		}
	m_CharList = CharList;
	
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
