#pragma once
#include "controls/TWidget.h"
#include <common/Controlptr.h>

class QLabel;
class QPushButton;
class QVBoxLayout;
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QDialog>  
#include <QNetworkAccessManager>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPushButton>
#include <QVBoxLayout>
#include <QIODevice>
#include <QFileInfo>
#include <QProgressBar>


namespace ui{
	class DownloadDialog : public QDialog
	 {
	Q_OBJECT
 		public:
			DownloadDialog(QWidget *parent = 0);
			~DownloadDialog();

			void Download(QString url, QString localFile);

			QUrl m_url;
			QString m_localfile;
			void UrlDownload();
			QString m_fileMD5;
		protected slots:
			void httpDownload();
			void replyFinished(QNetworkReply*reply);
			void onDownloadProgress(qint64 bytesSent, qint64 bytesTotal);
			void onReadyRead();//  
			void stop();//暂停，重新下载  
				
		private:
			QPushButton *download_Btn;
			QPushButton *stop_Btn;
			QProgressBar *progressBar;
			QFile *file;
			QFileInfo fileInfo;
			QNetworkAccessManager *accessManager;
			QNetworkRequest request;
			QNetworkReply *reply;
			QVBoxLayout *layout;
			bool httpRequestAbort; //请求停止的标志位,false表示允许请求  
	};






	class AboutInfo :	public TWidget
	{
        Q_OBJECT
	public:
		AboutInfo(QWidget* parent);
		~AboutInfo(void);
    public slots:
        void onBtnCheckUpClicked();
    protected:
		void InitWidgets();
	private:
		CSharedPtr<QLabel>   m_labImage;
		CSharedPtr<QLabel>	 m_labName;
		CSharedPtr<QLabel>   m_labVersion;
        CSharedPtr<QPushButton> m_btnCkeckUp;
		CSharedPtr<QVBoxLayout> m_mainLayout;
        IUpdateControl_Ptr      m_updateServer;
        IUserControl_Ptr        m_userServer;
        IAuthControl_Ptr        m_autherServer;

	public:
		void GetVersionInfo();
		QNetworkAccessManager *m_httpManager;
		QNetworkRequest       *m_httRrequest;
	public slots:
		void onSerUnicomRepResult(QNetworkReply* preplay);



	public:
		void  DownloadPkg(QString v_id);
		QNetworkAccessManager *m_httpManagerDown;
		QNetworkRequest       *m_httRrequestDown;

		QNetworkReply *reply;

		DownloadDialog *m_downloadDlg;
	public slots:
		void onDownloadResult(QNetworkReply* preplay);

	};
};

	


