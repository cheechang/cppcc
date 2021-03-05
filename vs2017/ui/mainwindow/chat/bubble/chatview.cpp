#include "chatview.h"
#include "abstractmessagewidget.h"
#include "flexaction.h"
#include "detail/flexmessagewidget.h"

#include <QPainter>
#include <QScrollBar>
#include <QDebug>
#include <QContextMenuEvent>
#include <QGraphicsProxyWidget>
#include <QMenu>

class ChatViewPrivate
{
public:
    QPixmap bgImage;
};

ChatView::ChatView(QWidget* parent) : QGraphicsView(parent)
{
    d_ptr = new ChatViewPrivate;
}

ChatView::~ChatView()
{
    delete d_ptr;
}

void ChatView::setBackgroundImage(const QPixmap& image)
{
    d_ptr->bgImage = image;
    update();
}

QPixmap ChatView::backgroundImage() const
{
    return d_ptr->bgImage;
}

void ChatView::drawBackground(QPainter *painter, const QRectF &rect)
{
    if (!d_ptr->bgImage.isNull()) {
        qDebug() << "bg rect: " << rect;
        painter->drawPixmap(QRect(QPoint(0, this->verticalScrollBar()->value()), viewport()->size()), d_ptr->bgImage);
    }
}

static void loadActions(QMenu* menu, FlexAction* action)
{
    if (action->isSeparator()) {
        menu->addSeparator();
        return;
    }

    if (action->isEmpty()) {
        menu->addAction(action);
        return;
    }

    QMenu* subMenu = new QMenu(action->text(), menu);
    subMenu->setIcon(action->icon());
    menu->addMenu(subMenu);

    foreach (FlexAction* childAction, action->children())
        loadActions(subMenu, childAction);
}

void ChatView::contextMenuEvent(QContextMenuEvent* event)
{
    QGraphicsItem* currentItem = scene()->itemAt(QPointF(event->pos().x(), event->pos().y() + verticalScrollBar()->value()), QTransform());
    if (!currentItem) return;

    QGraphicsProxyWidget* proxyWidget = dynamic_cast<QGraphicsProxyWidget*>(currentItem);
    if (!proxyWidget) return;

    FlexMessageWidget* widget = qobject_cast<FlexMessageWidget*>(proxyWidget->widget());
    if (!widget) return;

    AbstractMessageWidget* msgWidget = widget->messageWidget();
    if (!msgWidget || msgWidget->actions().isEmpty()) return;

    QMenu menu;
    foreach (FlexAction* action, msgWidget->actions()) {
//        if (action->isSeparator()) {
//            menu.addSeparator();
//            continue;
//        }
        loadActions(&menu, action);
    }

    menu.exec(event->globalPos());
}

void ChatView::mouseReleaseEvent(QMouseEvent *e)
{
	emit hideAtWin();
	QGraphicsView::mouseReleaseEvent(e);
}

