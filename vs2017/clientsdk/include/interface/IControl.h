/**************************************************
@describe:����
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
	* @brief ���ش���׺�Ĳ����
	* @param[in]��
	***********************************************/
    virtual std::string GetName()=0;
	/***********************************************
	* @brief ���ز�����׺�Ĳ����
	* @param[in]��
	***********************************************/
    virtual std::string GetDisplayName()=0;

    /***********************************************
	* @brief ����sdk�ͻ���ʵ������
	* @param[in]��
	***********************************************/
    virtual void SetSdkClientObj(void* obj)=0;
};
//��ȡʵ��������ָ�붨��
typedef IControl*(*GET_PLUGIN_FUNC)();
typedef void (*RELEASE_PLUGIN_FUNC)(IControl* pInstance);
}
