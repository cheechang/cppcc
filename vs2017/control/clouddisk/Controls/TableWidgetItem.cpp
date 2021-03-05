#include "TableWidgetItem.h"
#include "QClickLabel.h"
#include "PushButton.h"
#include "MyLineEdit.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QEvent>
#include <QKeyEvent>
#include <QTextCodec>
#include <qdebug.h>
#include <qtimer.h>
#include "../Utils/utils.h"
#include "../Common/Common.h"
namespace ui{
	model::CloudPermission  TableWidgetItem::m_permission;
	TableWidgetItem::TableWidgetItem(QWidget *parent) :QWidget(parent)
	, m_checkBox(nullptr)
	, m_foldericon(nullptr)
	, m_name(nullptr)
	, m_dowanloadBtn(nullptr)
	, m_viewfile(nullptr)
	, m_mainlayout(nullptr)
	, m_row(-1)
	, m_isowner(false)
	, m_iseditnameokbtn(false)
	{
		setMouseTracking(true);
		m_checkBox = new QCheckBox(this);
		m_foldericon = new QLabel(this);
		m_name = new MyLineEdit(this);
		m_okBtn = new PushButton(this);
		m_cancelBtn = new PushButton(this);
		m_dowanloadBtn = new PushButton(this);
		m_authormgrBtn = new PushButton(this);
		m_fromtip = new QLabel(this);
		m_fromName = new QLabel(this);
		m_viewfile = new PushButton(this);
		m_mainlayout = new QHBoxLayout(this);
		m_renameLayout = new QHBoxLayout(this);
		m_fromLayout = new QHBoxLayout(this);
		m_namecontentLayout = new QVBoxLayout(this);

		m_name->setFixedSize(220,20);
		m_foldericon->setScaledContents(true);
		m_foldericon->setFixedSize(QSize(35,35));
		m_foldericon->setPixmap(QPixmap(":/img/folder"));

		m_okBtn->setPicName(QString(":/img/okbtn"));
		m_cancelBtn->setPicName(QString(":/img/cancelbtn"));
		m_dowanloadBtn->setPicName(QString(":/img/download"));
		m_viewfile->setPicName(QString(":/img/viewfile"));
		m_authormgrBtn->setPicName(QString(":/img/author"));


		m_dowanloadBtn->setToolTip(tr("下载"));
		m_authormgrBtn->setToolTip(tr("授权管理"));
		m_viewfile->setToolTip(tr("查看文件"));
		m_fromtip->setText(tr("来自:"));
		m_fromtip->setFixedHeight(15);
		m_fromName->setFixedHeight(15);

		m_fromtip->setObjectName("fromtip");
		m_fromName->setObjectName("fromname");
		m_dowanloadBtn->setObjectName("downloadbtn");
		m_viewfile->setObjectName("viewfilebtn");
		m_authormgrBtn->setObjectName("authormgrbtn");
		m_checkBox->setObjectName("checkbtn");
		//m_checkBox->setDisabled(true);
		m_checkBox->setVisible(true);

		m_okBtn->setVisible(false);
		m_cancelBtn->setVisible(false);
		m_dowanloadBtn->setVisible(false);
		m_viewfile->setVisible(false);
		m_authormgrBtn->setVisible(false);


		m_renameLayout->setSpacing(0);
		m_renameLayout->setContentsMargins(0, 0, 0, 0);
		m_renameLayout->setAlignment(Qt::AlignLeft);
		m_renameLayout->addWidget(m_name);
		m_renameLayout->addWidget(m_okBtn);
		m_renameLayout->addWidget(m_cancelBtn);
		m_renameLayout->addStretch();

		m_fromLayout->setSpacing(0);
		m_fromLayout->setContentsMargins(0, 0, 0, 0);
		m_fromLayout->setAlignment(Qt::AlignLeft);
		m_fromLayout->addWidget(m_fromtip);
		m_fromLayout->addWidget(m_fromName);
		m_fromLayout->addStretch();

		m_namecontentLayout->setSpacing(3);
		m_namecontentLayout->setContentsMargins(0, 0, 0, 0);
		m_namecontentLayout->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		m_namecontentLayout->addLayout(m_renameLayout);
		m_namecontentLayout->addLayout(m_fromLayout);

		m_mainlayout->setSpacing(5);
		m_mainlayout->setContentsMargins(5, 0, 5, 0);
		m_mainlayout->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		m_mainlayout->addWidget(m_checkBox);
		m_mainlayout->addWidget(m_foldericon);
		m_mainlayout->addLayout(m_namecontentLayout);
		m_mainlayout->addStretch();
		m_mainlayout->addWidget(m_dowanloadBtn);
		m_mainlayout->addWidget(m_authormgrBtn);
		m_mainlayout->addWidget(m_viewfile);
		setLayout(m_mainlayout);

		//重命名
		connect(m_name, SIGNAL(signalClicked()), this, SLOT(onRename()));
		connect(m_name, SIGNAL(signalFocusOut()), this, SLOT(onCancelEdit()));
		connect(m_okBtn, SIGNAL(clicked()), this, SLOT(onRenameOkBtnClicked()));
		connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(onRenameCancelBtnClicked()));
		connect(m_dowanloadBtn,SIGNAL(clicked()),this,SLOT(onDownLoadBtnClick()));
		connect(m_authormgrBtn, SIGNAL(clicked()), this, SLOT(onGetAuthorMgrClick()));
		connect(m_checkBox, SIGNAL(clicked()), this, SLOT(onCheckBtnClicked()));
		connect(m_viewfile, SIGNAL(clicked()), this, SLOT(onViewBtnClicked()));
	}
	TableWidgetItem::~TableWidgetItem(){

	}
	void TableWidgetItem::setItemRow(int row){
		m_row = row;
	}
	int TableWidgetItem::getItemRow()const{
		return m_row;
	}
	void TableWidgetItem::setItemData(model::CloudFileInfo&data, int type){
		m_data = data;
		if (1 == data.fileType){
			QString icon = getFileIcon(QString::fromUtf8(data.fileSuffix.data()));
			m_foldericon->setPixmap(icon);
		}
		else{
			if (1 == type){
				m_foldericon->setPixmap(QPixmap(":/img/folder"));
			}
			else{
				m_foldericon->setPixmap(QPixmap(":/img/teamfolder"));
			}
			
		}
		QString fileName = QString::fromUtf8(data.fileName.c_str());
		fileName = utils::webUnicodeToString(fileName);
		QString fileSuffix = QString::fromUtf8(data.fileSuffix.c_str());
	
		if (!fileSuffix.isEmpty()){
			fileName += QString(".");
			fileName += fileSuffix;
		}
		QString fromname = QString::fromUtf8(data.uploaderName.data());
		m_fromName->setText(fromname);
		m_name->setElidedText(fileName);
		m_name->setToolTip(fileName);
		m_name->setCursorPosition(0);
	}
	model::CloudFileInfo TableWidgetItem::getItemData()const{
		return m_data;
	}
	void TableWidgetItem::setItemPermission(model::CloudPermission&permission){
		m_permission = permission;
	}
	bool TableWidgetItem::isOwner()const{
		return m_isowner;
	}
	void TableWidgetItem::setIsOwner(bool isowned){
		m_isowner = isowned;
	}
	bool TableWidgetItem::isRootNode()const{
		return (SHARED_FILE_ROOT_PID==m_data.pid ? true : false);
	}
	model::CloudPermission TableWidgetItem::getItemPermission(){
		return m_permission;
	}
	QString TableWidgetItem::getFileIcon(QString fileSuffix)
	{
		//文件类型 0.未知文件类型 1.图片 2.word 3.execl 4.ppt 5.视频 6.安装文件 7.压缩文件 8.文本文件 9.pdf
		QString strImageName = "";
		QString strFileExtension = "";
		strFileExtension = fileSuffix.toLower();
		if (0 == strFileExtension.compare("txt"))
		{
			strImageName = QString(":/img/txt");
		}
		else if ((0 == strFileExtension.compare("doc")) || (0 == strFileExtension.compare("docx")))
		{
			strImageName = QString(":/img/word");
		}
		else if ((0 == strFileExtension.compare("xls")) || 0 == strFileExtension.compare("xlsx"))
		{
			strImageName = QString(":/img/execl");
		}
		else if ((0 == strFileExtension.compare("png")) || (0 == strFileExtension.compare("bmp"))
			|| (0 == strFileExtension.compare("jpg")) || (0 == strFileExtension.compare("xpm"))
			|| (0 == strFileExtension.compare("gif")) || (0 == strFileExtension.compare("jpeg"))
			|| (0 == strFileExtension.compare("ico")) || (0 == strFileExtension.compare("tiff")))
		{
			strImageName = QString(":/img/picture");
		}
		else if ((0 == strFileExtension.compare("ppt")) || (0 == strFileExtension.compare("pptx")))
		{
			strImageName = QString(":/img/ppt");
		}
		else if ((0 == strFileExtension.compare("rar")) || (0 == strFileExtension.compare("zip")))
		{
			strImageName = QString(":/img/package");
		}
		else if ((0 == strFileExtension.compare("avi")) || (0 == strFileExtension.compare("3gp"))
			|| (0 == strFileExtension.compare("rmvb")) || (0 == strFileExtension.compare("wav"))
			|| (0 == strFileExtension.compare("flv")) || (0 == strFileExtension.compare("rm"))
			|| (0 == strFileExtension.compare("wmv")) || (0 == strFileExtension.compare("mkv"))
			|| (0 == strFileExtension.compare("mov")) || (0 == strFileExtension.compare("raw"))
			|| (0 == strFileExtension.compare("wma")) || (0 == strFileExtension.compare("amr"))
			|| (0 == strFileExtension.compare("mp4")) || (0 == strFileExtension.compare("mp3"))
			)
		{
			strImageName = QString(":/img/play");
		}
		else if ((0 == strFileExtension.compare("exe")))
		{
			strImageName = QString(":/img/install");
		}
		else if ((0 == strFileExtension.compare("pdf")))
		{
			strImageName = QString(":/img/pdf");
		}
		else
		{
			strImageName = QString(":/img/unknown");
		}
		return strImageName;
	}
	void TableWidgetItem::onRename(){
		setEnableRename(true);
	}
	void TableWidgetItem::onDelFile(){
		emit signalDelFile();
	}
	void TableWidgetItem::onRenameOkBtnClicked(){
		QString newname("");
		QString oldname("");
		m_iseditnameokbtn = true;
		newname = m_name->text();
		if (!newname.isEmpty()){
			emit signalRename(m_data.fileId, newname);
			QString fileSuffix = QString::fromUtf8(m_data.fileSuffix.c_str());
			if (!fileSuffix.isEmpty()){
				newname += QString(".");
				newname += fileSuffix;
			}
			m_name->setElidedText(newname);
			m_name->setToolTip(newname);
		}
		setEnableRename(false);
	}
	void TableWidgetItem::onRenameCancelBtnClicked(){
		if (m_iseditnameokbtn){
			m_iseditnameokbtn = false;
			return;
		}
		QString fileName = QString::fromUtf8(m_data.fileName.c_str());
		fileName = utils::webUnicodeToString(fileName);
		QString fileSuffix = QString::fromUtf8(m_data.fileSuffix.c_str());
		if (!fileSuffix.isEmpty()){
			fileName += QString(".");
			fileName += fileSuffix;
		}
		m_name->setElidedText(fileName);
		setEnableRename(false);
	}
	void TableWidgetItem::setEnableRename(bool enabled){
		if (nullptr == m_name) return;
		m_okBtn->setVisible(enabled);
		m_cancelBtn->setVisible(enabled);
		m_fromtip->setVisible(!enabled);
		m_fromName->setVisible(!enabled);
		m_name->setReadOnly(!enabled);
		if (enabled){
			QString fileSuffix = QString::fromUtf8(m_data.fileSuffix.c_str());
			QString filename = m_name->text();
			filename.replace(QString(".") + fileSuffix, "");
			filename.replace(QString(".") + fileSuffix.toUpper(), "");
			m_name->setFixedSize(220,30);
			m_name->setElidedText(filename);
			m_name->setFocus();
			m_name->selectAll();
		}
		else{
			m_name->setFixedSize(220, 20);
			m_name->clearFocus();
			m_name->deselect();
		}
	}
	void TableWidgetItem::onDownLoadBtnClick(){
		emit signalDownLoad(m_data);
	}
	void TableWidgetItem::onCheckBtnClicked(){
		bool ischecked = !m_checkBox->isChecked();
		m_checkBox->setChecked(ischecked);
		emit signalItemClicked(m_item);
	}
	void TableWidgetItem::onGetAuthorMgrClick(){
		emit signalAuthorMgr(m_data);
	}
	void TableWidgetItem::onViewBtnClicked(){
		emit signalViewFile(m_data);
	}
	void TableWidgetItem::onUpdateName(QString&newname){
		m_data.fileName = newname.toUtf8().data();
	}
	void TableWidgetItem::onCancelEdit(){
		QTimer::singleShot(200, this, SLOT(onRenameCancelBtnClicked()));
	}
	void TableWidgetItem::setTableItem(QTableWidgetItem* item){
		m_item = item;
	}
}