#include "MsgItemBase.h"
#include "common/MsgTimeDeal.hpp"
#include "common/Common.h"
MsgItemBase::MsgItemBase():m_isRecv(false),m_msgType(0),m_sendResult(0),m_satus(0),
m_msgId(0),m_msgTime(0),m_sendId(0),m_uiLocalId(0),m_sdkLocalId(0),m_targetId(0)
{
}
MsgItemBase::~MsgItemBase()
{

}
MsgItemBase::MsgItemBase(const MsgItemBase &rh)
{
	 m_isRecv = rh.isRecv();
	 m_msgType = rh.msgType();
	 m_sendResult = rh.sendResult();	
	 m_msgId = rh.msgId();
	 m_msgTime = rh.msgTimeMsc();
	 m_sendId = rh.sendId();        
	 m_uiLocalId = rh.uiLocalId();         		
	 m_targetId = rh.targetId();
	 m_satus = rh.status();
}
MsgItemBase&  MsgItemBase::operator = (const MsgItemBase &rh)
{
	m_isRecv = rh.isRecv();
	m_msgType = rh.msgType();
	m_sendResult = rh.sendResult();
	m_msgId = rh.msgId();
	m_msgTime = rh.msgTimeMsc();
	m_sendId = rh.sendId();
	m_uiLocalId = rh.uiLocalId();
	m_targetId = rh.targetId();
	m_satus = rh.status();
	return *this;
}
bool MsgItemBase::isRecv() const
{
	return m_isRecv;
}
void MsgItemBase::setIsRecv(const bool&isRecv)
{
	m_isRecv = isRecv;
}
bool MsgItemBase::isDevice() const{
	return m_isDevice;
}
void MsgItemBase::setIsDevice(const bool& val){
	m_isDevice = val;
}

int MsgItemBase::msgType() const
{
	return m_msgType;
}
void MsgItemBase::setMsgType(const int& msgType)
{
	m_msgType = msgType;
}
int MsgItemBase::sendResult() const
{
	return m_sendResult;
}
void MsgItemBase::setMsgSendResult(const int& result)
{
	m_sendResult = result;
}

void  MsgItemBase::setStatus(const qint32&val){
	m_satus = val;
}
qint32 MsgItemBase::status()const{
	return m_satus;
}

qint64 MsgItemBase::msgId() const
{
	return m_msgId;
}
void MsgItemBase::setMsgId(const qint64& msgId)
{
	m_msgId = msgId;
}
qint64 MsgItemBase::targetId() const
{
	return m_targetId;
}

QString MsgItemBase::strTargetId() const
{
	return QString::number(m_targetId);
}
void MsgItemBase::setTargetId(const qint64& val)
{
	m_targetId = val;
}

qint64 MsgItemBase::uiLocalId() const
{
	return m_uiLocalId;
}
void MsgItemBase::setUiLocalId(const qint64& val)
{
	m_uiLocalId = val;
}
qint64 MsgItemBase::sdkLocalId() const
{
	return m_sdkLocalId;
}
void MsgItemBase::setSdkLocalId(const qint64& val)
{
	m_sdkLocalId = val;
}
QString MsgItemBase::msgTime() const
{
	return DealMsgTime(m_msgTime,CHATWND_TIME);
}
qint64 MsgItemBase::msgTimeMsc() const
{
	return m_msgTime;
}
void MsgItemBase::setMsgTime(const qint64& val)
{
	m_msgTime = val;
}
qint64 MsgItemBase::sendId() const
{
	return m_sendId;
}
QString MsgItemBase::strSendId() const
{
	return QString::number(m_sendId);
}
void MsgItemBase::setSendId(const qint64& val)
{
	m_sendId = val;
}
QString MsgItemBase::name() const
{
	return m_name;
}
void MsgItemBase::setName(const QString& val)
{
	m_name = val;
}
QString MsgItemBase::avatar() const
{
	return m_avatar;
}
void MsgItemBase::setAvatar(const QString& val)
{
	m_avatar = val;
}

int64 MsgItemBase::snapeId() const
{
	return m_snapeId;
}

void MsgItemBase::setSnapeId(const int64& val)
{
	m_snapeId = val;
}
