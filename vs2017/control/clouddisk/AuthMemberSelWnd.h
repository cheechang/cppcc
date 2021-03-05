#pragma once
#include <model/Packet.h>
#include <qdialog.h>
#include <qsharedpointer.h>
class QTabWidget;
class QVBoxLayout;
class QPushButton;
class QHBoxLayout;
namespace ui{
	class TitleBar;
	class ContactListWidget;
	class OrgListWidget;
	class AuthMemberSelWnd :public QDialog{
		Q_OBJECT
	public:
		explicit AuthMemberSelWnd(QVector<qint64>&memberlist,QWidget*parent = NULL);
		virtual  ~AuthMemberSelWnd();
	signals:
		void signalAuthMembers(std::vector<model::TeamMemberInfo>&);
	protected:
		void paintEvent(QPaintEvent *event);
	public slots:
		void onOkBtnClicked();
		void onCancelBtnClicked();
		void onChecked(qint32 type, qint64 id, bool ischecked);
	private:
		std::shared_ptr<TitleBar>				m_titleBar;
		std::shared_ptr<QTabWidget>				m_tabWidget;
		std::shared_ptr<ContactListWidget>		m_contactList;
		std::shared_ptr<OrgListWidget>			m_orgList;
		std::shared_ptr<QPushButton>				m_okBtn;
		std::shared_ptr<QPushButton>				m_cancelBtn;
		/*QSharedPointer<TitleBar>				m_titleBar;
		QSharedPointer<QTabWidget>				m_tabWidget;
		QSharedPointer<ContactListWidget>		m_contactList;
		QSharedPointer<OrgListWidget>			m_orgList;
		QSharedPointer<QPushButton>				m_okBtn;
		QSharedPointer<QPushButton>				m_cancelBtn;*/
		QHBoxLayout*							m_btnLayout;
		QVBoxLayout*							m_contentLayout;
		QVBoxLayout*							m_mainLayout;
	};
}