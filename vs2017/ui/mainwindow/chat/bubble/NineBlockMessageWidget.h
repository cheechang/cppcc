#ifndef NINEBLOCKMESSAGEWIDGET_H
#define NINEBLOCKMESSAGEWIDGET_H
#include <QLabel>
#include <QGridLayout>
#include <QMouseEvent>
#include "abstractmessagewidget.h"
#include "common/Common.h"
#include "common/Controlptr.h"
enum{
	NINE_IMG_ITEM_SIZE=100,

};
class NineBlockMessageItem:public QWidget{
	Q_OBJECT
public:
	NineBlockMessageItem(IChatMgrControl_Ptr ctrl,int64 targetId,QWidget *parent=0);
	~NineBlockMessageItem();
	void setNineBlockMsg(data::MsgImg&msg);
	QString bigImgPath;
signals:
	void signalSerDownLoadImg(int,const std::string&,int64,int64,const std::string&,bool isSrc);
public slots:
	void onSerDownLoadImg(int err,const std::string& imgname,int64 targetid,int64 localid,const std::string& encrptykey,bool isSrc);
protected:
	void  downLoadImg(std::string&url,bool isSrc);
	QString enctrptFile(std::string&url,std::string&encrptkey,FileDefaultPathType filepath=DATAPATH_USERIMG,FileCachePathType cacheType=DATACACHEPATH_USERIMG);
private:
	QLabel*mlblImage;
	MediaMsgItemInfo m_media;
	IChatMgrControl_Ptr m_chatcontrol;
	int64 mTargetId;
};

class NineBlockMessageWidget : public AbstractMessageWidget
{
	Q_OBJECT
public:
	NineBlockMessageWidget(QWidget *parent=0);
	~NineBlockMessageWidget();
	void setNineBlockMsg(CSharedPtr<data::Msg>&msg);
	QSize suggestWidth(int width);
protected:
	void mouseDoubleClickEvent(QMouseEvent* event);
private:
	QGridLayout* mMainLayout;
	QSize mSize;
	QList<QWidget*>mItems;
};

#endif // NINEBLOCKMESSAGEWIDGET_H
