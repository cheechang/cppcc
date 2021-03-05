#pragma once

#include <core/BaseDialog.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "common/Controlptr.h"
namespace ui{
	class PushButton;
	class SearchResultListWidget;
	class AddContactWindow;
	class SearchContactWindow : public BaseDialog
	{
		Q_OBJECT

	public:
		SearchContactWindow(QWidget *parent=CNull);
		~SearchContactWindow();
	protected slots:
		void onSearchBtnClicked();
		void onLineEditChanged(const QString &text);
		void onClearKeyBtnClicked();
		void onAddContact(const data::SearchResultInfo data);
	protected:
		void keyPressEvent(QKeyEvent * event);
	private:
		void setAttribute();
		void layout();

		QHBoxLayout*	m_pTitleBtnLayout;		//��������ť����
		QVBoxLayout* m_pMainLayout;  
		QLabel*			m_pBackground;			//����ͼƬ
		PushButton*		m_pCloseButton;			//�ر�
		QLineEdit*      m_pKeyLineEdit;
		QLabel*			m_pTitle;
		QPushButton*    m_pBtnSearch;
		PushButton*     m_pClearKeyBtn;
		SearchResultListWidget* m_resultListWidget;
		AddContactWindow* m_addContactWin;
	};
	
}
