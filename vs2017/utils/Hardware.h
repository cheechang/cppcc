#pragma once
#include <string>
#include <vector>
namespace utils
{
    class Hardware
    {
    public:
        /// ∏Ò Ω"58:B0:35:FA:33:B7"
        static std::string mac();
		static std::vector<std::string>getlocalip();
    };
}