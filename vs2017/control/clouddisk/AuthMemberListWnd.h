#pragma once
#include <qdialog.h>
#include <QWidget>   
#include <QEvent> 
#include <model/packet.h>
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
namespace ui{
	class PushButton;
	class AuthMemListWidget;
	class AuthMemList;
	class AuthMemListItem;
	class TitleBar;
	class AuthMemberListWnd :public QDialog{
		Q_OBJECT
	public:
		explicit AuthMemberListWnd(model::CloudFileInfo&info, QWidget*parent = NULL);
		virtual  ~AuthMemberListWnd();
		QVector<qint64> getMemberList();
	protected:
		void paintEvent(QPaintEvent *event);
	public	slots:
		void onCancelBtnClicked();
		void onOkBtnClicked();
		void onAddMemClicked();
		void onClose();
	signals:
		void signalAddMember();
		void signalAuthMembers(std::vector<model::TeamMemberInfo>&);
		void signalConfirm();
	private:
		AuthMemListWidget* m_authMemList;
		QLabel* m_title;
		QHBoxLayout* m_buttonlayout;
		QHBoxLayout* m_btnAddLayout;
		QVBoxLayout* m_mainlayout;
		PushButton* m_addMember;
		QPushButton* m_ok;
		QPushButton* m_cancelBtn;
		TitleBar*	m_titleBar;;
	};
}