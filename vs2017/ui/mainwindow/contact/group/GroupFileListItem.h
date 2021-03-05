#pragma once

#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QProgressBar>
#include <data/GroupData.h>
#include "controls/TWidget.h"
#include "common/Controlptr.h"
#include "interface/Defines.h"

namespace ui{

	enum OPERTYPE{
		FILEUPOP,
		FILEDOWNOP,
		FILECANCELUP,
		FILECANCELDOWN
	};

	class ToolButton;
	class GroupFileListItem : public TWidget
	{
		Q_OBJECT
	public:
		GroupFileListItem(QWidget *parent = CNull, int64 id = 0);
		~GroupFileListItem();

		void SetDownOrOpen();
		void setData(const data::FileInfo& file);
		void Setfileurl(std::string url);
		QString GetfileUrl();
		void setNewData(const data::FileInfo& file);
		int64 id(){return m_id;};
		void SetUpFileState(bool IsFinish);
		bool GetUpFileState();
		void setfilelocalid(int64);
		int64 Getfilelocalid();
		QString GetEncryptKey(){ return m_strEncryptKey; };
		bool GetIsDowning(){return isDownding;}
		//QString name (){return m_pLabelName->text();}
		//void setId(int64 id){m_id = id;};
		void setProgressVisible(bool isShow);
		void SetTipVisible(bool istrue,int type);
		void StartTimer(int ntime);
		void SetOperType(OPERTYPE type);
		int GetOperType();
	signals:
		void showGroupInforPage(int64 groupId);
		void signalSerDownLoadFile(int, const std::string&, int64);
		void signalSerProgressCb(qint64, qint32, qint32, const std::string&);

	public slots:
		void downloadFile();
		void openFileDir();
		void onSerDownLoadFile(int err,const std::string& filepath, int64 targetId);
		void onSerProgressCb(qint64, qint32, qint32, const std::string&);
		void onSerFileUpProGress(qint32);
		void onSerSetTip();
	protected:
		QString getFileType(QString fileName);
		QString enctrptFile(QString saveaspath = QString(""));

		IChatMgrControl_Ptr m_pChatControl;

		QGridLayout* m_pMainLayout;
		QLabel* m_pLabelIcon;
		QLabel* m_pLabelName;
		QLabel* m_pLabelSize;
		QLabel* m_pLabelTime;
		QLabel* m_pLabelAuther;
		QLabel* m_fileUptip;
		QLabel* m_fileDowntip;
		QLabel* m_CancelTip;


		ToolButton* m_pButtonDownload;
		ToolButton* m_pButtonOpenFile;
		QProgressBar* m_pProgress;

		int64 m_id;
		int64 m_iFromId;
		QString m_strEncryptKey;
		QString m_strUrl;
		QString m_strFilePath;
		bool FileUpisFinish;
		int64 SendFileLocalId;
		QString m_orgfilepath;
		bool isDownding;
		int opertype;

		QTimer * timer;
	};
}
