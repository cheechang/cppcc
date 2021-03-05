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
	CSharedPtr<QAction> m_pDelItem;			//ɾ��
	CSharedPtr<QAction> m_pRecallItem;		//����
	CSharedPtr<QAction> m_pCollectItem;		//�ղ�
	CSharedPtr<QAction> m_pTransportItem;	//ת��
	CSharedPtr<QAction> m_pCopyItem;		//����
	CSharedPtr<QAction> m_pSaveItem;		//����
	CSharedPtr<QAction> m_pMsgStatus;  //��Ϣ״̬
	CSharedPtr<QAction> m_pCloudDisdkItem;  //��������
	CSharedPtr<QAction> m_pRecallEditItem; //�����ر༭
	CSharedPtr<QAction> m_pMsgTopItem;	//��Ϣ�ö�
private:
	qint64	 m_targetId;
	qint64   m_localId;
	qint64	 m_msgTime;
	bool	 m_isRecv;
};
#endif