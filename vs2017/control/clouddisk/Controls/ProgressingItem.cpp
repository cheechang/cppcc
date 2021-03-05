#include "ProgressingItem.h"
#include "QClickLabel.h"
#include "PushButton.h"
#include "MyLineEdit.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QEvent>
#include <QKeyEvent>
#include <QProgressBar>
#include "MyMessageBox.h"
#include <QFileInfo>
#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QProcess>
namespace ui{
	ProgressingItem::ProgressingItem(QWidget *parent) :QWidget(parent)
		, m_progress(nullptr)
		, m_pauseBtn(nullptr)
		, m_cancelBtn(nullptr)
	,m_row(-1)
	, m_pro(0)
	, m_localId(0)
	{
		setMouseTracking(true);

		//m_pauseBtn = new PushButton(this);
		m_cancelBtn = new PushButton(this);
		m_mainlayout = new QHBoxLayout(this);
		m_progress = new QProgressBar(this);

		m_progress->setFixedSize(120,16);
		m_progress->setMinimum(0);
		m_progress->setMaximum(100);
		m_progress->setTextVisible(true);
		//m_pauseBtn->setPicName(QString(":/img/pause"));
		m_cancelBtn->setPicName(QString(":/img/quit"));
		 

		//m_pauseBtn->setToolTip(QString::fromUtf8("暂停")); //上传
		m_cancelBtn->setToolTip(tr("取消"));  //取消

		//m_pauseBtn->setObjectName("pausebtn");
		m_cancelBtn->setObjectName("quitbtn");

		m_mainlayout->setSpacing(5);
		m_mainlayout->setContentsMargins(3, 0, 3, 0);
		m_mainlayout->setAlignment(Qt::AlignCenter);
		m_mainlayout->addWidget(m_progress);
		m_mainlayout->addWidget(m_cancelBtn);
		m_mainlayout->addStretch();
		this->setLayout(m_mainlayout);

		connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(onCancel()));
		//取消
		
	}
	ProgressingItem::~ProgressingItem(){

	}
	void ProgressingItem::setItemRow(int row){
		m_row = row;
	}
	int ProgressingItem::getItemRow()const{
		return m_row;
	}
	void ProgressingItem::setProgress(int32 pro, int64 localId, std::string& filename){
		if (!m_localId){
			m_localId = localId;
		}
		if (m_localId == localId){
			m_progress->setValue(pro);
			if (pro == 100){
				//m_pauseBtn->setVisible(false);
				m_cancelBtn->setVisible(false);
				if (!filename.empty()){
					emit signalPath(QString::fromStdString(filename), localId);
					emit display(2, localId);
				}
			}
		}
	}
	void ProgressingItem::onProgress(int32 proval, int64 localid, std::string& filename){
		setProgress(proval, localid, filename);
	}
	void ProgressingItem::onCancel(){
		emit signalCancel(m_localId);
		emit display(1, m_localId);
	}
}