#ifndef FLEXACTION_H
#define FLEXACTION_H

#include <QAction>

class FlexAction : public QAction
{
    Q_OBJECT
public:
    explicit FlexAction(QObject* parent = 0);
    explicit FlexAction(const QString &text, QObject *parent = 0);
    explicit FlexAction(const QIcon &icon, const QString &text, QObject *parent = 0);

    ~FlexAction();

    void addChild(FlexAction* action);
    QList<FlexAction*> children() const;
    void clear();
    bool isEmpty() const;
    int count() const;

private:
    QList<FlexAction*> m_children;
};

#endif // FLEXACTION_H
