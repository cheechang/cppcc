#include "ToolTip.h"
#include <QTextEdit>
#include <QHBoxLayout>
#include <QEvent>
#include <QPainter>
namespace uicontrols{
Tooltip *Tooltip::instance = 0;
Tooltip::Tooltip(QWidget *parent):QLabel(parent),m_content(0),m_maxtextLenth(240)
{
	delete instance;
    instance = this;

    setWindowFlags(Qt::ToolTip|Qt::BypassGraphicsProxyWidget);
    m_content = new QTextEdit(this);
	m_content->setReadOnly(true);
	m_content->setFrameShape(QFrame::NoFrame);
	m_content->document()->setDocumentMargin(0);
	m_content->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_content->setLineWidth(m_maxtextLenth);
	m_content->setAlignment(Qt::AlignCenter);
    QHBoxLayout *mLayout = new QHBoxLayout(this);
	mLayout->setContentsMargins(0,0,0,0);
	mLayout->setAlignment(Qt::AlignCenter);
    mLayout->addWidget(m_content);
}
Tooltip::~Tooltip()
{
}

void Tooltip::setText(const QString &context)
{
	if(context.isEmpty())return;
	m_content->setText(context);
	QString text = m_content->toPlainText();
	text.replace("\n","");
	QString::const_iterator txtIter = text.begin();
	QFontMetrics fm = m_content->fontMetrics();
	QSize sizeContent;
	int charWidth = 0;
	int width = 0;
	int height = 0;
	int len = 0;
	int row = 1;
	while (txtIter != text.end()) {
		charWidth = fm.width(*txtIter);
		len += charWidth;
		if (len > m_maxtextLenth || *txtIter == '\n') {
			++row;
			len = 0;
		}
		++txtIter;
	}
	width = row>1?m_maxtextLenth:len;
	height = fm.height()*row;
	m_content->setFixedSize(width,height);
	this->setFixedSize(width+8,height+8);
}
void Tooltip::paintEvent(QPaintEvent*event)
{
   QPainter painter(this);
   painter.setRenderHints(QPainter::Antialiasing, true);
   painter.setPen(Qt::gray);
   painter.setBrush(Qt::white); 
   painter.drawRect(this->rect());
   QLabel::paintEvent(event);
}
void Tooltip::hideTip()
{
	if(this->isVisible()){
	  this->hide();
	  m_content->setText("");
	  m_content->setFixedSize(0,0);
	  this->setFixedSize(0,0);
	}
}
void Tooltip::popup(QPoint pos, const QString &text)
{
    if (!text.isEmpty() && !Tooltip::instance){ 
        new Tooltip;
	}
	if (!text.isEmpty() && Tooltip::instance && Tooltip::instance->isVisible()){ 
        Tooltip::instance->hideTip();
	}
	if(Tooltip::instance && !Tooltip::instance->isVisible()){
		Tooltip::instance->setText(text);
		Tooltip::instance->move(pos);
		Tooltip::instance->show();
	}
}
void Tooltip::hideTipWnd(){
	if(Tooltip::instance){
		Tooltip::instance->hideTip();
	}
}
}