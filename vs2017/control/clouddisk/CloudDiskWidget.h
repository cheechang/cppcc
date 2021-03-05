#pragma once
#include "Controls/TWidget.h"
#include "Common/ServiceDefine.h"
#include <qsharedpointer.h>
#include <model/Packet.h>
class QStackedWidget;
class QHBoxLayout;
class QVBoxLayout;
namespace ui{
	class TitleBar;
	class LeftWidget;
	class DefaultWidget;
	class FileListWidget;
	class ProgressWindow;
	class AuthMemberListWnd;
	class CloudDiskUploadWnd;
	class AuthMemberSelWnd;
	struct UpInfo{
		model::CloudUploadFileInfo info;
		int type;
		QString rootname;
		int64 localId;
		int64 sdklocalId;
	};
	struct DownInfo{
		model::CloudFileInfo info;
		int type;
		QString rootname;
		int64 localId;
		int64 sdklocalId;
		std::string filename;
	};
	class CloudDiskWidget :public TWidget{
		Q_OBJECT
	public:
		CloudDiskWidget(QWidget *parent = NULL);
		~CloudDiskWidget();
		void ShowUploadSelectDirWnd(QString&filePath,QString&encrptkey);
		void ShowAuthorMemSelWnd();
		void ShowWindow();
		void ReFreshData();
		void ReInitData();
		void decryptFile(std::string encryptKey, QString filePath, QString fileName, QString&outPath, QString inCachePath);
		int  ParseUpdateJson(QString json, model::CloudFileInfo& info);
		QString getDecryptFilePath(QString cacheDirPath, QString fileName);
		bool IsFileExist(QString path);
	protected:
		QString getUploadName(qint64 id);
		void    showTipMessageBox(int code);
	signals:
		void signalSerQueryFolder(service::ErrorInfo, std::vector<model::CloudFileInfo>&, int,int64);
		void signalSerGetPermission(service::ErrorInfo, model::CloudPermission&, model::CloudFileInfo,int);
		void signalSerCreateFolder(service::ErrorInfo,model::CloudFileInfo&,int);
		void signalSerRename(service::ErrorInfo, std::string&);
		void signalSerDelFile(service::ErrorInfo,int);
		void signalSerSearchFiles(service::ErrorInfo, std::vector<model::CloudFileInfo>&, int);
		void signalSerUploadFileResult(service::ErrorInfo, const std::string&, int64);
		void signalSerUploadFileProgress(int32, int32, const std::string&, int64);
		void signalSerDownloadResult(service::ErrorInfo, int64, model::CloudFileInfo);
		void signalSerDownloadProgress(int32 extra_req, int32 progress, const std::string& info, int64 localId,std::string& );
		void signalSerDownCancelRlt(service::ErrorInfo);
		void signalSerUpCancelRlt(service::ErrorInfo);
		void signalUpFail(int64);
		void signalDownFail(int64);
		void signalDecryptFile(int64, model::CloudFileInfo&, std::string&);
		void signalSerOperUser(const model::Account& userInfo);
	public slots:
	    void onShowCloudDiskWnd();
		void onSignalDown(model::CloudFileInfo data, QString name, int64 localId);
		void onSelfBtnClicked();
		void onShareBtnClicked();
		void onGetFolderFiles(int type,model::CloudFileInfo info);
		void onGetFolderPermission(int type,model::CloudFileInfo info);
		void onRename(qint64 fileid,QString&newname);
		void onDelFile(std::vector<std::string>&hascodes,int type);
		void onCreateFolder(model::CloudAddFileInfo&data,int type);
		void onSearchFiles(QString&key, int type);
		void onUpLoadFile(model::CloudUploadFileInfo&, QString);
		void onUpClose();
		void onDownClose();
		void onDownCancel(int64 localid);
		void onUpCancel(int64 localid);
		void onUpRetry(int64 localid);
		void onDownRetry(int64 localid);
		void onAuthorMgr(model::CloudFileInfo);
		void onShowAuthorMemSelWnd();
		void onSerOperUser(const model::Account& userInfo);
	protected slots:
	void onSerQueryFolder(service::ErrorInfo err, std::vector<model::CloudFileInfo>&folderlist, int type, int64 fileid);
		void onSerGetPermission(service::ErrorInfo err, model::CloudPermission&permission,model::CloudFileInfo info,int type);
		void onSerCreateFolder(service::ErrorInfo err, model::CloudFileInfo&info,int type);
		void onSerRename(service::ErrorInfo err, std::string&newname);
		void onSerDelFile(service::ErrorInfo err,int type);
		void onSerSearchFiles(service::ErrorInfo err, std::vector<model::CloudFileInfo>&files, int type);
		void onSerUploadFileResult(service::ErrorInfo, const std::string&, int64);
		void onSerUploadFileProgress(int32, int32, const std::string&, int64);
		void onSerDownloadResult(service::ErrorInfo, int64, model::CloudFileInfo);
		void onSerDownloadProgress(int32 extra_req, int32 progress, const std::string& info, int64 localId, std::string&);
		void onSerDownCancelRlt(service::ErrorInfo);
		void onSerUpCancelRlt(service::ErrorInfo);
	private:
		//std::shared_ptr<TitleBar> m_titleBar;
		std::shared_ptr<TitleBar> m_titleBar;
		std::shared_ptr<LeftWidget> m_leftWidget;
		std::shared_ptr<DefaultWidget> m_defaultWidget;
		std::shared_ptr<FileListWidget> m_myselfWidget;
		std::shared_ptr<FileListWidget> m_sharedWidget;
		std::shared_ptr<QStackedWidget> m_rightWidget;
		std::shared_ptr<CloudDiskUploadWnd> m_uploadWnd;
		std::shared_ptr<AuthMemberSelWnd> m_authorSelWnd;
		QHBoxLayout* m_contentLayout;
		QVBoxLayout* m_mainLayout;
		std::shared_ptr<ProgressWindow> m_progressTip;
		std::shared_ptr<ProgressWindow> m_downloadWnd;
		std::shared_ptr<AuthMemberListWnd> m_authMemberListWnd;

		int32 m_extrareq;
	private:
		bool     m_isFirstFlag;
		qint64   m_userid;
		QString  m_username;
		IContactService_Ptr m_contactservice;
		ICloudService_Ptr m_cloudservice;
		IUserService_Ptr  m_userservice;
		IFileService_Ptr m_fileservice;
		IConfigService_Ptr m_config;
		std::vector<UpInfo> CloudUpInfos;
		std::vector<DownInfo> CloudDownInfos;
		std::string m_filePath;
	};
}
