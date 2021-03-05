#ifndef GROUPLISTITEMWIDGET_H
#define GROUPLISTITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "controls/TWidget.h"
#include "interface/Defines.h"
namespace ui{
	class HeadImage;
	class ToolButton;
	class GroupListItemWidget : public TWidget
	{
		Q_OBJECT
	public:
		GroupListItemWidget(QWidget *parent=CNull,int64 id = 0);
//		GroupListItemWidget(QWidget * parent, int64 id);
		~GroupListItemWidget();

		void setData(QString head,QString name,bool isShowHaremMaster=false,bool isVSign=false, int groupType = 0);
		void setHead(QString head);
		void setName(QString name);
		void setShowHaremMaster(bool isShow, QString tooltip = "");
		void setGroupType(int type, QString tooltip = "");
		void showItemAsTeam(QString itemName);
		void setHeadGray(bool isGray);
		void setAvaterSize(QSize size);
		int64 id(){return m_id;};
		QString name (){return m_lblName->text();}
		QString head();
		void setId(int64 id){m_id = id;};
		void SetVGroupSignVisible(bool IsVisible);
	signals:
		void showGroupInforPage(int64 groupId);
		void headClicked(int64 id);
	protected slots:
		void onHeadClicked();
	protected:
		CSharedPtr<QLabel> m_lblName;
		CSharedPtr<HeadImage> m_imgHead;
		CSharedPtr<ToolButton> m_VSign;
		CSharedPtr<ToolButton> m_lblHaremMaster;
		CSharedPtr<ToolButton> m_pLabelOrg;
		CSharedPtr<QHBoxLayout> m_hMainLayout;
		CSharedPtr<QWidget> mLineWidget;
		int64                        m_id;
	};
}

#endif // GROUPLISTITEMWIDGET_H
