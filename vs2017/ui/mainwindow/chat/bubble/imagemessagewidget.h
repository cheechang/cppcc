#ifndef IMAGEMESSAGEWIDGET_H
#define IMAGEMESSAGEWIDGET_H
#include "textmessagewidget.h"
class ElidedLabel;
namespace uicontrols{
	class CircleProgressBar;
}
class ImageMessageWidget : public TextMessageWidget
{
    Q_OBJECT
public:
	enum{
		MinWidthOrHeight = 30
	};
    explicit ImageMessageWidget(QWidget* parent = 0);

    virtual void setImage(MsgDataPtr&msg);
    QString image() const;
	void setPixImage(QString&path);
    QSize suggestWidth(int width);

	virtual void setStatus(const qint32&val);
public slots:
	void onCopyMsg();
	void onSerGetImgMsgs(int code, std::map<int64,data::MsgImg> msg);
	void onSerDownLoadImg(int err,const std::string& imgname,int64 targetid,int64 localid,const std::string& encrptykey,bool isSrc);
	void onSerProgressCb( int32, int32, const std::string&,int64);	
signals:
	void signalSerDownLoadImg(int,const std::string&,int64,int64,const std::string&,bool isSrc);
	void signalSerGetImgMsgs(int, std::map<int64,data::MsgImg>);
	void signalSerProgressCb( int32, int32, const std::string&,int64);	
protected:
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void initializeContextActions();
	void scaledImage(QString sourceImagePath, float scaledWidth, float scaledHeight,QPixmap &outPixmap);
	void scaledImage(QString sourceImagePath, float scaledWidth, float scaledHeight, QString &outImagePath);
	QSize calculateImgSize(int imgWidth,int imgHeight,int containerWidth=260,int containerHeight=280);

	QPixmap loadImgByFormat(QString sourceImagePath);
	void  dealSendMsg(MsgDataPtr&msg);
	void  dealHistoryMsg(MsgDataPtr&msg);
	void  dealImgRecv(MsgDataPtr&msg);
	QSize getImageThumpSize(QString filePath);
	void  getImgBinaryData(QByteArray& imgData, const QString thumbImgPath, const QSize thumbSize);
	void  downLoadImg(std::string&url,bool isSrc);
	QString enctrptFile(std::string&url,std::string&encrptkey,FileDefaultPathType filepath=DATAPATH_USERIMG,FileCachePathType cacheType=DATACACHEPATH_USERIMG);
	void  viewImg(QString&path);

	virtual void paintEvent(QPaintEvent *);

protected:
	MediaMsgItemInfo m_media;
    QString  m_image;
	int64 mWidth;
	int64 mHeight;
	uicontrols::CircleProgressBar*m_progressBar;
	int64 m_localId;
	ElidedLabel*m_contextImgs;
};

#endif // IMAGEMESSAGEWIDGET_H
