#include "LocalSearchLineEdit.h"
#include <QEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QDebug>
namespace ui{
	LocalSearchLineEdit::LocalSearchLineEdit(FileType type, QWidget *parent)
		: TWidget(parent)
	{
		setMouseTracking(true);
		mSearchLineEdit = new QLineEdit(this);
		mSearchLineEdit->setMouseTracking(true);
		mSearchLineEdit->setObjectName("localsearch");
		connect(mSearchLineEdit,SIGNAL(textChanged(const QString &)),this,SIGNAL
			(textChanged(const QString &)));
		mSearchLineEdit->setFixedSize(220,30);

		if (SELF_FILE == type){
			mSearchLineEdit->setPlaceholderText(tr("搜索:输入文件名"));
		}
		else{
			mSearchLineEdit->setPlaceholderText(tr("搜索:输入文件名"));
		}
		connect(mSearchLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(onTextChanged(const QString&)));
		
		mBtnDel = new PushButton(mSearchLineEdit);
		mBtnDel->setPicName(":/img/delete");
		mBtnDel->setFixedSize(20, 20);
		mBtnDel->move(180, 5);
		mBtnDel->setVisible(false);
		connect(mBtnDel, SIGNAL(clicked()), this, SLOT(onDelBtnClicked()));

		mBtnSearch = new PushButton(mSearchLineEdit);
		mBtnSearch->setPicName(":/img/search");
		mBtnSearch->move(200, 5);
		connect(mBtnSearch, SIGNAL(clicked()), this, SLOT(onSearchBtnClicked()));

		mMainLayout = new QVBoxLayout();
		mMainLayout->addWidget(mSearchLineEdit);
		mMainLayout->setContentsMargins(10,0,0,0);
		setLayout(mMainLayout);

		installEventFilter(mSearchLineEdit);
		installEventFilter(this);
		
	}

	LocalSearchLineEdit::~LocalSearchLineEdit()
	{
		if(mBtnDel){
			delete mBtnDel;
		}
		if (mSearchLineEdit)
		{
			delete mSearchLineEdit;
		}
		if (mMainLayout)
		{
			delete mMainLayout;
		}
	}

	void LocalSearchLineEdit::clearText()
	{
		mSearchLineEdit->setText("");
	}

	bool LocalSearchLineEdit::eventFilter( QObject *obj, QEvent *e )
	{
		if(e->type() == QEvent::Show){
			//mSearchLineEdit->setFocus();
		}
		else if(e->type() == QEvent::MouseButtonPress){
			emit clearBtnClicked();
		}
		else if(e->type() == QEvent::KeyPress){
			QKeyEvent *event = static_cast<QKeyEvent*>(e);
			if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)  
			{ 
				onSearchBtnClicked();
				event->accept();
				return true;
			}
		}
		return TWidget::eventFilter(obj,e);
	}
	void LocalSearchLineEdit::paintEvent(QPaintEvent *event){
		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
		p.setBrush(QBrush(QColor(242,242,243)));
		p.setPen(QColor(242, 242, 243));  //边框色
		p.drawRoundedRect(QRect(0, 0, this->width(), this->height()),15,15);
	}
	void LocalSearchLineEdit::onSearchBtnClicked(){
		QString key = mSearchLineEdit->text();
		if (key.isEmpty()){
			return;
		}
		emit signalSearchFile(key);
	}
	void LocalSearchLineEdit::onDelBtnClicked(){
		clearText();
	}
	void LocalSearchLineEdit::onTextChanged(const QString &text){
		if (text.isEmpty()){
			mBtnDel->setVisible(false);
			emit signalRefreshList();
		}
		else{
			mBtnDel->setVisible(true);
		}
	}
}
