#include "ClickQLabel.h"
#include <QMouseEvent>
#include <QEvent>

namespace ui{

	ClickQLabel::ClickQLabel(QWidget* parent) : QLabel(parent), m_underlined(false), m_textColor(Qt::black)
	{
		setMouseTracking(true);
	}

	void ClickQLabel::setUnderlined(bool underlined)
	{
		m_underlined = underlined;
	}

	bool ClickQLabel::underlined() const
	{
		return m_underlined;
	}

	void ClickQLabel::setTextColor(const QColor& clr)
	{
		if (m_textColor != clr) {
			m_textColor = clr;
			QString style = QString("color: rgb(%1, %2, %3);").arg(clr.red()).arg(clr.green()).arg(clr.blue());
			setStyleSheet(style);
		}
	}

	QColor ClickQLabel::textColor() const
	{
		return m_textColor;
	}

	void ClickQLabel::setPicName(QString pic_name)
	{
		this->setPixmap(QPixmap(pic_name));
		setFixedSize(QPixmap(pic_name).size());
	}

	void ClickQLabel::enterEvent(QEvent* event)
	{
		Q_UNUSED(event)
			if (m_underlined) {
				setCursor(Qt::PointingHandCursor);
				makeUnderlined(true);
			}
	}

	void ClickQLabel::leaveEvent(QEvent* event)
	{
		Q_UNUSED(event)
			if (m_underlined) {
				qApp->restoreOverrideCursor();
				makeUnderlined(false);
			}
	}

	void ClickQLabel::mousePressEvent(QMouseEvent* event)
	{
		if (event->buttons() & Qt::LeftButton)
			emit clicked();
		QLabel::mousePressEvent(event);
	}

	void ClickQLabel::mouseReleaseEvent(QMouseEvent* event)
	{
		if (event->buttons() & Qt::LeftButton)
			emit clicked();
		QLabel::mouseReleaseEvent(event);
	}

	void ClickQLabel::makeUnderlined(bool underline)
	{
		QFont f = font();
		f.setUnderline(underline);
		setFont(f);
	}

}