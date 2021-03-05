#pragma once
#include <string>
namespace utils
{
    class DirCompress
    {
    public:
		static bool zipdircompress(std::string srcfiles, std::string destdirpath, bool bUtf8 = false);
		static bool zipdiruncompress(std::string srcfile, std::string destfolder);
    };
}