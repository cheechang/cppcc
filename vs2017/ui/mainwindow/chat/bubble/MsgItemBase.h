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
	bool    m_isRecv;        //是否是接收消息
	bool    m_isDevice;		 //是否是设备同步消息
	int		m_msgType;		 //消息类型
	int		m_sendResult;	 //消息发送结果:0，成功; 1.发送中; -1.失败
	qint32  m_satus;		 //根据具体消息定义具体所需的状态值
	qint64	m_msgId;		 //消息id
	qint64	m_msgTime;		 //消息时间
	qint64	m_sendId;        //为了更新发送者的头像或者名称
	qint64	m_uiLocalId;     //界面上用的每条消息的唯一ID，为了定位消息
	qint64	m_sdkLocalId;    //发送消息sdk返回的localID，为了消息重发用, 文件上传完成后，发送消息时要填写上传时生成的localID到msg里面
	qint64	m_targetId;      //目标id
	QString m_name;			 //本条消息的姓名
	QString m_avatar;		 //本条消息的头像
	int64  m_snapeId;       //快照id
};
