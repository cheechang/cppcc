#ifndef GROUPATSELECTLISTWIDGET_H
#define GROUPATSELECTLISTWIDGET_H
#include <qwidget.h>
#include <QDialog>
#include <ui/common/Connect.h>
#include <ui/common/Controlptr.h>
#include <utils/common.h>
#include <ui/common/PageSizeDataItem.hpp>

class QListWidget;
class QListWidgetItem;
class QVBoxLayout;
class QHBoxLayout;
namespace uicontrols{
	class Label;
	class BaseQListWidget;
	class AvatarWidget;
}
namespace ui{
	class GroupAtWidgetItem:public QWidget{
		Q_OBJECT
	public:
		GroupAtWidgetItem(QWidget* parent = NULL);
		void setData(int64 id,QString name,QString avatar);
		int64 id();
		QString name();
	signals:
		void clicked(int64 id);	
	protected:
		virtual void mousePressEvent(QMouseEvent *);

		int64 memId;
		QString mName;
		uicontrols::Label* mWidget;
		uicontrols::AvatarWidget*m_pHead;
	};
	class GroupAtSelectListWidget : public QWidget
	{
		Q_OBJECT
	public:
		enum LIST_SIZE{
			WIDTH=360,
			Max_Height=200
		}; 

		GroupAtSelectListWidget(QWidget *parent=NULL);
		~GroupAtSelectListWidget();
		void showWin(int64 groupId,QPoint pos,QString regText="");
		void clearData();
	signals:
		void signalSerGetGroupMems(QString regText, int, std::vector<CSharedPtr<data::Member>>&, int64 localId);
		void memInfo(QString path);
		void dataFinish();
	protected slots:
	void onSerGetGroupMems(QString regText, int code, std::vector<CSharedPtr<data::Member>>&mems, int64 localId);
		void onItemClicked(QListWidgetItem *item);
		void onItemClicked(int64 id );
		void onKeyPressed(QEvent *event);
		void onLazyLoadMember();
	protected:
		void makeImg(QListWidgetItem* item);
		void setData( std::vector<MemberPtr > &mems, QString &regText );
		void moveWinPos();
		void addItem(MemberPtr&data);
		void addItems();

		virtual void focusOutEvent(QFocusEvent *);

		uicontrols::BaseQListWidget*mListWidget;
		QVBoxLayout* mainLayout;
		IGroupMgrControl_Ptr mGroupCtrl;
		IChatMgrControl_Ptr  mChatCtrl;
		IUserControl_Ptr mUserCtrl;
		std::vector<MemberPtr > mMems;
		int64 mGroupId;
		int64 mUserId;
		QPoint mPos;
		int64 m_reqLocalId;

		PageSizeDataItem<MemberPtr> m_memberpage;
	};
}
#endif // GROUPATSELECTLISTWIDGET_H
