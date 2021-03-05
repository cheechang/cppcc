#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>

class EventFilter : public QObject
{
    Q_OBJECT
public:
    explicit EventFilter(QObject *parent = 0);

    void setTargetObject(QObject* target);
    QObject* targetObject() const;

    bool eventFilter(QObject *watched, QEvent *event);

signals:
    void eventFiltered(QEvent* event);

private:
    QObject* m_target;
};

#endif // EVENTFILTER_H
