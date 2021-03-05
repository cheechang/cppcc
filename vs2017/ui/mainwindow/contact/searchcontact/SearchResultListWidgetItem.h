#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include "controls/TWidget.h"
#include "controls/ElidedLabel.h"
#include "interface/Defines.h"
namespace ui{
	class HeadImage;
	class ToolButton;
	class PushButton;
	class SearchResultListWidgetItem : public TWidget
	{
		Q_OBJECT
	public:
		SearchResultListWidgetItem(QWidget *parent=CNull,int64 id = 0);
		~SearchResultListWidgetItem();

		void setData(QString head,QString name,bool IsShowAddBtn=true);
		void setHead(QString head);
		void setName(QString name);
		void setExistInfo(QString tipInfo);
		void setAddBtnText(QString txt);

		int64 id(){return m_id;};
		void setId(int64 id){m_id = id;};
		QString name (){return m_lblName->text();}
		QString head();
protected slots:
		void onAddBtnClicked();
signals:
		void signalAddContactBtnClicked(int64 targetId, void* itemWidget);
	protected:
		CSharedPtr<QPushButton> m_btnAdd;
		CSharedPtr<QLabel> m_isExistLbl;
		CSharedPtr<ElidedLabel> m_lblName;
		CSharedPtr<HeadImage> m_imgHead;
		CSharedPtr<QHBoxLayout> m_hMainLayout;
		CSharedPtr<QVBoxLayout> m_vLayout;
		int64                        m_id;
	};
}

