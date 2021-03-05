#ifndef LISTWIDGETITEM_H
#define LISTWIDGETITEM_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include "interface/Defines.h"
namespace ui {
	class HeadImage;
	class PushButton;
	class ToolButton;
	class UnreadMsgLabel;
class ListWidgetItem : public QWidget
{
    Q_OBJECT
public:
    explicit ListWidgetItem(int64 targetId,QWidget *parent = CNull);
	void setData(QString strTitle,QString strLastMsg,QString strTime,QString strHeadPath,QString unreadMsg,int count=0,bool isShowAtTip=false);
	void showUnreadMsg();
	void setUnreadCount(QString unreadMsg);
	int64 targetId()const{return mTargetId;}
	void updateHead(QString head);
	void updateName(QString name);
	int  unreadMsgCount(){return mUnreadCount;}
	void setSupportStretch(bool isSupportStretch);
	void setChatTop(bool isTop);
	void setNotDisturb(bool isDisturb);
	int64 msgTime();
	void setMsgTime(int64 time);
signals:
	void signalDelItem(int64 targetId);
	void signalClicked(int64 targetId);
protected:
	void enterEvent(QEvent *e);
	void leaveEvent(QEvent *e);
	void mousePressEvent(QMouseEvent *event);
public slots:
	void onClicked(bool isClick);
private:
    void init();

	CSharedPtr<QLabel> m_lblTitle;
	CSharedPtr<QLabel> m_lblTime;
	CSharedPtr<QLabel> m_lblLasMsg;
	CSharedPtr<HeadImage> m_head;
	CSharedPtr<PushButton> m_btnDel;
	CSharedPtr<UnreadMsgLabel> m_lblUnreadMsg;
	CSharedPtr<QGridLayout> mainLayout;
	CSharedPtr<ToolButton> m_lblChatTop;
	CSharedPtr<ToolButton>m_lblNotDisturb;
	int64 mTargetId;
	int   mUnreadCount;
	int mMsgTime;
};
}

#endif // LISTWIDGETITEM_H
