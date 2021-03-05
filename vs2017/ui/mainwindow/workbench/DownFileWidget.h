#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMap>
#include <QLabel>
#include <QTabWidget>
#include <QListWidget>
#include <QProgressBar>
#include <QGridLayout>
#include <interface/Defines.h>
#include "json.h"
#include "../contact/createGroup/BaseWindow.h"

namespace ui{
	class ToolButton;
	class DownFileWidgetListItem : public QWidget
	{
		Q_OBJECT
		public:
			DownFileWidgetListItem(QWidget *parent = CNull);
			~DownFileWidgetListItem();
		public:
			QString getFileType(QString fileName);
			std::string convertFileSize(double size);
			void setdata(QString name, QString filepath,qint64 FileSize);
			void SetOpenFileVisible(bool isTrue);
		signals:
			void signalSersetProgress(qint64, qint64);
		public slots:
			void onSersetProgress(qint64, qint64);
			void openFileDir();
		private:
			CSharedPtr<QLabel> m_FileIocnLbl;
			CSharedPtr<QLabel> m_NameLbl;
			CSharedPtr<QProgressBar> m_pProgressBar;
			CSharedPtr<QLabel> m_pLabelSize;
			CSharedPtr<QLabel> m_pLabelTime;
			//CSharedPtr<QVBoxLayout> m_pMainLayout;
			CSharedPtr<QGridLayout> m_pMainLayout;
			ToolButton* m_pButtonOpenFile;
		
			QString mFilePath;
	};

	class DownFileWidget : public BaseWindow
	{
		Q_OBJECT
	public:
		DownFileWidget(QWidget *parent = CNull);
		~DownFileWidget();

	public:
		bool FileIdIsExit(int32 id);
		void SetMap(int32 id, QString FilePath);
		void SetItemWidget(int32, DownFileWidgetListItem*);
		DownFileWidgetListItem* GetItemWidget(int32 id);
		void EraserMap(int32 id);
		void SetData(QString Name, int32 id, QString filepath, qint64 filesieze);
		QString GetFilePath(int32 id);
	signals:
		void setProgress(qint64, qint64);
		bool signalSerOpenChatWidget(int64 targetid);
	public slots:

	private:
		CSharedPtr<QListWidget> m_DownFileList;
		CSharedPtr<QVBoxLayout> m_Vlayout;
		CSharedPtr<QWidget> m_Widget;
		std::map<int32, QString> m_DownFileMap;
		std::map<int32, DownFileWidgetListItem*> m_ItemwidgetMap;
	};
}