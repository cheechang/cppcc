/**************************************************
@describe:豆豆
@author:lxy
***************************************************/
#pragma once
#include <string>
#include <functional>
#include <vector>
#include <memory>
namespace control{
class IControl{
public:  
	/***********************************************
	* @brief 返回带后缀的插件名
	* @param[in]无
	***********************************************/
    virtual std::string GetName()=0;
	/***********************************************
	* @brief 返回不带后缀的插件名
	* @param[in]无
	***********************************************/
    virtual std::string GetDisplayName()=0;

    /***********************************************
	* @brief 设置sdk客户端实例对象
	* @param[in]无
	***********************************************/
    virtual void SetSdkClientObj(void* obj)=0;
};
//获取实例对象函数指针定义
typedef IControl*(*GET_PLUGIN_FUNC)();
typedef void (*RELEASE_PLUGIN_FUNC)(IControl* pInstance);
}
