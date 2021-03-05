#pragma  once
#include <QLabel>
namespace ui{
	class ElidedLabel : public QLabel
	{
		Q_OBJECT
	public:
		explicit ElidedLabel(QWidget *parent = 0, Qt::WindowFlags f = 0);
		explicit ElidedLabel(const QString &text, QWidget *parent = 0, Qt::WindowFlags f = 0);

		void setText(const QString &text);
		void setFullText(const QString &text);
		void setTextLimitShrink(const QString &text, int width);
		void setTextLimitExpand(const QString &text);
		QString fullText() const;
		void setTextColor(const QColor& clr);
	protected:
		void paintEvent(QPaintEvent *);

	private:
		void elideText();
	private:
		QColor m_textColor;
		QString m_fullText;
	};
}