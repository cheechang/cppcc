#ifndef CHATSCENE_H
#define CHATSCENE_H
#include<Defines.h>
#include <QGraphicsScene>
class AbstractMessageWidget;
class FlexMessageWidget;
class ChatScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ChatScene(QObject* parent = 0);
    ~ChatScene();
	QMap<int64, FlexMessageWidget*>getMySendMessageWidgets();
	AbstractMessageWidget* getMsgWidgetByMsgId(int64 msgId);
    void setBackgroundImage(const QPixmap& image);
    QPixmap backgroundImage() const;

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    QPixmap m_bgImage;
};

#endif // CHATSCENE_H
