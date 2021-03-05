#pragma once
#include <QLabel>
#include <model/Packet.h>
class QWidget;
namespace ui{
	class QClickLabel : public QLabel {
		Q_OBJECT
	public:
		QClickLabel(QWidget* parent = 0);
		~QClickLabel();
		void setTextColor(const QColor& clr);
		void setUnderlined(bool underlined);
		bool underlined() const;
		void setData(model::CloudFileInfo&data);
		model::CloudFileInfo getData()const;
	signals:
		void signalClicked(model::CloudFileInfo);
	protected:
		void mouseReleaseEvent(QMouseEvent*);
		void enterEvent(QEvent *event);
		void leaveEvent(QEvent *event);
		void makeUnderlined(bool underline);
	private:
		QColor m_textColor;
		bool m_underlined;
	private:
		model::CloudFileInfo m_data;
	};
}