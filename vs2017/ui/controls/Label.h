#pragma  once
/**
** 新封装控件：超过长度"..."显示
**/
#include <QLabel>
namespace uicontrols{
	class Label : public QLabel
	{
		Q_OBJECT
	public:
		explicit Label(QWidget *parent=0, Qt::WindowFlags f=0);
		explicit Label(const QString &text, QWidget *parent=0, Qt::WindowFlags f=0);

		void setText(const QString &text);
		void setFullText(const QString &text);
		void setTextLimitShrink(const QString &text, int width);
		void setTextLimitExpand(const QString &text);
		QString fullText() const;
		void setTextColor(const QColor& clr);
		void setAtMeStr(const QString &str);
	signals:
		void clicked();
	protected:
		void paintEvent(QPaintEvent *);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
		bool eventFilter(QObject *o, QEvent *e);
	private:
		void elideText();
	private:
		QColor m_textColor;
		QString m_fullText;
		QString m_atMeStr;
	};
}