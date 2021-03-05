#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <QGraphicsView>

class ChatView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ChatView(QWidget* parent = 0);
    ~ChatView();

    void setBackgroundImage(const QPixmap& image);
    QPixmap backgroundImage() const;
signals:
	void hideAtWin();
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void contextMenuEvent(QContextMenuEvent* event);

	virtual void mouseReleaseEvent(QMouseEvent *e);

private:
    class ChatViewPrivate* d_ptr;
};

#endif // CHATVIEW_H
