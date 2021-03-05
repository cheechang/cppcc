#include "LocalSearchLineEdit.h"
#include <QEvent>
#include <QKeyEvent>
namespace ui{
	LocalSearchLineEdit::LocalSearchLineEdit(QWidget *parent,bool setfocus)
		: TWidget(parent)
	{
		mShowSetFocus = setfocus;
		mSearchLineEdit = new QLineEdit(this);
		mSearchLineEdit->setObjectName("localsearch");
		connect(mSearchLineEdit,SIGNAL(textChanged(const QString &)),this,SIGNAL
			(textChanged(const QString &)));

		mBtnDel = new PushButton(mSearchLineEdit);
		mBtnDel->setPicName(":/chat/delete");
		mBtnDel->move(220,9);
		mBtnDel->setFixedSize(12, 12);
		connect(mBtnDel,SIGNAL(clicked()),this,SIGNAL(clearBtnClicked()));

		///mMainLayout = new QVBoxLayout();
		////mMainLayout->addWidget(mSearchLineEdit);
		///mMainLayout->setContentsMargins(10,0,0,0);
		////setLayout(mMainLayout);

		this->installEventFilter(this);
		this->setMouseTracking(true);
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
		///if (mMainLayout)
		///{
		////	delete mMainLayout;
		///}
	}

	void LocalSearchLineEdit::clearText()
	{
		mSearchLineEdit->setText("");
	}

	bool LocalSearchLineEdit::eventFilter( QObject *obj, QEvent *e )
	{
		if(e->type() == QEvent::Show){
			if (mShowSetFocus)
			{
				mSearchLineEdit->setFocus();
			}
		}else if(e->type() == QEvent::MouseButtonPress){
			emit clearBtnClicked();
		}
		if(e->type() == QEvent::KeyPress){
			QKeyEvent *event = static_cast<QKeyEvent*>(e);
			if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)  
			{ 
				event->accept();
				return true;
			}
		}
		return TWidget::eventFilter(obj,e);
	}

	void LocalSearchLineEdit::setPlaceholderText( QString text )
	{
		mSearchLineEdit->setPlaceholderText(text);
	}

	QString LocalSearchLineEdit::text()
	{
		return mSearchLineEdit->text();
	}

}
