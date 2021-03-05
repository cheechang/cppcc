#pragma once
#include<QWidget>
#include <model/Packet.h>
#include "Common/ServiceDefine.h"
class QLabel;
class QHBoxLayout;
class QLineEdit;
class QTableWidgetItem;
class QProgressBar;
namespace ui{
	class QClickLabel;
	class PushButton;
	class MyLineEdit;
	class SuccessItem : public QWidget
	{
		Q_OBJECT
	public:
		explicit SuccessItem(QWidget *parent = 0);
		~SuccessItem();
		bool decryptFile(std::string encryptKey, QString filePath, QString fileName, QString&outPath, QString inCachePath);
		QString getDecryptFilePath(QString cacheDirPath, QString fileName);
		bool IsFileExist(QString path);
	public slots:
		void onOpenDir();
		void onOpenFile();
		void onGetpath(QString,int64);
		void onDecryptFile(int64, model::CloudFileInfo&, std::string&);
	private:
		QLabel*	m_progress; // 进度
		QClickLabel* m_openDir;
		QClickLabel* m_openFile;
		QHBoxLayout*	m_mainlayout;
		QString m_filePath;
		int64 m_localId;

	private:
		int m_row; //保存item在列表中的行数
		int32 m_pro;
		IFileService_Ptr m_fileservice;
	};
}