#pragma once
#include <QString>
#include <Defines.h>
class MsgItemBase
{
public:
	MsgItemBase();
	~MsgItemBase();
	MsgItemBase(const MsgItemBase &rh);
	MsgItemBase&  operator = (const MsgItemBase &rh);

	int64 snapeId() const;
	void setSnapeId(const int64& val);

	bool isRecv() const;
	void setIsRecv(const bool& val);

	bool isDevice() const;
	void setIsDevice(const bool& val);

	int msgType() const;
	void setMsgType(const int& val);

	int sendResult() const;
	void setMsgSendResult(const int& val);

	qint32 status()const;
	void setStatus(const qint32&val);

	qint64 msgId() const;
	void setMsgId(const qint64& val);

	QString msgTime() const;
	qint64  msgTimeMsc() const;
	void    setMsgTime(const qint64& val);

	qint64 sendId() const;
	QString strSendId() const;
	void setSendId(const qint64& val);

	qint64 uiLocalId() const;
	void setUiLocalId(const qint64& val);

	qint64 sdkLocalId() const;
	void setSdkLocalId(const qint64& val);
	
	qint64 targetId() const;
	QString strTargetId() const;
	void setTargetId(const qint64& val);

	QString name() const;
	void setName(const QString& val);

	QString avatar() const;
	void setAvatar(const QString& val);
private:
	bool    m_isRecv;        //�Ƿ��ǽ�����Ϣ
	bool    m_isDevice;		 //�Ƿ����豸ͬ����Ϣ
	int		m_msgType;		 //��Ϣ����
	int		m_sendResult;	 //��Ϣ���ͽ��:0���ɹ�; 1.������; -1.ʧ��
	qint32  m_satus;		 //���ݾ�����Ϣ������������״ֵ̬
	qint64	m_msgId;		 //��Ϣid
	qint64	m_msgTime;		 //��Ϣʱ��
	qint64	m_sendId;        //Ϊ�˸��·����ߵ�ͷ���������
	qint64	m_uiLocalId;     //�������õ�ÿ����Ϣ��ΨһID��Ϊ�˶�λ��Ϣ
	qint64	m_sdkLocalId;    //������Ϣsdk���ص�localID��Ϊ����Ϣ�ط���, �ļ��ϴ���ɺ󣬷�����ϢʱҪ��д�ϴ�ʱ���ɵ�localID��msg����
	qint64	m_targetId;      //Ŀ��id
	QString m_name;			 //������Ϣ������
	QString m_avatar;		 //������Ϣ��ͷ��
	int64  m_snapeId;       //����id
};
