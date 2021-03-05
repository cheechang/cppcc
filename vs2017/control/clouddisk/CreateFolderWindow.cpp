#include "CreateFolderWindow.h"
#include "Controls/TitleBar.h"
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <QPainter>
#include <log.h>
namespace ui{
	CreateFolderWindow::CreateFolderWindow(QWidget*parent) :QDialog(parent)
	,m_title(nullptr)
	,m_edit(nullptr)
	,m_ok(nullptr)
	,m_cancel(nullptr)
	,m_btnLayout(nullptr)
	,m_mainlayout(nullptr)
	{
		//LOG_METHOD("CreateFolderWindow::CreateFolderWindow", LOG_FILE);
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->resize(300, 100);

		m_title = new TitleBar(this,true,false,true);
		m_edit = new QLineEdit(this);
		m_ok = new QToolButton(this);
		m_cancel = new QToolButton(this);
		m_label = new QLabel(this);
		m_contentlayout = new QVBoxLayout();
		m_btnLayout = new QHBoxLayout();
		m_mainlayout = new QVBoxLayout(this);

		m_title->setFixedSize(300,30);
		installEventFilter(m_title);
		setWindowTitle(tr("创建文件夹"));
		setWindowIcon(QIcon(":/img/logo"));

		m_edit->setMaxLength(32);
		m_edit->setFixedSize(200,30);

		m_edit->setObjectName("createfolderedit");
		m_ok->setObjectName("blueToolButton");
		m_cancel->setObjectName("grayToolButton");
		m_edit->setFocus();

		m_ok->setFixedSize(75,25);
		m_cancel->setFixedSize(75,25);

		m_ok->setText(tr("确定"));
		m_cancel->setText(tr("取消"));
		m_label->setText(tr("请输入文件夹名:"));

		m_btnLayout->setAlignment(Qt::AlignRight);
		m_btnLayout->setContentsMargins(5, 5, 5, 10);
		m_btnLayout->setSpacing(15);
		m_btnLayout->addStretch();
		m_btnLayout->addWidget(m_ok);
		m_btnLayout->addWidget(m_cancel);

		m_contentlayout->setAlignment(Qt::AlignCenter);
		m_contentlayout->setContentsMargins(5, 5, 5, 5);
		m_contentlayout->setSpacing(5);
		m_contentlayout->addWidget(m_label);
		m_contentlayout->addWidget(m_edit);

		m_mainlayout->setAlignment(Qt::AlignTop);
		m_mainlayout->setContentsMargins(0, 0, 0, 0);
		m_mainlayout->setSpacing(10);
		m_mainlayout->addWidget(m_title);
		m_mainlayout->addLayout(m_contentlayout);
		m_mainlayout->addLayout(m_btnLayout);
		setLayout(m_mainlayout);

		connect(m_ok, SIGNAL(clicked()), this, SLOT(onOkBtnClicked()));
		connect(m_cancel, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
	}
	CreateFolderWindow::~CreateFolderWindow(){

	}
	void CreateFolderWindow::paintEvent(QPaintEvent *event)
	{
		//LOG_METHOD("CreateFolderWindow::paintEvent", LOG_FILE);
		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
		p.setBrush(QBrush(Qt::white));
		p.setPen(Qt::gray);  //边框色
		p.drawRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
	}
	void CreateFolderWindow::onOkBtnClicked(){
		//LOG_METHOD("CreateFolderWindow::onOkBtnClicked", LOG_FILE);
		QString foldername = m_edit->text();
		if (foldername.isEmpty()){
			//todo提示不能为空
			return;
		}
		emit signalCreateFolder(foldername);
		this->close();
	}
	void CreateFolderWindow::onCancelClicked(){
		//LOG_METHOD("CreateFolderWindow::onCancelClicked", LOG_FILE);
		this->close();
	}
}