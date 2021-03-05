#ifndef TRAYUNREADMSGTIPWIN_H
#define TRAYUNREADMSGTIPWIN_H
#include "../core/BaseDialog.h"
#include "../contact/group/GroupListItemWidget.h"
#include "interface/Defines.h"
#include "common/Controlptr.h"
#include <QWidget>
#include <QListWidget>
class ElidedLabel;
namespace ui{
	class MyQPushButton;
	class TWidget;
	class HeadImage;
	class UnreadMsgLabel;
	class TrayUnreadMsgTipWidgetItem :public TWidget{
		Q_OBJECT
	public:
		TrayUnreadMsgTipWidgetItem(QWidget*parent = 0);
		void setData(QString head,QString name,QString unreadMsgCount,int64 targetId);
		int64 id(){return mTargetId;}
	signals:
		void ignoreMsg(int64 targetId);
    protected slots:
		void onBtnIgnoreMsg();
	protected:
        virtual void enterEvent(QEvent *e);
		virtual void leaveEvent(QEvent *e);

		UnreadMsgLabel* mMsgCount;
		ElidedLabel* mName;
		HeadImage*mAvatar;
		int64 mTargetId;
		MyQPushButton* mBtnIgnore;
	};
	class TrayUnreadMsgTipWin : public BaseDialog
	{
		Q_OBJECT
	public:
		static TrayUnreadMsgTipWin* Instance();
		static void showWin(int x);
		static void hideWin();
		void RemoveAllItems();
		void setWinSize();
		static bool isRrayFlash;

		~TrayUnreadMsgTipWin();
	signals:
		void trayMsgClicked(int64 targetId);
		void showMainWin();
	    void signalNotifyTrayFlash(bool);
	public slots:
		void onNoticeTrayMsgTip(CSharedPtr<data::ChatInfo>&chat);
		void onItemClicked(QListWidgetItem*item);
		void onNoticeTrayMsgUpdateReaded(int64 targetId);
		void onIgnoreAllMsg();
		void onBtnIgnoreMsg(int64 targetId);
	protected:
		void mouseMoveEvent(QMouseEvent *event);
		virtual void paintEvent(QPaintEvent *event);

		void removeItem( int64 targetId );
		void updateTitleText();
	private:
		TrayUnreadMsgTipWin(QWidget *parent=CNull);
	    static TrayUnreadMsgTipWin* mPInstance;

		QLabel* mTitle;
		MyQPushButton* mBtnIgnoreAll;
		QListWidget* mMsgListWidget;
		static const int ItemHeight = 40;
		QMap<int64,CSharedPtr<data::ChatInfo>> mMsgDatas;
	};
}

#endif // TRAYUNREADMSGTIPWIN_H
