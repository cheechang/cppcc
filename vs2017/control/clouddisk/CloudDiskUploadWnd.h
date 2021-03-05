#pragma once
#include <qdialog.h>
#include "Common/ServiceDefine.h"
class QVBoxLayout;
class QHBoxLayout;
class QStackedWidget;
class QPushButton;
class QTreeWidgetItem;
namespace ui{
	class TitleBar;
	class MyTreeWidget;
	class DefaultWidget;
	class CloudDiskUploadWnd :public QDialog{
		Q_OBJECT
	public:
		explicit CloudDiskUploadWnd(QString&filepath,QString&encrptkey=QString(""),QWidget*parent = nullptr);
		virtual  ~CloudDiskUploadWnd();
	signals:
		void signalShowCloudDiskWnd();
		void signalUpLoadFile(model::CloudUploadFileInfo&, QString);
		void signalSerQueryFolder(service::ErrorInfo, std::vector<model::CloudFileInfo>&);
		void signalSerGetNetFolder(service::ErrorInfo, std::vector<model::CloudFileInfo>&,QTreeWidgetItem* item);
	protected slots:
		void onSerQueryFolder(service::ErrorInfo err, std::vector<model::CloudFileInfo>&folderlist);
		void onSerGetNetFolder(service::ErrorInfo err, std::vector<model::CloudFileInfo>&folderlist,QTreeWidgetItem* item);
	public slots:
		void onGetNetFolder(QTreeWidgetItem* item, model::CloudFileInfo& info);
		void onOkBtnClicked();
		void onCancelBtnClicked();
	protected:
		void paintEvent(QPaintEvent *event);
	private:
		TitleBar*		m_title;
		MyTreeWidget*	m_tree;
		QPushButton*		m_okBtn;
		QPushButton*		m_cancelBtn;
		DefaultWidget*  m_default;
		QStackedWidget*   m_stack;
		QHBoxLayout*	m_hlayout;
		QVBoxLayout*	m_mainlayout;
	private:
		QString			  m_encrptkey;
		QString           m_filePath;
		qint64			  m_userid;
		ICloudService_Ptr m_cloudservice;
		IUserService_Ptr  m_userservice;
	};
}