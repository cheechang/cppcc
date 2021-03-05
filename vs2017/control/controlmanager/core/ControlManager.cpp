#include "ControlManager.h"
#include "Dynamiclib.h"
#include "../utils/common.h"
#include "ControlClient.h"
#include <IControl.h>
#include <log.h>
namespace control{
	 CSharedPtr<ControlManager> ControlManager::m_instance = CNull;
	 ControlManager::ControlManager(void){
	 }
	 ControlManager::~ControlManager(void){
	 }
bool ControlManager::LoadAll(){
BEGIN;
	bool bret = false;
	std::string dirpath("");
	std::vector<std::string> filelist;
	dirpath = utils::GetModulePath();
	dirpath +="/LddPlugins/";

	DynamicLib::SetPluginDir(dirpath);
	dirpath +="*.dll";
	utils::EnumAllFiles(dirpath,filelist);
	for (size_t index=0; index<filelist.size(); ++index)
	{
		utils::string_replace(filelist[index],".dll","");
		IControl* pInstance = Load(filelist[index]);
		if ( NULL == pInstance)
		{
			AddLog(LOG_LEV_ERROR,"插件加载(%s)失败",filelist[index].c_str());
			continue;
		}
		AddLog(LOG_LEV_ERROR,"插件加载(%s)成功!",filelist[index].c_str());
		m_vecplugins.push_back(pInstance);
	}
	bret = true;
END;
	return bret;
}
bool ControlManager::UnLoadAll(){
BEGIN;
	std::string dirpath("");
	std::vector<std::string> filelist;

	dirpath = DynamicLib::GetPluginDir();
	dirpath +="*.dll";
	utils::EnumAllFiles(dirpath,filelist);
	for (size_t index=0; index<filelist.size(); ++index)
	{
		UnLoad(filelist[index]);
		AddLog(LOG_LEV_ERROR,"卸载插件(%s)",filelist[index].c_str());
	}
END;
	return true;
}
bool ControlManager::LoadPlugin(IControl *pPlugin){
	return false;
}
bool ControlManager::UnLoadPlugin(IControl* pPlugin){
	return false;
}
IControl* ControlManager::Load(std::string&name){
	auto iter = m_pluginLibs.find(name);  
    if (iter == m_pluginLibs.end())  //不存在就需要插入  
    {  
        DynamicLib* pLib = new DynamicLib;  
        if (NULL != pLib)  
        {  
            pLib->LoadLib(name.c_str());  
            m_pluginLibs.insert(std::make_pair(name,pLib));  
            GET_PLUGIN_FUNC pFun = (GET_PLUGIN_FUNC)(pLib->GetFuncAddress("GetPluginInstance"));  
            if (pFun != NULL)  
            {  
                IControl* pPlugin = pFun(); 
				pPlugin->SetSdkClientObj(static_cast<void*>(ControlClient::GetSdkClient()));
				pLib->SetPlugin(pPlugin);
                return pPlugin;  
            } 
            return NULL;  
        }  
    }  
    else //如果存在，在插件列表里面寻找名字是strName的插件  
    {  
        for (size_t index=0;index<m_vecplugins.size();++index)  
        {  
			if (name == m_vecplugins[index]->GetDisplayName())  
            {   
                return m_vecplugins[index];  
            }
        }  
    }   
    return NULL;  
}
bool  ControlManager::UnLoad(std::string&name){
	auto iter = m_pluginLibs.begin();  
    for (; iter != m_pluginLibs.end(); ++iter )  
    {  
        DynamicLib *pLib = iter->second;  
        if (NULL == pLib)  
        {  
            continue;  
        }  
		if (name == pLib->GetLibName())  
        {  
            RELEASE_PLUGIN_FUNC pFun = (RELEASE_PLUGIN_FUNC)pLib->GetFuncAddress("ReleasePluginInstance");  
            if (pFun != NULL)  
            {  
               pFun(pLib->GetPlugin());  
            }  
            pLib->FreeLib();  
            delete pLib;  
            //然后从列表中删除  
          //  m_pluginLibs.erase(iter);  
            return true;  
        }  
    } 
    return false;  
}
IControl* ControlManager::GetPlugin(std::string&name){
	for (size_t index=0;index<m_vecplugins.size();++index)  
	{  
		if (name == m_vecplugins[index]->GetDisplayName())  
		{   
			return m_vecplugins[index];  
		}
	}  
	return CNull;
}
 CSharedPtr<ControlManager> ControlManager::GetInstance(){
	 if ( CNull == m_instance)
	 {
		 m_instance=CMakePtr<ControlManager>();
	 }
	 return m_instance;
 }
}