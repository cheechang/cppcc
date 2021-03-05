#ifndef MODIFYFRIENDREMARKWINDOW_H
#define MODIFYFRIENDREMARKWINDOW_H

#include <core/BaseDialog.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <interface/Defines.h>
namespace ui{
	class PushButton;
	class ModifyFriendRemarkWindow : public BaseDialog
	{
		Q_OBJECT

	public:
		ModifyFriendRemarkWindow(QWidget *parent=CNull,QString text="");
		~ModifyFriendRemarkWindow();
		void showWin(QString text);
		QString text();
	signals:
		void textChanged(QString text);

	protected slots:
		void onOk();
	private:
		void setAttribute();
		void layout();

		QHBoxLayout*	m_pTitleBtnLayout;		//��������ť����
		QLabel*			m_pBackground;			//����ͼƬ
		PushButton*		m_pCloseButton;			//�ر�
		QLineEdit*      m_pRemarkLineEdit;
		QLabel*			m_pTitle;
		QPushButton*    m_pBtnOk;
	};
}
#endif // MODIFYFRIENDREMARKWINDOW_H
