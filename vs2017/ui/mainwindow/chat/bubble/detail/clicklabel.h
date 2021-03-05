#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>

class ClickLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickLabel(QWidget* parent = 0);

    void setUnderlined(bool underlined);
    bool underlined() const;

    void setTextColor(const QColor& clr);
    QColor textColor() const;

signals:
    void clicked();

protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    void makeUnderlined(bool underline);

private:
    bool m_underlined;
    QColor m_textColor;
};

#endif // CLICKLABEL_H
