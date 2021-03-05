#include "eventfilter.h"

EventFilter::EventFilter(QObject *parent) : QObject(parent), m_target(0)
{

}

void EventFilter::setTargetObject(QObject* target)
{
    m_target = target;
}

QObject* EventFilter::targetObject() const
{
    return m_target;
}

bool EventFilter::eventFilter(QObject *watched, QEvent *event)
{
    if (m_target == watched)
        emit eventFiltered(event);

    return QObject::eventFilter(watched, event);
}
