#pragma once

#include "../../controls/TWidget.h"
#include "controls/ElidedLabel.h"
#include <interface/Defines.h>
#include <data/SysMsgData.h>
class QGridLayout;
class QLabel;
class QPushButton;
class QVBoxLayout;
class QEvent;
class QSignalMapper;

namespace ui{
	class PushButton;
	class SystemMsgItem : public TWidget
	{
		Q_OBJECT
	public:
		explicit SystemMsgItem(QWidget *parent = 0);
		~SystemMsgItem();
		void Init();
		void SetItemData(data::SysMsg& data);
		int64 getSysMsgid(){ return m_msgID;};
		int64 getSysUserid(){ return m_userId;};
		
	signals:
		void signalDelBtnClicked(int64 msgId);
		void signalAgreeClicked(int64 msgId);
		void signalIgnoreClicked(int64 msgId);
	public slots:
		void onBtnDelClicekd();
		void onBtnAgreeClicekd();
		void onBtnIgnoreClicked();
	protected:
		void enterEvent(QEvent *e);
		void leaveEvent(QEvent *e);

	private:
		void initLayout();
		void initWidgets();
		void handleMsg(data::SysMsg sysMsg);
	private:
    CSharedPtr<PushButton>  m_ptrDel;           //删除条目

    CSharedPtr<QGridLayout> m_ptrGridLayout;    //栏栅布局
    CSharedPtr<QVBoxLayout> m_ptrMainLayout;    //主布局

    CSharedPtr<QLabel>      m_ptrDate;          //日期显示
    CSharedPtr<QLabel>      m_ptrName;          //显示名字
   // CSharedPtr<QLabel>      m_ptrStatu;          //显示已同意

    CSharedPtr<QLabel>      m_ptrExtraMsg;      //附加信息
    CSharedPtr<QLabel>      m_ptrNotifyMsg;     //通知消息
    CSharedPtr<QLabel>      m_ptrSplitteLine;   //分割线

    CSharedPtr<QPushButton>  m_ptrAgree;          //同意
    CSharedPtr<QPushButton>  m_ptrIgnore;          //忽略

	int64						  m_msgID;
	int64                         m_userId;
	};
}

