#pragma  once
#include <string>
#include <utility>
#include <map>

	class InstructExpress
	{
	public:
		InstructExpress();
		~InstructExpress();
		static void InstructParseTo(std::string src, std::string& target);
		static void InstructParseFrom(std::string src, std::string& target);
   private:
		static void init();
		static std::string getExpression(const std::string& instruct);
		static std::string getInstruct(const std::string& expression);
	private:
		static std::map<std::string, std::string> m_InstructMap;
		static std::map<std::string, std::string> m_engInstructMap;
	};

