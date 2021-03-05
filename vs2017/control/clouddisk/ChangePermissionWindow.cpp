#include "ChangePermissionWindow.h"
#include "Controls/TitleBar.h"
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <QPainter>
#include <QSignalMapper>
namespace ui{
	ChangePermissionWindow::ChangePermissionWindow(std::vector<model::CloudRoleInfo>& info,QWidget*parent) :QDialog(parent)
	,m_title(nullptr)
	,m_mainlayout(nullptr)
	{
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->resize(150, 120);

		m_title = new TitleBar(this,false,false,true);
		m_contentlayout = new QVBoxLayout();
		m_mainlayout = new QVBoxLayout(this);

		m_title->setFixedSize(150,30);
		installEventFilter(m_title);
		setWindowTitle(tr("更改权限"));
		setWindowIcon(QIcon(":/img/logo"));


		m_contentlayout->setAlignment(Qt::AlignCenter);
		m_contentlayout->setContentsMargins(5, 5, 5, 5);
		m_contentlayout->setSpacing(5);

		QSignalMapper *signal_mapper = new QSignalMapper(this);
		for (int i = 0; i<info.size(); i++)
		{
			QToolButton *tool_button = new QToolButton(this);
			QString rolename = QString::fromUtf8(info.at(i).name.c_str());
			QString dealRoleName = tool_button->fontMetrics().elidedText(rolename, Qt::ElideRight,90);
			tool_button->setObjectName("authorbtn");
			tool_button->setFixedSize(100,25);
			tool_button->setText(dealRoleName);
			connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
			signal_mapper->setMapping(tool_button, QString::number(info.at(i).roleId));
			m_contentlayout->addWidget(tool_button);
			m_buttonlist.append(tool_button);
		}
		connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(onBtnClicked(QString)));
		m_mainlayout->setAlignment(Qt::AlignTop);
		m_mainlayout->setContentsMargins(0, 0, 0, 10);
		m_mainlayout->setSpacing(10);
		m_mainlayout->addWidget(m_title);
		m_mainlayout->addLayout(m_contentlayout);
		setLayout(m_mainlayout);
	}
	ChangePermissionWindow::~ChangePermissionWindow(){
		if (nullptr != m_contentlayout){
			m_contentlayout->deleteLater();
		}
	}
	void ChangePermissionWindow::paintEvent(QPaintEvent *event)
	{
		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
		p.setBrush(QBrush(Qt::white));
		p.setPen(Qt::gray);  //边框色
		p.drawRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
	}
	void ChangePermissionWindow::onBtnClicked(QString roleid){
		emit signalChangePerm(roleid.toInt());
		this->close();
	}
}