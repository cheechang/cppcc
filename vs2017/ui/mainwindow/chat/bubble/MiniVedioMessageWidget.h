#pragma once

#include "abstractmessagewidget.h"
#include "common/Controlptr.h"
#include <QProcess>
#include <Defines.h>
class QHBoxLayout;
class QLabel;
class QVBoxLayout;
class QStackedWidget;
class QMovie;
class QWidget;
class QProgressBar;

namespace ui
{
	class ClickQLabel;
	class PushButton;
	class MiniVedioMessageWidget : public AbstractMessageWidget
	{
		Q_OBJECT
	public:
		MiniVedioMessageWidget(QWidget *parent=CNull);
		~MiniVedioMessageWidget();
		QSize suggestWidth(int width);
		void SetMsg(MsgDataPtr& msg);
		QString enctrptFile(std::string& url, std::string& encrptkey,
			FileDefaultPathType filepath = DATAPATH_USERIMG,
			FileCachePathType cacheType = DATACACHEPATH_USERIMG);

	signals:
		void signalSerDownVedioMsgResult(int code, const std::string& path,
			int64 senderID, bool isSilent);
		void signalSerDownLoadImg(int, const std::string&, int64);
		void singalPlayVideo();

	public slots:
	void onSerDownLoadImg(int err, const std::string& imgname, const int64 targetid);
		void onSerDownVedioMsgResult(int code, const std::string& path,
			int64 senderID, bool isSilent);
		void onSerPlayVideo();
		void onCtrlSilentPlayMenu();
		void onSerDownLoadAduioMsg(std::string url,bool isSrc);
		void PlayFinish();
		void onFormatConvertFinished(int exitCode, QProcess::ExitStatus exitStatus);

	protected:
		void initWidgets();
		void SetSourcePath(std::string pVideopath, std::string pPreImgPath,
			int64 pHight, int64 pWideth, std::string encryptkey);
		QString decryptFile(const std::string& url, std::string& Key);
		void downLoadImg(std::string& url,bool isSrc);
		void setImgBackgroundColor();
		void setLoadVideo();
		void setFinishLoad();
		QString srcConvertMp4(QString srcPath);
		QString GetAviVideoPath(QString pVideoPath);
		void palyMinVideo(bool isSilent=false);
		void dealVideopalyerPro();
		virtual void paintEvent(QPaintEvent *);

	private:
		ClickQLabel* imglabel;
		QLabel* mimgwidget;
		QStackedWidget* mstackwidget;
		QVBoxLayout* mainlayout;
		QVBoxLayout* Videomainlayout;
		QMovie*  moviePlay;
		QProcess* m_process;

		std::string m_strUrl;
		std::string m_strImgUrl;
		std::string m_strVedioPath;
		std::string m_strImgPath;
		std::string m_strCachePath;

		int64 vedioHight;
		int64 vedioWideth;
		std::string encyptkey;

		bool IsSetValue;
		int m_oriWidth;
		//CSharedPtr<MiniVedioMessageWidgetWidget> m_pMinPlayer;
	};
}