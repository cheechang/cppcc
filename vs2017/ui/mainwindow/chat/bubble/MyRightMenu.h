#ifndef MY_RIGHT_MENU__H
#define MY_RIGHT_MENU__H
#include <QMenu>
#include <interface/Defines.h>
enum MenuItem
{
	MENU_DEL,
	MENU_COLLECT,
	MENU_RECALL,
	MENU_TRANSPORT,
	MENU_COPY,
	MENU_SAVE,
	MENU_MSGSTATUS,
	MENU_SAVECLOUDDISK,
	MENU_RECALLEDIT,
	MENU_TOPMSG
};
class MyRightMenu :public QMenu{
	Q_OBJECT
public:
	MyRightMenu(QWidget *parent = 0);
	virtual ~MyRightMenu();
	void init(qint64 targetId, qint64 localId, qint64 msgTime, bool isRecv);
	void setMenuState(MenuItem item,bool isShow);
	void show();
public slots:
	void onCtrlDelMenu();
	void onCtrlRecallMenu();
	void onCtrlCollectMenu();
	void onCtrlTransportMenu();
	void onCtrlCopyMenu();
	void onCtrlSaveMenu();
	void onCtrlMsgStatusMenu();
	void onCtrlSaveCloudDiskMenu();
	void onCtrlRecallEditMenu();
	void onCtrMsgTopMenu();
signals:
	void signalCtrlDelMenu(qint64 targetId, qint64 localId);
	void signalCtrlRecallMenu(qint64 targetId, qint64 localId);
	void signalCtrlCollectMenu(qint64 targetId, qint64 localId);
	void signalCtrlTransportMenu(qint64 targetId, qint64 localId);
	void signalCtrlCopyMenu(qint64 targetId, qint64 localId);
	void signalCtrlSaveMenu(qint64 targetId, qint64 localId);
	void signalCtrlMsgStatusMenu(qint64 targetId, qint64 localId);
	void signalCtrlSaveCloudDiskMenu(qint64 targetId, qint64 localId);
	void signalCtrlRecallEditMenu(qint64 targetId, qint64 localId);
	void siganlCtrMsgTopMenu(qint64 targetId, qint64 localId);
private:
	CSharedPtr<QAction> m_pDelItem;			//删除
	CSharedPtr<QAction> m_pRecallItem;		//撤回
	CSharedPtr<QAction> m_pCollectItem;		//收藏
	CSharedPtr<QAction> m_pTransportItem;	//转发
	CSharedPtr<QAction> m_pCopyItem;		//复制
	CSharedPtr<QAction> m_pSaveItem;		//保存
	CSharedPtr<QAction> m_pMsgStatus;  //消息状态
	CSharedPtr<QAction> m_pCloudDisdkItem;  //保存云盘
	CSharedPtr<QAction> m_pRecallEditItem; //撤销重编辑
	CSharedPtr<QAction> m_pMsgTopItem;	//消息置顶
private:
	qint64	 m_targetId;
	qint64   m_localId;
	qint64	 m_msgTime;
	bool	 m_isRecv;
};
#endif