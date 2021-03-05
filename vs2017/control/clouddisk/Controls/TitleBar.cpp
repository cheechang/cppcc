#include "TitleBar.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QPainter>
#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif
namespace ui{
	TitleBar::TitleBar(QWidget *parent, bool showMinbtn, bool showMaxBtn, bool showCloseBtn,bool isSelfdeal)
	:TWidget(parent), m_ismove(true),m_isSelfdeal(isSelfdeal)
	{
		setFixedHeight(40);
		
		m_pIconLabel = new QLabel(this);
		m_pTitleLabel = new QLabel(this);
		m_pMinimizeButton = new QPushButton(this);
		m_pMaximizeButton = new QPushButton(this);
		m_pCloseButton = new QPushButton(this);



		m_pIconLabel->setFixedSize(20, 20);
		m_pIconLabel->setScaledContents(true);

		m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

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
		pLayout->addWidget(m_pMinimizeButton);
		pLayout->addWidget(m_pMaximizeButton);
		pLayout->addWidget(m_pCloseButton);
		pLayout->setSpacing(0);
		pLayout->setContentsMargins(5, 0, 5, 0);

		setLayout(pLayout);

		if (!isSelfdeal){
			connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
			connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
			connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
		}
		else{
			connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SIGNAL(signalMin()));
			connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SIGNAL(signalMax()));
			connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SIGNAL(signalClose()));
		}

		m_pMinimizeButton->setVisible(showMinbtn);
		m_pMaximizeButton->setVisible(showMaxBtn);
		m_pCloseButton->setVisible(showCloseBtn);
	}
	TitleBar::~TitleBar()
	{

	}
	void TitleBar::setWindowMove(bool ismove){
		m_ismove = ismove;
	}
	void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
	{
		Q_UNUSED(event);
		//emit m_pMaximizeButton->clicked();
		if (!m_isSelfdeal){
			onClicked();
		}
		else
		{
			emit signalMax();
		}
	}
	void TitleBar::mousePressEvent(QMouseEvent *event)
	{
#ifdef Q_OS_WIN
		if (ReleaseCapture())
		{
			QWidget *pWindow = this->window();
			if (pWindow->isTopLevel() && m_ismove)
			{
				SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
			}
		}
		event->ignore();
#else
#endif
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
		case QEvent::WindowStateChange:
		case QEvent::Resize:
			updateMaximize();
			emit signalWindowSizeChanged();
			return true;
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
				pWindow->showMinimized();
			}
			else if (pButton == m_pMaximizeButton && m_pMaximizeButton->isVisible())
			{
				pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
			}
			else if (pButton == m_pCloseButton && m_pCloseButton->isVisible())
			{
				emit signalClose();
				pWindow->close();
			}
		}
	}

	void TitleBar::updateMaximize()
	{
		QWidget *pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			bool bMaximize = pWindow->isMaximized();
			if (bMaximize)
			{
				m_pMaximizeButton->setToolTip(tr("Restore"));
				m_pMaximizeButton->setProperty("maximizeProperty", "restore");
				m_pMaximizeButton->setObjectName("restoreButton");
			}
			else
			{
				m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
				m_pMaximizeButton->setToolTip(tr("Maximize"));
				m_pMaximizeButton->setObjectName("maximizeButton");
			}
			m_pMaximizeButton->setStyle(QApplication::style());
		}
	}
	void TitleBar::paintEvent(QPaintEvent *event)
	{
		TWidget::paintEvent(event);

		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing);  // �����;
		p.setBrush(QBrush("#008CEE"));
		p.setPen(Qt::transparent);  //�߿�ɫ
		p.drawRect(QRect(0, 0, this->width(),this->height()));

	}
}