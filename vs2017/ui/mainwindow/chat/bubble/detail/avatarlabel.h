#ifndef AVATARLABEL_H
#define AVATARLABEL_H

#include <QLabel>

class AvatarLabel : public QLabel
{
    Q_OBJECT
public:
    explicit AvatarLabel(QWidget* parent = 0);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    QPoint m_cursorPos;
};

#endif // AVATARLABEL_H
