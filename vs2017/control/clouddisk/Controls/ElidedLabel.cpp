#include "elidedlabel.h"
namespace ui{
	ElidedLabel::ElidedLabel(QWidget *parent, Qt::WindowFlags f)
		: QLabel(parent, f)
	{
		this->setMinimumWidth(0);
		setTextFormat(Qt::PlainText);
	}

	ElidedLabel::ElidedLabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
		: QLabel(text, parent, f), m_fullText(text)
	{
		this->setMinimumWidth(0);
		setTextFormat(Qt::PlainText);
	}

	void ElidedLabel::setText(const QString &text)
	{
		setFullText(text);
	}

	void ElidedLabel::setFullText(const QString &text)
	{
		m_fullText = text;
		update();
	}

	void ElidedLabel::setTextLimitShrink(const QString &text, int width)
	{
		this->setMinimumWidth(qMin(this->fontMetrics().width(text), width));
		setFullText(text);
	}

	void ElidedLabel::setTextLimitExpand(const QString &text)
	{
		int textWidth = this->fontMetrics().width(text);
		this->setMaximumWidth(textWidth);
		setFullText(text);
	}

	QString ElidedLabel::fullText() const
	{
		return m_fullText;
	}

	void ElidedLabel::paintEvent(QPaintEvent *event)
	{
		QLabel::paintEvent(event);
		elideText();
	}

	void ElidedLabel::elideText()
	{
		QFontMetrics fm = this->fontMetrics();
		int dif = fm.width(m_fullText) - this->width();
		if (dif > 0) {
			QString showText = fm.elidedText(m_fullText, Qt::ElideRight, this->width());
			QLabel::setText(showText);
			if (showText != m_fullText) {
				this->setToolTip(m_fullText.left(1024));
			}
			else {
				this->setToolTip("");
			}
		}
		else {
			QLabel::setText(m_fullText);
			this->setToolTip("");
		}
	}
	void ElidedLabel::setTextColor(const QColor& clr)
	{
		if (m_textColor != clr) {
			m_textColor = clr;
			QString style = QString("color: rgb(%1, %2, %3);").arg(clr.red()).arg(clr.green()).arg(clr.blue());
			setStyleSheet(style);
		}
	}
}

