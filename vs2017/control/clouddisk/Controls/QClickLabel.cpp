#include "QClickLabel.h"
#include <QApplication>
#include <qwidget.h>
namespace ui{
	QClickLabel::QClickLabel(QWidget* parent) : 
	QLabel(parent),m_underlined(false){
		QFont font = this->font();
		font.setFamily("Microsoft YaHei");
		this->setFont(font);
		this->setMaximumWidth(220);
	}
	QClickLabel::~QClickLabel() {

	}
	void QClickLabel::mouseReleaseEvent(QMouseEvent*) {
		if (m_underlined){
			emit signalClicked(m_data);
		}
	}

	void QClickLabel::enterEvent(QEvent *event) {
		Q_UNUSED(event);
		if (m_underlined) {
			setCursor(Qt::PointingHandCursor);
			makeUnderlined(true);
		}
	}
	void QClickLabel::leaveEvent(QEvent *event) {
		Q_UNUSED(event);
		if (m_underlined) {
			qApp->restoreOverrideCursor();
			makeUnderlined(false);
		}
	}
	void QClickLabel::setTextColor(const QColor& clr)
	{
		if (m_textColor != clr) {
			m_textColor = clr;
			QString style = QString("color: rgb(%1, %2, %3);").arg(clr.red()).arg(clr.green()).arg(clr.blue());
			setStyleSheet(style);
		}
	}
	void QClickLabel::makeUnderlined(bool underline)
	{
		QFont f = font();
		f.setUnderline(underline);
		setFont(f);
	}
	void QClickLabel::setUnderlined(bool underlined)
	{
		m_underlined = underlined;
		setMouseTracking(m_underlined);
		if(!underlined){
			makeUnderlined(false);
		}
	}

	bool QClickLabel::underlined() const
	{
		return m_underlined;
	}
	void QClickLabel::setData(model::CloudFileInfo&data){
		m_data = data;
	}
	model::CloudFileInfo QClickLabel::getData()const{
		return m_data;
	}
}