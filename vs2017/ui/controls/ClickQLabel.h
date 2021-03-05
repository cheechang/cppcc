#ifndef CLICKQLABEL_H
#define CLICKQLABEL_H
#include <QLabel>
#include <QColor>
#include <QWidget>
#include <QApplication>
class QEvent;
class QMouseEvent;
namespace ui{
	class ClickQLabel : public QLabel
	{
		Q_OBJECT
	public:
		explicit ClickQLabel(QWidget* parent = 0);

		void setUnderlined(bool underlined);
		bool underlined() const;

		void setTextColor(const QColor& clr);
		QColor textColor() const;
		void setPicName(QString pic_name);
	signals:
		void clicked();
	protected:
		void enterEvent(QEvent* event);
		void leaveEvent(QEvent* event);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
	private:
		void makeUnderlined(bool underline);

	private:
		bool m_underlined;
		QColor m_textColor;
	};
}
#endif // CLICKQLABEL_H
