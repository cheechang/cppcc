#include "dircompress.h"
#include "common.h"
#include "ZLibWrapLib.h"

namespace utils
{
	bool DirCompress::zipdircompress(std::string srcfiles, std::string destdirpath, bool bUtf8){
		bool bret = false;
#ifdef _WIN32
		string_replace(srcfiles, "/", "\\");
		//bret = ZipCompress(srcfiles.c_str(), destdirpath.c_str(), bUtf8);
#else

#endif
		return bret;
	}
	bool DirCompress::zipdiruncompress(std::string srcfile, std::string destfolder){
		bool bret = false;
#ifdef _WIN32
		//bret = ZipExtract(srcfile.c_str(), destfolder.c_str());
#else

#endif
		return bret;
	}
}