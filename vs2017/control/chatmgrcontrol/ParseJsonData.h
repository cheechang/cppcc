#pragma once
#include <string>
namespace control{
	class ParseJsonData{
	public:
		explicit ParseJsonData();
		virtual ~ParseJsonData();
		static std::string ParaseJson(int msgtype,int acivetype,std::string json,std::string msgprop);
		static std::string char2utf8(std::string src);
		static std::string utf82char(std::string src);
		static std::string emojideal(std::string text,bool isdealInstuct=true);
		static std::string emojisenddeal(std::string text);
		static int dealEraserType(std::string text);
	};
}