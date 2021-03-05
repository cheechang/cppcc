#pragma once
#include <string>
namespace utils
{
	class PinYinConvert
	{
	public:
		static int GetTeam(std::string name);
		static std::string GetPinyin(std::string name);
	private:
		static std::string GetLetter(std::string strText);
		static std::string findLetter(int nCode);
	};
}