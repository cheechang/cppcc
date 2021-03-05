#pragma once
#include <string>
#include <Defines.h>
namespace control{
	class IControl;
	class DynamicLib{
	public:
		explicit DynamicLib(void);
		virtual ~DynamicLib(void);
	public:
		static void SetPluginDir(const std::string&plugindir);
		static std::string GetPluginDir();
		IControl* GetPlugin()const;
		void      SetPlugin(IControl*plugin);
		bool  LoadLib(const std::string&libname);
		void  FreeLib();
		std::string GetLibName()const;
		void* GetFuncAddress(const  std::string& funcname)const;
	private:
	    IControl*   m_plugin;
		std::string m_libname;
		HLIB m_module;
		static std::string m_plugindirpath;
	};
}
