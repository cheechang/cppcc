#pragma once
#include <interface/IControl.h>
#include "interface/Defines.h"
#include "interface/Exports.h"
#include "data/SysMsgData.h"
namespace control {
	class ISysMsgMgrControl:public IControl {
	public:
	/*****************************************ע��֪ͨ�ص�*******************************************/

	/**
	* \brief ���ü���ϵͳ��Ϣ�Ļص�
	* @param[out] cb �յ�ϵͳ��Ϣ�ص� _1ϵͳ��Ϣ�ṹ
	*/
		virtual void regSysMsgCb(CFunction<void(const  data::SysMsg&)> cb) = 0;

	/**
	* \brief ���ü�������δ��ϵͳ��Ϣ�Ļص�
	* @param[out] cb �յ�����δ��ϵͳ��Ϣ�ص� _1���һ��ϵͳ��Ϣ��_2δ��ϵͳ��Ϣ����
	*/
	virtual void regLastSysMsgCb(CFunction<void(const  data::SysMsg&, int)> cb) = 0;

	/*****************************************����ӿ�*******************************************/

	/**
	* \brief ��Ӧ�Ӻ��ѵ�����
	* @param[in] userId �����ߵ��û�ID 
	* @param[in] msgId ������Ϣ��msgId
	* @param[in] operType �Դ�����Ĳ���: 1.���� 2.ͬ�� 3.�ܾ� 4.�ܾ����������ٴ�����
	* @param[in] remark ���ѱ�ע
	* @param[in] refuseReason �����ľܾ���Ϣ
	* @param[out] cb  ������ս���ص�  _1������Ϣ
	*/
	virtual void respToAddBuddy(int64 userId, int64 msgId,  data::SysOperType operType, const std::string &remark, 
									const std::string &refuseReason, CFunction<void(int)> cb) = 0;

	/**
	* \brief ��Ӧ��Ⱥ������
	* @param[in] groupId Ҫ�����ȺID
	* @param[in] msgId ������Ϣ��msgId
	* @param[in] operType �Դ�����Ĳ�����1.���� 2.ͬ�� 3.�ܾ� 4.�ܾ����������ٴ�����
    *      ����ǻ�Ӧ�������Ⱥ��Ϣ��ֻ��2ͬ���3�ܾ�ѡ��
	* @param[in] refuseReason �����ľܾ���Ϣ
    * @param[out] cb  ������ս���ص�  _1������Ϣ
	*/
	virtual void respToEnterGroup(int64 groupId, int64 msgId,  data::SysOperType operType, const std::string &refuseReason, 
										CFunction<void(int)> cb) = 0;

	/**
	* \brief ������Ϣ�Ѷ�
	* @param[in] type �����������1 ����������֤���Ѷ�|2 �������󷵻ؿ��Ѷ�| 3 ����Ⱥ��֤������Ϣ�Ѷ�|4 ����Ⱥ��֤��Ӧ��Ϣ�Ѷ�                      
	* @param[in] msgs ������Ϣid����
	* @param[out] cb  ������ս���ص�  _1������Ϣ
	*/
	virtual void setMessagRead(int type, std::vector<int64> &msgs, CFunction<void(int)> cb) = 0;

	/**
	* \brief ��ȡϵͳ��Ϣ��Ϣ
	* @param[in] type  ������Ӧ��Ϣ���� 0 ȫ�� 1 �Ӻ������� 2 �Ӻ�����Ӧ 3 ��Ⱥ���� 4 ��Ⱥ
	* @param[in] count ��������
	* @param[in] time  ���ҵ���ʼʱ�� 
	* @param[in] flag   ����ƫ�Ʊ�־ 0 �Դ����time��ʼ������ƫ�ƣ���ȡС��time����Ϣ ���time = 0������������յ���ϵͳ��Ϣ��ʼ��ȡ
	                                1 �Դ����time��ʼ������ƫ�ƣ���ȡ����time����Ϣ. 
	* @param[out] cb  ������ս���ص�  _1������Ϣ  _2ϵͳ��Ϣ����
	*/
	virtual void getMessages(int type,int count,int64 time,int flag, CFunction<void(int,std::vector< data::SysMsg>&)>cb) = 0;	

	/**
	* \brief ɾ��ȫ��ϵͳ��Ϣ
	* @param[out] cb  ������ս���ص�  _1������Ϣ
	*/
	virtual void deleteAllMessage(CFunction<void(int)> cb) = 0;

	/**
	* \brief ͨ������ɾ��ϵͳ��Ϣ
	* @param[in] type  ��Ϣ����  �����������1 ����������֤���Ѷ�|2 �������󷵻ؿ��Ѷ�| 3 ����Ⱥ��֤������Ϣ�Ѷ�|4 ����Ⱥ��֤��Ӧ��Ϣ�Ѷ� 
	* @param[in] msgIds ��ϢID����
	* @param[out] cb  ������ս���ص�  _1������Ϣ
	*/
	virtual void deleteMessageByType(int type, std::vector<int64> msgIds, CFunction<void(int)> cb) = 0;

	};
	extern "C" CONTROL_EXPORT_API IControl* GetPluginInstance();
	extern "C" CONTROL_EXPORT_API void ReleasePluginInstance(IControl* instance);
}