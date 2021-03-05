#pragma  once
#include <string>
#include <utility>
#include <map>
class EmojiExpress
{
public:
	EmojiExpress();
	~EmojiExpress();
	static void EmojiParseFrom(std::string src, std::string& target,std::string&rp=std::string(""));
	static void EmojiParseTo(std::string src, std::string& target);
private:
	static void init();
private:
	 static std::map<std::string, std::string>m_EmojiMap;
 };

