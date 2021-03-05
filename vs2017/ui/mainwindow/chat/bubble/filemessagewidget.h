#ifndef FILEMESSAGEWIDGET_H
#define FILEMESSAGEWIDGET_H
#include "abstractmessagewidget.h"
#include "controls/TWidget.h"
class ElidedLabel;
class QLabel;
class QGridLayout;
class QHBoxLayout;
class ClickLabel;
class QVBoxLayout;
class QProgressBar;
class FileMessageItem:public ui::TWidget
{
    Q_OBJECT
public:
    explicit FileMessageItem(IChatMgrControl_Ptr& chatcontrol,QWidget* parent = 0);
	~FileMessageItem();
    void setFile(const QString& file);
    QString file() const;

	void setStatus(int status);
	void setLocalId(qint64 localid){
		m_localid = localid;
	}
	void setIsRecv(const bool& val){
		m_isrecv = val;
	}
	void setMedia(const MediaMsgItemInfo&val){
		m_media = val;
	}
	QSize sizeHint() const
	{
		return QSize(300,100);
	}
	void setCloudDisk(bool isClouddisk)
	{
		m_isClouddisk = isClouddisk;
	}

	bool getCloudDisk()
	{
		return m_isClouddisk;
	}

	void DownLoadFile(QString& saveAsPath=QString(""));

	void tipInfoShow(bool isVisble);
signals:
	void signalSerProgressCb(qint64, qint32, qint32, const std::string&);	
	void signalSerDownLoadFile(int,const std::string&,int64);
	void signalDownfileFinish();
protected:
	void translateLanguage();
	void setFileInfo(QString&path);
	void dealtransformat();
	void dealdownload();
	void dealFinish();
	void dealFailed();
	QString getFileType(QString fileName);
	QString EnctrptFile(QString saveaspath=QString(""));
	QString makeFileName(QString localpath, int index = 1);
	QString hasFileInCache(QString localpath);
private slots:
    void openFile();
    void openFileDir();
	void downloadFile();
	void saveAsFile();
	void onSerProgressCb(qint64, qint32, qint32, const std::string&);
	void onSerDownLoadFile(int err,const std::string&filepath, int64 targetId);
private:
	ElidedLabel* m_fileNameLabel;
	QLabel* m_fileSizeLabel;
	QLabel* m_fileIconLabel;
	ElidedLabel* m_fileTip;
	QProgressBar*  m_progress;
	ClickLabel* m_openfile;
	ClickLabel* m_openDir;
	ClickLabel* m_download;
	ClickLabel* m_saveas;
	ClickLabel* m_redownload;
	QGridLayout* m_fileLayout;
	QHBoxLayout* m_btndownloadlayout;
	QHBoxLayout* m_btnfinishlayout;
	QHBoxLayout* m_btnfailedlayout;
	QVBoxLayout* m_mainLayout;
    QString m_file;
	qint64 m_localid;
	bool   m_isrecv;
	bool m_isClouddisk;
	QLabel* m_tipInfo;
	MediaMsgItemInfo m_media;
	IChatMgrControl_Ptr m_chatcontrol;
};
class FileMessageWidget : public AbstractMessageWidget
{
    Q_OBJECT
public:
    explicit FileMessageWidget(QWidget* parent = 0);
    ~FileMessageWidget();

	void setFile(CSharedPtr<data::Msg>&msg);
    void setFile(const QString& file);
    QString file() const;

	void setFileStatus(int status);

    QSize suggestWidth(int width);
signals:
	void onSaveCloudDisk();
protected slots:
	void onSerSendMsg(int err,qint64 msgtime,qint64 msgid,qint64 uiLocalId);
	void onSerCloudDisk();
	void onSerDownfileFinish();
protected:
    void initializeContextActions();
	void dealSendFile(CSharedPtr<data::Msg>&msg);
	void dealHistoryMsg(CSharedPtr<data::Msg>&msg);
private:
	MediaMsgItemInfo m_media;
    class FileMessageWidgetPrivate* d_ptr;
};

#endif // FILEMESSAGEWIDGET_H