#include "CloudDiskUploadWnd.h"
#include "Controls/TitleBar.h"
#include "Controls/MyTreeWidget.h"
#include "Controls/DefaultWidget.h"
#include "Controls/PushButton.h"
#include "Controls/MyTreeWidgetItem.h"
#include "Common\Common.h"
#include <qlayout.h>
#include <qicon.h>
#include <qdatetime.h>
#include <qfileinfo.h>
#include <QPainter>
#include <QStackedWidget>
#include <log.h>
namespace ui{
	CloudDiskUploadWnd::CloudDiskUploadWnd(QString&filepath,QString&encrptkey,QWidget*parent) :QDialog(parent)
	,m_title(nullptr)
	,m_tree(nullptr)
	,m_okBtn(nullptr)
	,m_cancelBtn(nullptr)
	,m_default(nullptr)
	,m_hlayout(nullptr)
	,m_mainlayout(nullptr)
	,m_filePath(filepath)
	,m_encrptkey(encrptkey)
	{
		//LOG_METHOD("CloudDiskUploadWnd::CloudDiskUploadWnd", LOG_FILE);
		setWindowFlags(Qt::FramelessWindowHint);
		setFixedSize(370, 440);

		m_title = new TitleBar(this,false,false,true);
		m_stack = new QStackedWidget(this);
		m_tree = new MyTreeWidget(this);
		m_default = new DefaultWidget(this);
		m_okBtn = new QPushButton(this);
		m_cancelBtn = new QPushButton(this);
		m_hlayout = new QHBoxLayout();
		m_mainlayout = new QVBoxLayout(this);

		m_title->setFixedSize(370,30);
		installEventFilter(m_title);

		setWindowTitle(tr("选择上传目录"));
		setWindowIcon(QIcon(":/img/logo"));

		m_okBtn->setObjectName("blueButton");
		m_cancelBtn->setObjectName("grayButton");

		m_okBtn->setFixedSize(75, 25);
		m_cancelBtn->setFixedSize(75, 25);

		m_okBtn->setText(tr("确定"));
		m_cancelBtn->setText(tr("取消"));

		m_stack->addWidget(m_default);
		m_stack->addWidget(m_tree);
		m_stack->setContentsMargins(20, 10, 0, 10);
		m_stack->setFixedSize(350, 360);
		

		m_hlayout->setAlignment(Qt::AlignRight);
		m_hlayout->setContentsMargins(5, 5, 20, 10);
		m_hlayout->setSpacing(15);
		m_hlayout->addWidget(m_okBtn);
		m_hlayout->addWidget(m_cancelBtn);

		m_mainlayout->setAlignment(Qt::AlignTop);
		m_mainlayout->setContentsMargins(0, 0, 0, 0);
		m_mainlayout->setSpacing(0);
		m_mainlayout->addWidget(m_title);
		m_mainlayout->addWidget(m_stack);
		m_mainlayout->addLayout(m_hlayout);
		m_mainlayout->addStretch();
		setLayout(m_mainlayout);

		m_userservice = USERSERVICE;
		m_cloudservice = CLOUDSERVICE;

		model::Account account;
		m_userservice->getAccountInfo(account);
		m_userid = account.id.value();
		m_stack->setCurrentIndex(0);

		connect(m_okBtn, SIGNAL(clicked()), this, SLOT(onOkBtnClicked()));
		connect(m_cancelBtn, SIGNAL(clicked()),this,SLOT(onCancelBtnClicked()));
		connect(m_tree, SIGNAL(signalGetNetFolder(QTreeWidgetItem*, model::CloudFileInfo&)), this, SLOT(onGetNetFolder(QTreeWidgetItem*, model::CloudFileInfo&)));
		CONNECT_SERVICE(QueryFolder(service::ErrorInfo, std::vector<model::CloudFileInfo>&));
		CONNECT_SERVICE(GetNetFolder(service::ErrorInfo, std::vector<model::CloudFileInfo>&,QTreeWidgetItem*));
		
		m_stack->setCurrentIndex(0);
		//查询跟目录所有文件及文件夹
		m_cloudservice->queryFloder(
									0,
									m_userid,
									std::bind(&CloudDiskUploadWnd::signalSerQueryFolder,
									this,
									std::placeholders::_1,
									std::placeholders::_2));

	}
	CloudDiskUploadWnd::~CloudDiskUploadWnd(){
		//LOG_METHOD("CloudDiskUploadWnd::~CloudDiskUploadWnd", LOG_FILE);
	}
	void CloudDiskUploadWnd::paintEvent(QPaintEvent *event)
	{
		//LOG_METHOD("CloudDiskUploadWnd::paintEvent", LOG_FILE);
		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
		p.setBrush(QBrush(Qt::white));
		p.setPen(Qt::gray);  //边框色
		p.drawRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
	}
	void CloudDiskUploadWnd::onSerQueryFolder(service::ErrorInfo err, std::vector<model::CloudFileInfo>&folderlist){
		//LOG_METHOD("CloudDiskUploadWnd::onSerQueryFolder", LOG_FILE);
		Log(LOG_LEV_INFO,LOG_FILE,"err = %s", err);
		int foldercount = 0;
		if (!err){
			std::vector<model::CloudFileInfo>::iterator index = folderlist.begin();

			for(; index != folderlist.end(); index++)
			//for (auto index : folderlist){
			{
				if (1 != index->fileType && 1 == index->fileId){
					m_tree->addRootItem(*index);
					++foldercount;
				}
			}
		}
		if (!foldercount){
			m_stack->setCurrentIndex(1);
		}
	}
	void CloudDiskUploadWnd::onGetNetFolder(QTreeWidgetItem* item, model::CloudFileInfo& info){
		//LOG_METHOD("CloudDiskUploadWnd::onGetNetFolder", LOG_FILE);
		//查询跟目录所有文件及文件夹
		m_cloudservice->queryFloder(
						info.fileId,
						m_userid,
						std::bind(&CloudDiskUploadWnd::signalSerGetNetFolder,
						this,
						std::placeholders::_1,
						std::placeholders::_2,
						item));
	}
	void CloudDiskUploadWnd::onSerGetNetFolder(service::ErrorInfo err, std::vector<model::CloudFileInfo>&folderlist, QTreeWidgetItem* item){
		//LOG_METHOD("CloudDiskUploadWnd::onSerGetNetFolder", LOG_FILE);
		Log(LOG_LEV_INFO,LOG_FILE,"err = %d", err);
		int foldercount = 0;
		if (!err){

			std::vector<model::CloudFileInfo>::iterator index = folderlist.begin();
			for(; index != folderlist.end(); index++)
			//for (auto index : folderlist){
			{
				if (1 != index->fileType){
					m_tree->addChildItem(item,*index);
					++foldercount;
				}
			}
		}
		if (!foldercount){
			m_stack->setCurrentIndex(1);
		}
	}
	void CloudDiskUploadWnd::onOkBtnClicked(){
		//LOG_METHOD("CloudDiskUploadWnd::onOkBtnClicked", LOG_FILE);
		MyTreeWidgetItem* item = nullptr;
		model::CloudFileInfo data;
		model::CloudUploadFileInfo upload;
		QString rootFolderName("");
		QFileInfo fileInfo(m_filePath);
		QList<QTreeWidgetItem*>list= m_tree->selectedItems();
		if (list.size() > 0){
			item = dynamic_cast<MyTreeWidgetItem*>(list.at(0));
			data = item->getItemData();
			rootFolderName = tr(data.fileName.data());
		}
		upload.fileSize = fileInfo.size();
		upload.localPath = m_filePath.toUtf8().data();
		upload.fileCode = data.fileCode.empty() ? MYSELF_FILE_ROOT_FILECODE:data.fileCode;
		upload.pid = data.pid <= 0 ? MYSELF_FILE_ROOT_PID:data.fileId;
		upload.localId = QDateTime::currentMSecsSinceEpoch();
		upload.isResume = true;
		upload.encryptKey = m_encrptkey.toUtf8().data();
		emit signalUpLoadFile(upload, rootFolderName);
		emit signalShowCloudDiskWnd();
		this->close();
	}
	void CloudDiskUploadWnd::onCancelBtnClicked(){
		//LOG_METHOD("CloudDiskUploadWnd::onCancelBtnClicked", LOG_FILE);
		this->close();
	}
}