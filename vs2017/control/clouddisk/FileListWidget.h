#pragma once
#include <QWidget>
#include <model/Packet.h>
#include "Common/Common.h"
#include "Common/EncryptKey.h"
class QPainter;
class QVBoxLayout;
class QHBoxLayout;
class QStackedWidget;
namespace ui{
	class ToolButton;
	class TableWidget;

	class LocalSearchLineEdit;
	class QClickLabel;
	class DefaultWidget;
	class CreateFolderWindow;
class FileListWidget : public QWidget
{
	Q_OBJECT
public:
	explicit FileListWidget(FileType type,QWidget *parent = 0);
	~FileListWidget();
	void addFolder(model::CloudFileInfo&fileinfo);
	void insertFolder(model::CloudFileInfo&info);
	void setFileCount(int count);
	void setFolderInfo(int type, model::CloudFileInfo info);
	void setFolderPermission(model::CloudPermission&permission, model::CloudFileInfo info);
	void clearData();
	void setStartLoadingAnimate();
	void setStopLoadingAnimate();
	void setNoFileTip();
	void refreshList(bool isrefreshcur=false);
	void restorePermission();
	void clearTipLabelData();
	void initPermission(int type);
	void sortDescByTime();
	void updateFileName(QString&newname);
	qint64 getSharedDirOwnerId()const;
signals:
	void signalGetFolderFiles(int type, model::CloudFileInfo info);
	void signalGetFolderPermission(int type, model::CloudFileInfo info);
	void signalSpaceInfo(QString&, QString&, int&);
	void signalRename(qint64 fileid, QString&newname);
	void signalDelFile(std::vector<std::string>&, int);
	void sigalCreateFolder(model::CloudAddFileInfo&, int);
	void signalSearchFiles(QString&, int);
	void signalUpLoadFile(model::CloudUploadFileInfo&, QString);
	void signalDown(model::CloudFileInfo,QString name, int64 localId);
	void signalAuthorMgr(model::CloudFileInfo);
	void signalUpdateName(QString&);
protected slots:
	void onClicked(model::CloudFileInfo data);
	void onCreateFolder();
	void onDelFile(std::vector<std::string>&hashcode);
	void onDealCreateFolder(QString&foldername);
	void onSearchFile(QString&key);
	void onRefreshList();
	void onGetFolderPermission(int type, model::CloudFileInfo info);
	void onUpLoadFile();
	void onDownload(model::CloudFileInfo );
private:
	void getFolderOperate(int type, model::CloudFileInfo info,bool ispermission = true);
private:
	EncryptKey m_encryptKey;
	CreateFolderWindow* m_createfolderwin;
	DefaultWidget* m_defaultWidget;
	DefaultWidget* m_defaultListTip;
	QStackedWidget* m_stackWidget;
	QClickLabel* m_parentLabel;
	ToolButton* m_uploadbtn;
	ToolButton* m_createfolderbtn;
	QClickLabel* m_returnLabel;
	QClickLabel* m_vspliter;
	QClickLabel* m_allFileLabel;
	QClickLabel* m_rightLabel;
	LocalSearchLineEdit* m_search;
	TableWidget* m_fileList;
	QHBoxLayout* m_labelLayout;
	QHBoxLayout* m_tipLayout;
	QHBoxLayout* m_pBtnLayout;
	QVBoxLayout* m_mainLayout;

	QList<QSharedPointer<QClickLabel>> m_tipLabelList;
	bool m_isFirstFlag;
private:
	qint64 m_userid;
	qint64 m_firstSharedOwnerId; //保存一级目录文件文件夹拥有者id
	model::CloudPermission m_permisson;
	model::CloudFileInfo m_currentfolder;
};
}


