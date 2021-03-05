#include "Label.h"
#include "ToolTip.h"
#include <QMouseEvent>
#include <QTimer>
#include <qdebug.h>
#include <ui/common/ChineseInfos.hpp>
namespace uicontrols{
	Label::Label(QWidget *parent, Qt::WindowFlags f)
		: QLabel(parent, f),m_atMeStr("")
	{
		this->setMouseTracking(true);
		this->installEventFilter(this);
	}

	Label::Label(const QString &text, QWidget *parent, Qt::WindowFlags f)
		: QLabel(text, parent, f), m_fullText(text),m_atMeStr("")
	{
		this->setMouseTracking(true);
		this->installEventFilter(this);
	}

	void Label::setText(const QString &text)
	{
		setFullText(text);
	}

	void Label::setFullText(const QString &text)
	{
		m_fullText = text;
		elideText();
	}

	void Label::setTextLimitShrink(const QString &text, int width)
	{
		this->setMinimumWidth(width);
		setFullText(text);
	}

	void Label::setTextLimitExpand(const QString &text)
	{
		setFullText(text);
		int textWidth = this->fontMetrics().width(this->text());
		this->setMinimumWidth(textWidth);
	}

	QString Label::fullText() const
	{
		return m_fullText;
	}
	void Label::paintEvent(QPaintEvent *event)
	{
		elideText();
		QLabel::paintEvent(event);
	}

	void Label::elideText()
	{
		QString tempText = m_fullText;
		tempText.replace(m_atMeStr,"");
		QFontMetrics fm = this->fontMetrics();
		bool isContiansAtMe = (!m_atMeStr.isEmpty() && m_fullText.contains(m_atMeStr));
		int width =isContiansAtMe?this->width()-55:this->width();
		int dif = fm.width(tempText)-width;
		if (dif > 0) {
			QString showText = fm.elidedText(tempText,Qt::ElideRight,width);
			showText = isContiansAtMe?m_atMeStr+showText:showText;
			QLabel::setText(showText);
		}
		else{
			QLabel::setText(m_fullText);
		}
	}
	void Label::setTextColor(const QColor& clr)
	{
		if (m_textColor != clr) {
			m_textColor = clr;
			QString style = QString("color: rgb(%1, %2, %3);").arg(clr.red()).arg(clr.green()).arg(clr.blue());
			setStyleSheet(style);
		}
	}
	void Label::mousePressEvent(QMouseEvent* event)
	{
		if (event->buttons() & Qt::LeftButton)
			emit clicked();
		QLabel::mousePressEvent(event);
	}

	void Label::mouseReleaseEvent(QMouseEvent* event)
	{
		if (event->buttons() & Qt::LeftButton)
			emit clicked();
		QLabel::mouseReleaseEvent(event);
	}
bool Label::eventFilter(QObject *o, QEvent *e)
{
	QRect rect = this->rect();
	qDebug()<<"========="<<e->type();
    switch (e->type()) 
	{
	case QEvent::ToolTip:
	{
		if (o == this && !rect.isNull() && !rect.contains(QCursor::pos())){
			QPoint pos = QCursor::pos()+QPoint(5,10);
			Tooltip::popup(pos,m_fullText); 
		}
		break;
	 }
#ifdef Q_WS_MAC
    case QEvent::KeyPress:
    case QEvent::KeyRelease: 
	{
        int key = static_cast<QKeyEvent *>(e)->key();
        Qt::KeyboardModifiers mody = static_cast<QKeyEvent *>(e)->modifiers();
        if (!(mody & Qt::KeyboardModifierMask)
            && key != Qt::Key_Shift && key != Qt::Key_Control
            && key != Qt::Key_Alt && key != Qt::Key_Meta)
           Tooltip::hideTipWnd();
           break;
    }
#endif
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::Wheel:
		{
			Tooltip::hideTipWnd();
			break;
		}
	case QEvent::Leave:
	case QEvent::MouseMove:{
		if (o == this && !rect.isNull() && !rect.contains(QCursor::pos())){
			Tooltip::hideTipWnd();
			break;
		}  
	  }
    default:
        break;
    }
    return false;
 }
 void Label::setAtMeStr(const QString &str){
	 m_atMeStr = str;
 }
}