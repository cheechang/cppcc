#include "TitleBar.h"
#include "PushButton.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <log/log.h>
#include <ui/common/Common.h>
//#ifdef _WIN32
//	#pragma comment(lib, "user32.lib")
//	#include <qt_windows.h>
//#endif
namespace uicontrols{
	TitleBar::TitleBar(QWidget *parent, bool showMinbtn, bool showMaxBtn, bool showCloseBtn)
	:ui::TWidget(parent), m_ismove(true),m_Drag(false),m_BackImg(""),m_isSelfdeal(false),m_WindowRadius(0),
	m_WindowMargin(0),m_isMax(false),m_windowNormalSize(QSize(0,0)),m_backColor(QColor(Qt::white))
	{
		setFixedHeight(40);
		m_pIconLabel = new QLabel(this);
		m_pTitleLabel = new QLabel(this);
		m_pMinimizeButton = new ui::PushButton(this);
		m_pMaximizeButton = new ui::PushButton(this);
		m_pCloseButton = new ui::PushButton(this);
		m_pAdvanceSetButton = new ui::PushButton(this);

		m_pIconLabel->setFixedSize(20, 20);
		m_pIconLabel->setScaledContents(true);

		m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

		m_pAdvanceSetButton->setFixedSize(20, 20);
		m_pMinimizeButton->setFixedSize(20, 20);
		m_pMaximizeButton->setFixedSize(20, 20);
		m_pCloseButton->setFixedSize(20, 20);

		m_pTitleLabel->setObjectName("whiteLabel");
		m_pMinimizeButton->setObjectName("minimizeButton");
		m_pMaximizeButton->setObjectName("maximizeButton");
		m_pCloseButton->setObjectName("closeButton");
		

		QHBoxLayout *pLayout = new QHBoxLayout(this);
		pLayout->addWidget(m_pIconLabel);
		pLayout->addSpacing(5);
		pLayout->addWidget(m_pTitleLabel);
		pLayout->addStretch();
		pLayout->addWidget(m_pAdvanceSetButton);
		pLayout->addWidget(m_pMinimizeButton);
		pLayout->addWidget(m_pMaximizeButton);
		pLayout->addWidget(m_pCloseButton);
		pLayout->setSpacing(0);
		pLayout->setContentsMargins(5, 0, 0, 0);
		pLayout->setAlignment(Qt::AlignVCenter);
		setLayout(pLayout);

		if (!m_isSelfdeal){
			connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
			connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
			connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
		}
		else{
			connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SIGNAL(signalMin()));
			connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SIGNAL(signalMax()));
			connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SIGNAL(signalClose()));
			connect(m_pAdvanceSetButton, SIGNAL(clicked(bool)), this, SIGNAL(signalAdvanceSet()));
		}
		m_pMinimizeButton->setVisible(showMinbtn);
		m_pMaximizeButton->setVisible(showMaxBtn);
		m_pCloseButton->setVisible(showCloseBtn);
		m_pCloseButton->setFocus();
	}
	TitleBar::~TitleBar()
	{

	}
	void TitleBar::setSelfDealBtnEvent(bool isSelfdeal){
		m_isSelfdeal = isSelfdeal;
		disconnect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
		disconnect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
		disconnect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
		if (!isSelfdeal){
			connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
			connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
			connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
		}
		else{
			connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SIGNAL(signalMin()));
			connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SIGNAL(signalMax()));
			connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SIGNAL(signalClose()));
			connect(m_pAdvanceSetButton, SIGNAL(clicked(bool)), this, SIGNAL(signalAdvanceSet()));
		}
	}
	void TitleBar::setWindowMove(bool ismove){
		m_ismove = ismove;
	}
	void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		if (!m_isSelfdeal && m_pMaximizeButton->isVisible()){
			m_pMaximizeButton->click();
		}
		else
		{
			emit signalMax();
		}
		event->accept();
	}
	void TitleBar::mousePressEvent(QMouseEvent *event)
	{
		//LOG_METHOD("TitleBar::mousePressEvent", LOG_FILE);
		QWidget *pWindow = this->window();
		if (event->button() == Qt::LeftButton && 0 !=pWindow && pWindow->isTopLevel()){
			//#ifdef _WIN32
			//	if (ReleaseCapture())
			//	{
			//		if (0 !=pWindow && pWindow->isTopLevel() && m_ismove)
			//		{
			//			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
			//		}
			//	}
			//#else
				Log(LOG_LEV_DEBUG, LOG_FILE,"[ ****** mousePressEvent**********]");
				m_Drag = true;
				m_DragPosition = event->globalPos() - pWindow->pos();
			//#endif
			event->ignore();
		 }
	}
	void TitleBar::mouseMoveEvent(QMouseEvent *event)
	{
		//LOG_METHOD("TitleBar::mouseMoveEvent", LOG_FILE);
//#ifdef _WIN32
//		event->accept();
//#else
	   QWidget *pWindow = this->window();
	   if(m_Drag && (event->buttons() && Qt::LeftButton && pWindow->isTopLevel())) {
		   Log(LOG_LEV_DEBUG, LOG_FILE,"[ ****** mouseMoveEvent**********]");
		   pWindow->move(event->globalPos() - m_DragPosition);
		   event->accept();
		}
//#endif
		
	}

	void TitleBar::mouseReleaseEvent(QMouseEvent*event)
	{
		//LOG_METHOD("TitleBar::mouseMoveEvent", LOG_FILE);
//#ifdef _WIN32
//		event->ignore();
//#else
		m_Drag = false;
//#endif
	}

	bool TitleBar::eventFilter(QObject *obj, QEvent *event)
	{
		switch (event->type())
		{
		case QEvent::WindowTitleChange:
		{
				QWidget *pWidget = qobject_cast<QWidget *>(obj);
				if (pWidget)
				{
					m_pTitleLabel->setText(pWidget->windowTitle());
					return true;
				}
		}
		case QEvent::WindowIconChange:
		{
				QWidget *pWidget = qobject_cast<QWidget *>(obj);
				if (pWidget)
				{
					QIcon icon = pWidget->windowIcon();
					m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
					return true;
				}
		}
		case QEvent::MouseMove:
			{
			   return true;				   
			}
		case QEvent::WindowStateChange:
		case QEvent::Resize:{
			updateMaximize();
			emit signalWindowSizeChanged();
			return true;
		}
		case QEvent::KeyPress:{
			QKeyEvent *eventKey = static_cast<QKeyEvent*>(event);  
			if(eventKey->key() == Qt::Key_Return || eventKey->key() == Qt::Key_Enter){
				event->accept();
				return true;
			}
		}
	}

		return QWidget::eventFilter(obj, event);
}

	void TitleBar::onClicked()
	{
		QPushButton *pButton = qobject_cast<QPushButton *>(sender());
		QWidget *pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			if (pButton == m_pMinimizeButton && m_pMinimizeButton->isVisible())
			{
				if(m_isSelfdeal){
					emit signalMin();
				}
				else{
					pWindow->showMinimized();
				}
			}
			else if (pButton == m_pMaximizeButton && m_pMaximizeButton->isVisible())
			{
				if(m_isSelfdeal){
					emit signalMax();
				}
				else{
						QRect screenrect = QApplication::desktop()->availableGeometry();
						if(m_isMax)
						{
							int x = screenrect.x() + (screenrect.width()-m_windowNormalSize.width()) / 2;
							int y = screenrect.y() + (screenrect.height()-m_windowNormalSize.height()) / 2;
							pWindow->setGeometry(x,y,m_windowNormalSize.width(),m_windowNormalSize.height());
							m_isMax = false;
						}
						else{
							m_windowNormalSize = pWindow->size();
							pWindow->setGeometry(-SHADOW_WIDTH,-SHADOW_WIDTH,screenrect.width()+2*SHADOW_WIDTH,screenrect.height()  +2*SHADOW_WIDTH);
							m_isMax = true;
						}
				}
				emit signalMaxStateChanged(m_isMax);
				pWindow->show();
			}
			else if (pButton == m_pCloseButton && m_pCloseButton->isVisible())
			{
				if(m_isSelfdeal){
					emit signalClose();
				}
				else{
					pWindow->close();
				}
			}
		}
	}

	void TitleBar::updateMaximize()
	{
		QWidget *pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			if (m_isMax)
			{
				m_pMaximizeButton->setProperty("maximizeProperty", "restore");
				m_pMaximizeButton->setObjectName("restoreButton");
			}
			else
			{
				m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
				m_pMaximizeButton->setObjectName("maximizeButton");
			}
			m_pMaximizeButton->setStyle(QApplication::style());
		}
	}
	void TitleBar::paintEvent(QPaintEvent *event)
	{
		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing); 
		if(!m_BackImg.isEmpty()){
			QPixmap pixmap(m_BackImg);
			pixmap = pixmap.scaled(this->width(),this->height());
			p.setBrush(QBrush(pixmap));
		}
		else{
			p.setBrush(QBrush(m_backColor));
		}
		p.setPen(Qt::transparent);
		p.drawRoundedRect(QRect(0,0,this->width(),this->height()/2),WINDOWRADIUS,WINDOWRADIUS);
		p.drawRect(QRect(0,this->height()/2,this->width(),this->height()));
	}
	void TitleBar::setBackGroudImg(QString img)
	{
		m_BackImg = img;
		this->update();
	}
	void TitleBar::setBackGroudColor(QColor color){
		m_backColor = color;
		this->update();
	}
	void TitleBar::setTitleText(QString title){
		m_pTitleLabel->setText(title);
		this->update();
	}
	void TitleBar::setIcon(QString icon){
		m_pIconLabel->setPixmap(QPixmap(icon));
	}
	void TitleBar::setObjectSize(OBJTYPE type,QSize size){
		switch(type)
		{
		case OBJ_TITLE:
			{
			   m_pTitleLabel->setFixedSize(size);
			   break;
			}
		case OBJ_ICON:
			{
			   m_pIconLabel->setFixedSize(size);
			   break;
			}
		case OBJ_MIN:
			{
			   m_pMinimizeButton->setFixedSize(size);
			   break;
			}
		case OBJ_MAX:
			{
			   m_pMaximizeButton->setFixedSize(size);
			   break;
			}
		case OBJ_CLOSE:
			{
			   m_pCloseButton->setFixedSize(size);
			   break;
			}
		case OBJ_ADVANCESET:
			{
				m_pAdvanceSetButton->setFixedSize(size);
				break;
			}
		}
	}
	void TitleBar::setElemObjectName(OBJTYPE type,QString name){
		switch(type)
		{
		case OBJ_TITLE:
			{
			   m_pTitleLabel->setObjectName(name);
			   break;
			}
		case OBJ_ICON:
			{
			   m_pIconLabel->setObjectName(name);
			   break;
			}
		case OBJ_MIN:
			{
			   m_pMinimizeButton->setObjectName(name);
			   break;
			}
		case OBJ_MAX:
			{
			   m_pMaximizeButton->setObjectName(name);
			   break;
			}
		case OBJ_CLOSE:
			{
			   m_pCloseButton->setObjectName(name);
			   break;
			}
		case OBJ_ADVANCESET:
			{
				m_pAdvanceSetButton->setObjectName(name);
				break;
			}
		}
	}
	void TitleBar::setBtnPicName(OBJTYPE type,QString name){
		switch(type)
		{
		case OBJ_MIN:
			{
			   m_pMinimizeButton->setPicName(name);
			   break;
			}
		case OBJ_MAX:
			{
			   m_pMaximizeButton->setPicName(name);
			   break;
			}
		case OBJ_CLOSE:
			{
			   m_pCloseButton->setPicName(name);
			   break;
			}
		case OBJ_ADVANCESET:
			{
				m_pAdvanceSetButton->setPicName(name);
				break;
			}
		}
	}
	void TitleBar::setObjectVisible(OBJTYPE type,bool visible){
		switch(type)
		{
		case OBJ_TITLE:
		{
			 m_pTitleLabel->setVisible(visible);
			 break;
		}
		case OBJ_ICON:
			{
			   m_pIconLabel->setVisible(visible);
			   break;
			}
		case OBJ_MIN:
			{
			   m_pMinimizeButton->setVisible(visible);
			   break;
			}
		case OBJ_MAX:
			{
			   m_pMaximizeButton->setVisible(visible);
			   break;
			}
		case OBJ_CLOSE:
			{
			   m_pCloseButton->setVisible(visible);
			   break;
			}
		case OBJ_ADVANCESET:
			{
				m_pAdvanceSetButton->setVisible(visible);
				break;
			}
		}
	}
	void TitleBar::setBtnToolTip(OBJTYPE type,QString name){
		switch(type)
		{
		case OBJ_MIN:
			{
				m_pMinimizeButton->setToolTip(name);
			   break;
			}
		case OBJ_MAX:
			{
			   m_pMaximizeButton->setToolTip(name);
			   break;
			}
		case OBJ_CLOSE:
			{
			   m_pCloseButton->setToolTip(name);
			   break;
			}
		case OBJ_ADVANCESET:
			{
				m_pAdvanceSetButton->setToolTip(name);
				break;
			}
		}
	}
	void TitleBar::setWindowRadius(qint32 val){
		m_WindowRadius = val;
	}
	void TitleBar::setWindowMargin(qint32 val){
		m_WindowMargin = val;
	}
	QObject* TitleBar::getObj(OBJTYPE type){
		switch(type)
		{
		case OBJ_TITLE:
			{
				return m_pTitleLabel;
			}
		case OBJ_ICON:
			{
				return m_pIconLabel;
			}
		case OBJ_MIN:
			{
				return m_pMinimizeButton;
			}
		case OBJ_MAX:
			{
				return m_pMaximizeButton;
			}
		case OBJ_CLOSE:
			{
				return m_pCloseButton;
			}
		case OBJ_ADVANCESET:
			{
				return m_pAdvanceSetButton;
			}
		}
		return 0;
	}
	void TitleBar::setShowMax(){
		QWidget *pWindow = this->window();
		QRect screenrect = QApplication::desktop()->availableGeometry();
		m_windowNormalSize = pWindow->size();
		pWindow->setGeometry(-SHADOW_WIDTH,-SHADOW_WIDTH,screenrect.width()+2*SHADOW_WIDTH,screenrect.height()  +2*SHADOW_WIDTH);
		//pWindow->setWindowState(Qt::WindowMaximized);
	}
}