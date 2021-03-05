#include "flexaction.h"

FlexAction::FlexAction(QObject* parent) : QAction(parent)
{

}

FlexAction::FlexAction(const QString &text, QObject *parent) : QAction(text, parent)
{

}

FlexAction::FlexAction(const QIcon &icon, const QString &text, QObject *parent) : QAction(icon, text, parent)
{

}

FlexAction::~FlexAction()
{

}

void FlexAction::addChild(FlexAction* action)
{
    if (!m_children.contains(action))
        m_children.append(action);
}

QList<FlexAction*> FlexAction::children() const
{
    return m_children;
}

void FlexAction::clear()
{
    qDeleteAll(m_children);
    m_children.clear();
}

bool FlexAction::isEmpty() const
{
    return m_children.isEmpty();
}

int FlexAction::count() const
{
    return m_children.count();
}
