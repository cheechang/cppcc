#pragma once
#include <map>
#include <string>
#include <errorExport.h>
#include "Singleton.hpp"
namespace utils
{
	class Error
	{
		struct CodeMap
		{
			CodeMap();
			const char* info(int code) const;
			void init(bool isChinese);
		private:
			std::map<int, const char*> m_arr;
		};
	private:
		static bool m_isChinese;
	public:
		static void InitErrInfo(bool isChinese){
            m_isChinese = isChinese;
			utils::Singleton<CodeMap>::instance().init(isChinese);
		}
		static bool IsChinese(){
			return m_isChinese;
		}
		static std::string GetErrMsg(const int code){
			return std::string(utils::Singleton<CodeMap>::instance().info(code));
		}
	};
}