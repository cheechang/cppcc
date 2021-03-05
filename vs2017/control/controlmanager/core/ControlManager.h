#pragma once
#include <string>
#include <vector>
#include <map>
#include <Defines.h>
namespace control{
	class IControl;
    class DynamicLib;
	class ControlManager{
   public:
		explicit ControlManager(void);
		virtual ~ControlManager(void);
	public:
		static CSharedPtr<ControlManager> GetInstance();
		bool LoadAll();
		bool UnLoadAll();
		bool LoadPlugin(IControl* pPlugin);  
		bool UnLoadPlugin(IControl*  pPlugin);
		IControl*  Load(std::string&name);
		bool       UnLoad(std::string&name);
		IControl*  GetPlugin(std::string&name);
	private:
	   std::vector<IControl*>m_vecplugins; 
	   std::map<std::string,DynamicLib*>m_pluginLibs;
	   static CSharedPtr<ControlManager> m_instance;
	};
}
