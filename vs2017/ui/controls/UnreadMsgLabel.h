#ifndef UNREADMSGLABEL_H
#define UNREADMSGLABEL_H

#include <QLabel>
#include <QWidget>
#include <interface/Defines.h>
namespace ui{
	class UnreadMsgLabel : public QLabel
	{
		Q_OBJECT
		enum {
			FontW = 20,
			Font2W = 24,
			Font3W = 28,
			Height = 18
		};
	public:
		UnreadMsgLabel(QWidget *parent=CNull);
		~UnreadMsgLabel();
	public Q_SLOTS:
		void setText(const QString &text);
	protected:
		void paintEvent(QPaintEvent *e);
	private:

	};
}

#endif // UNREADMSGLABEL_H
