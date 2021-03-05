#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "controls/TWidget.h"
#include "interface/Defines.h"

namespace ui{
	class HeadImage;
	class ToolButton;
	class EnterpriseAccountListItem : public TWidget
	{
		Q_OBJECT
	public:
		EnterpriseAccountListItem(QWidget *parent = CNull, int64 id = 0);
		~EnterpriseAccountListItem();

		void setData(QString head,QString name,bool isShowHaremMaster=false);
		void setHead(QString head);
		void setName(QString name);
		void setShowHaremMaster(bool isShow, QString tooltip = "");
		void showItemAsTeam(QString itemName);
		void setHeadGray(bool isGray);

		int64 id(){return m_id;};
		QString name (){return m_lblName->text();}
		QString head();
		void setId(int64 id){m_id = id;};
	signals:
		void showGroupInforPage(int64 groupId);
	protected:
		CSharedPtr<ToolButton> m_lblHaremMaster;
		CSharedPtr<QLabel> m_lblName;
		CSharedPtr<HeadImage> m_imgHead;
		CSharedPtr<QHBoxLayout> m_hMainLayout;
		CSharedPtr<QWidget> mLineWidget;
		int64 m_id;
	};
}
