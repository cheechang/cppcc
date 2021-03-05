#ifndef TEXTMESSAGEWIDGET_H
#define TEXTMESSAGEWIDGET_H

#include "abstractmessagewidget.h"

class QLabel;
class DynamicFontSizeLabel;
class TextMessageWidget : public AbstractMessageWidget
{
    Q_OBJECT
public:
    explicit TextMessageWidget(QWidget* parent = 0);

    void setText(const QString& text);
    QString text() const;

    void setFont(const QFont &f);
    QFont font() const;

    void setTextColor(const QColor& clr);
    QColor textColor() const;

    QSize suggestWidth(int width);

protected:
    QLabel* label();
    void initializeContextActions();

private slots:
    void copyMsg();
    void searchMsg();
    void deleteMsg();

protected:
    QColor m_textColor;
    QLabel* m_label;
};

#endif // TEXTMESSAGEWIDGET_H
