#include "DynamicLib.h"
#include <memory>
namespace control{
	std::string DynamicLib::m_plugindirpath="";
	DynamicLib::DynamicLib(void):m_libname(""),m_module(CNull),m_plugin(CNull){

	}
	DynamicLib::~DynamicLib(void){

	}
	void DynamicLib::SetPluginDir(const std::string&plugindir){
		m_plugindirpath = plugindir;
	}
	std::string DynamicLib::GetPluginDir(){
		return m_plugindirpath;
	}
	IControl* DynamicLib::GetPlugin()const{
		return m_plugin;
	}
	void DynamicLib::SetPlugin(IControl*plugin){
		m_plugin = plugin;
	}
	bool  DynamicLib::LoadLib(const std::string&libname){
		bool bret = false;
#ifdef _WIN32
		std::string strName =m_plugindirpath+libname;  
		strName += ".dll";  
		m_module = LoadLibrary(strName.c_str());  
		if (NULL != m_module)  
		{  
			m_libname = libname;
			bret = true;
			return bret;  
		}  
#endif
		return bret;  
	}
	void  DynamicLib::FreeLib(){
		if (NULL != m_module)
		{
			FreeLibrary(m_module);
			m_module = NULL;
		}
	}
	std::string DynamicLib::GetLibName()const{
		return m_libname;
	}
	void* DynamicLib::GetFuncAddress(const  std::string& funcname)const{
		if ( NULL == m_module)
		{
			return NULL;
		}
		return  (void*)GetProcAddress(m_module,funcname.c_str());
	}
}
