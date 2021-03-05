#pragma once
#include <QObject>
#include <memory>
#include <QMap>
#include <interface/Defines.h>
namespace ui{   
class SystemTray;
class BaseDialog;
class WindowsManager : public QObject
{
    Q_OBJECT
public:
    WindowsManager(QObject *parent=0);
    ~WindowsManager();
	void Init();
	void restart_process();
public slots:
	void onloginSuccess();
	void onExitClient(bool isrestart);
protected:
	void InitSystemInfo(void);//��ʼ��ϵͳϵͳ
	void LoadLanguage(void);        //����ϵͳ����
	void InitControlClient(void);//��ʼ��ҵ���
private:
	QMap<int,CSharedPtr<BaseDialog>> m_wndlist;
	CSharedPtr<SystemTray> m_system_tray; //������
private:
	 bool m_isrestart;
};
extern ui::WindowsManager* gWinManger ;
}
