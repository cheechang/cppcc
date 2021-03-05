#include "WeMessageBox.h"
#include "TitleBar.h"
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QWidget>
#include <Button.h>
#include <QVBoxLayout>
#include <QPainter>

#include <ui/common/ChineseInfos.hpp>
#include <ui/common/Common.h>
namespace uicontrols{
	QColor		 WeMessageBox::m_titleBkColor = QColor("#2768c2");
	QString      WeMessageBox::m_defaultSkin = QString("#2768c2");
	WeMessageBox::WeMessageBox(QWidget *parent,const QString title,const QString text,const int maxTextLenth):QDialog(parent),m_strIconPath("")
	{
		setWeWindowFlags();
#if (QT_VERSION_CHECK(5,6,0) < QT_VERSION)
		this->setWindowIcon(QIcon(":/base/logo"));
#endif
		m_titleBar = new TitleBar(this,true,false,true);
		this->installEventFilter(m_titleBar);
		m_titleBar->setFixedHeight(35*gDdpi);
		m_titleBar->setMinimumWidth(100);
		m_titleBar->setWindowRadius(WINDOWRADIUS);
		m_titleBar->setIcon(QString::fromLocal8Bit(":/base/tray"));
		m_titleBar->setBackGroudImg(m_defaultSkin);
		m_titleBar->setBtnPicName(uicontrols::TitleBar::OBJ_CLOSE,":/title/close");
		m_titleBar->setBtnToolTip(uicontrols::TitleBar::OBJ_CLOSE,TEXT_TIP8);
		m_titleHeight  = m_titleBar->height();

		m_MainLayout = new QVBoxLayout(this);
		m_MainLayout->setSpacing(0);
		m_MainLayout->setContentsMargins(WINDOWMARGINS,WINDOWMARGINS,WINDOWMARGINS,WINDOWMARGINS);
		m_MainLayout->addWidget(m_titleBar);

		this->setWindowTitle(title);
		m_pBtnOK = new uicontrols::Button(this);
		m_pCancel = new uicontrols::Button(this);
		m_pIcon = new QLabel(this);
		m_pText = new QTextEdit(this);


		
		QWidget*widget = new QWidget(this);
		QHBoxLayout*hLayout = new QHBoxLayout(widget);
		hLayout->setAlignment(Qt::AlignCenter);
		hLayout->addWidget(m_pIcon);
		hLayout->addWidget(m_pText);
		widget->setLayout(hLayout);

		QWidget*widgetBtn = new QWidget(this);
		QHBoxLayout*hButtonLayout = new QHBoxLayout(widgetBtn);
		hButtonLayout->addStretch();
		hButtonLayout->addWidget(m_pBtnOK);
		hButtonLayout->addWidget(m_pCancel);
		widgetBtn->setLayout(hButtonLayout);

		m_pCancel->setText(CANCEL);
		m_pBtnOK->setText(OK);
		m_pBtnOK->setFocus();
		
		m_pBtnOK->setFixedWidth(60);
		m_pCancel->setFixedWidth(60);

		m_pText->document()->setDocumentMargin(0);
		m_pText->setContentsMargins(0,0,0,0);
		m_pText->setFrameShape(QFrame::NoFrame);
		m_pText->setText(text);
		m_pText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		m_pText->setReadOnly(true);
		m_pText->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		setMaxTextLenth(maxTextLenth);
		m_pText->setObjectName("MsgBoxEdit");
		m_pIcon->setObjectName("BurnLbl");
		m_MainLayout->addWidget(widget);
		m_MainLayout->addWidget(widgetBtn);
		m_RetunType = Cancel;
		this->setIconSize(QSize(32,32));
		m_pIcon->setScaledContents(true);
		m_pIcon->setPixmap(QPixmap(":/chat/question"));
		connect(m_pBtnOK,SIGNAL(clicked(bool)),this,SLOT(onBtnOk()));
		connect(m_pCancel,SIGNAL(clicked(bool)),this,SLOT(onBtnCancel()));
		connect(this,SIGNAL(closeClicked()),this,SLOT(onBtnCancel()));
	}
	WeMessageBox::~WeMessageBox()
	{

	}

	WeMessageBox::TypeOfButton  WeMessageBox::question()
	{
		if(m_strIconPath.isEmpty()){
			m_strIconPath = ":/chat/question";
		}
		m_pIcon->setPixmap(QPixmap(m_strIconPath));
		this->exec();
		return m_RetunType;
	}

	WeMessageBox::TypeOfButton WeMessageBox::warning()
	{
	
		if(m_strIconPath.isEmpty()){
			m_strIconPath = ":/chat/worning";
		}
		m_pIcon->setPixmap(QPixmap(m_strIconPath));
		m_pCancel->setVisible(false);
		this->exec();
		return m_RetunType;
	}

	WeMessageBox::TypeOfButton WeMessageBox::information()
	{
		
		m_pIcon->setPixmap(QPixmap(m_strIconPath));
		m_pCancel->setVisible(false);
		this->exec();
		return m_RetunType;
	}

	WeMessageBox::TypeOfButton WeMessageBox::TipInformation(bool isShowIocn,bool isShowCancelBtn)
	{
		if(!isShowIocn)
		{
			m_pIcon->setVisible(false);
		}
		else
		{
			m_strIconPath.isEmpty()?m_strIconPath =":/chat/information":m_strIconPath;
			m_pIcon->setPixmap(QPixmap(m_strIconPath));
		}
		m_pCancel->setVisible(isShowCancelBtn);
		this->exec();
		return m_RetunType;
	}
	WeMessageBox::TypeOfButton WeMessageBox::err()
	{
		if(m_strIconPath.isEmpty()){
			m_strIconPath = ":/chat/information";
		}
		m_pIcon->setPixmap(QPixmap(m_strIconPath));
		m_pCancel->setVisible(false);
		this->exec();
		return m_RetunType;
	}
	WeMessageBox::TypeOfButton WeMessageBox::noIcon(){
		m_pIcon->setVisible(false);
		m_pCancel->setVisible(false);
		this->exec();
		return m_RetunType;
	}

	void WeMessageBox::onBtnCancel()
	{
		m_RetunType = Cancel;
		this->close();
	}

	void WeMessageBox::onBtnOk()
	{
		m_RetunType = Ok;
		this->close();
	}

	void WeMessageBox::setIcon(QString path)
	{
		m_strIconPath = path;
		m_pIcon->setPixmap(QPixmap(path).scaled(m_iconSize));
	}

	void WeMessageBox::setIconSize(QSize size)
	{
		m_iconSize = size;
		m_pIcon->setFixedSize(size);
	}
	void WeMessageBox::setMaxTextLenth(int lenth){
		m_pText->setLineWidth(lenth);
		QString text = m_pText->toPlainText();
		QString::const_iterator txtIter = text.begin();
		QFontMetrics fm = m_pText->fontMetrics();
		QSize sizeContent;
		int charWidth = 0;
		int width = 0;
		int height = 0;
		int len = 0;
		int row = 1;
		while (txtIter != text.end()) {
			charWidth = fm.width(*txtIter);
			len += charWidth;
			if (len > lenth || *txtIter == '\n') {
				++row;
				len = 0;
			}
			++txtIter;
		}
		width = row>1?lenth:len;
	    height = fm.height()*row;
#if defined(__linux__)
		height+=10;
#endif
		m_pText->setFixedSize(width,height);
	}
	void WeMessageBox::setWeWindowFlags(){
			Qt::WindowFlags flags= Qt::FramelessWindowHint;
			flags |= Qt::Window;
		#if defined(_WIN32)
			flags |= Qt::WindowSystemMenuHint;
			flags |= Qt::WindowMinimizeButtonHint;
		#else
			flags |= Qt::WindowStaysOnTopHint;
		#endif
			this->setWindowFlags(flags);
	}
	void WeMessageBox::paintEvent(QPaintEvent*event)
	{
	   QPainter painter(this);
	   painter.setRenderHints(QPainter::Antialiasing,true);
	   painter.setPen(Qt::darkGray);
	   painter.setBrush(m_titleBkColor); 
	   painter.drawRoundedRect(QRect(0,0, this->width(),m_titleHeight+WINDOWRADIUS),WINDOWRADIUS,WINDOWRADIUS);
	   painter.setBrush(Qt::white); 
	   painter.drawRoundedRect(QRect(0,m_titleHeight,this->width(),this->height()-m_titleHeight),WINDOWRADIUS,WINDOWRADIUS);
	   QDialog::paintEvent(event);
	}
	WeMessageBox::TypeOfButton WeMessageBox::showInformation(QWidget *parent, const QString &title,const QString &text,const int maxTextLenth){
		WeMessageBox msgBox(parent,title,text,maxTextLenth);
		return msgBox.information();
	}
	WeMessageBox::TypeOfButton WeMessageBox::showTipInformation(QWidget *parent, const QString &title,const QString &text,bool showIocn,bool showCancelBtn,const int maxTextLenth)
	{
		WeMessageBox msgBox(parent,title,text,maxTextLenth);
		return msgBox.TipInformation(showIocn,showCancelBtn);
	}
	WeMessageBox::TypeOfButton WeMessageBox::showQuestion(QWidget *parent, const QString &title,const QString &text,const int maxTextLenth){
		WeMessageBox msgBox(parent,title,text,maxTextLenth);
		return msgBox.question();
	}
	WeMessageBox::TypeOfButton WeMessageBox::showWarning(QWidget *parent, const QString &title,const QString &text,const int maxTextLenth){
		WeMessageBox msgBox(parent,title,text,maxTextLenth);
		return msgBox.warning();	
	}
	WeMessageBox::TypeOfButton WeMessageBox::showCritical(QWidget *parent, const QString &title,const QString &text,const int maxTextLenth){
		WeMessageBox msgBox(parent,title,text,maxTextLenth);
		return msgBox.noIcon();	
	}
	void WeMessageBox::setDefaultSkin(const QString skin,const QColor skinColor){
		m_titleBkColor = skinColor;
		m_defaultSkin = skin;
	}
}
