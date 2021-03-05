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
	void InitSystemInfo(void);//初始化系统系统
	void LoadLanguage(void);        //加载系统语言
	void InitControlClient(void);//初始化业务层
private:
	QMap<int,CSharedPtr<BaseDialog>> m_wndlist;
	CSharedPtr<SystemTray> m_system_tray; //托盘项
private:
	 bool m_isrestart;
};
extern ui::WindowsManager* gWinManger ;
}
