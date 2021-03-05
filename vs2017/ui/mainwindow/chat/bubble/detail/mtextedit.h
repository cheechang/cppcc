#ifndef _MTEXTEDIT_H_
#define _MTEXTEDIT_H_

#include <QTextEdit>
#include <QMimeData>
#include <QImage>

class MTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    MTextEdit(QWidget *parent);

    void dropImage(const QImage& image, const QString& format);

signals:
    void sendMessage();
protected:
    bool canInsertFromMimeData(const QMimeData *source) const;
    void insertFromMimeData(const QMimeData *source);
    QMimeData* createMimeDataFromSelection() const;
    void keyPressEvent(QKeyEvent* event);
};

#endif
