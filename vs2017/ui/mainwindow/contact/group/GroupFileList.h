#pragma once

#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <data/ContactData.h>
#include <data/ChatData.h>
#include "controls/TWidget.h"
#include "interface/Defines.h"
#include "common/Controlptr.h"
#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QAction>
#include "common/UIUtils.h"
#include <QPushButton>
#include <QFileDialog>
#include <QDesktopServices>
#include "json.h"
//#include "../control/chatmgrcontrol/EncryptKey.h"

namespace ui
{
	class FriendListWidgetItem;
	class GroupFileListItem;
	class GroupFileList : public TWidget
	{
		Q_OBJECT
	public:
		GroupFileList(QWidget *parent = CNull);
		~GroupFileList();
		void updateData(int64 groupId);
		void AddDataToList(QString filepath,int64 filelocalid);
		//void AddDataToList(QString filepath,int64 filelocalid);

		std::string convertFileSize(double size);

		void sleep(int n);
	protected:
		void contextMenuEvent(QContextMenuEvent *ev);
		bool isGroupOwner();
		//void DelFileResult(int code);
		void onSerProgress(int32, int32, const std::string&);
		void UpFileFinish(QString filepaths,QString fileurl);
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&);
		void signalSerGetGroupFiles(int, std::vector<CSharedPtr<data::FileInfo>>&);
		void signalSerUpfile(QString FilePaht,QString);
		void signalSerFileProgress(qint32 progress);
		void signalSerGetProgress(int32, int32, const std::string&, QString, int64);
		void signalSerDelGroupfile(int64 code, QListWidgetItem* item);
		void signalSerDelUiFile(int64);
		void signalSerSendFile(int, int64, const std::string&,QString,int64);
		void signalSerCancelFile(int, QListWidgetItem* item,int);
	public slots:
		void onSerSendFile(int err, int64 targetId,
			const std::string& fileJson,QString filepath,int64 filelocalid/*, std::vector<std::string> files,
			Json::Value arrFiles, unsigned int time*/);
		void onSerGetGroupFiles(int code, std::vector<CSharedPtr<data::FileInfo>>& files);
		void onSerDelFile();
		void onSerCancelFile();
		//void onSerSetFileProgress(qint32 progress);
		void onSerUpFile();
		void onSerGetProgress(int32, int32, const std::string&, QString, int64);
		void onSerDelGroupfile(int64 code, QListWidgetItem* item);
		void onSerCancelFile(int code, QListWidgetItem* item,int);
	private:
		int addItemToList(const data::FileInfo& data);
		int insertItemToList(const data::FileInfo& data,int64 filelocalid);
		bool clearList();
		void SetCurrentFileList(int64 Groupid);
		
		IGroupMgrControl_Ptr m_pGroupControl;
		IChatMgrControl_Ptr m_pChatControl;
		QMap<int64, data::FileInfo> m_mapData;
		QMap<int64, QString> m_FilePathMap;
		QMap<int64, GroupFileListItem*> m_fileListItem;

		QVBoxLayout* m_fileLayout;
		QWidget* m_FileWidget;
		//QListWidget* m_pListWidget;
		QStackedWidget* m_fileStackWidget;
		QMap<int64, QListWidget*> m_pListWidgetMap;
		QHBoxLayout* m_FuncLayout;
		QVBoxLayout* m_pMainLayout;
		QWidget* Funcwidget;
		QLabel* mlblBg;
		int64 m_groupId;
		int64 m_curItemId;

		QPushButton*  m_btnBottomUpFile;

		CSharedPtr<QMenu> popMenu;
		std::shared_ptr<QAction> m_delaction;
		std::shared_ptr<QAction> m_cancelaction;
	};
}
