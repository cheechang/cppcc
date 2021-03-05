#ifndef RICHTEXTMESSAGEWIDGET_H
#define RICHTEXTMESSAGEWIDGET_H

#include "abstractmessagewidget.h"
class RichTextMessageWidgetPrivate;
class RichTextMessageWidget : public AbstractMessageWidget
{
    Q_OBJECT
public:
    explicit RichTextMessageWidget(QWidget* parent = 0);
    ~RichTextMessageWidget();

    void setText(CSharedPtr<data::Msg>&msg);
    QString text() const;

    void setFont(const QFont &f);
    QFont font() const;

    void setTextColor(const QColor& clr);
    QColor textColor() const;

    QSize suggestWidth(int width);
    int type() const;
signals:
	void noticeInputEditFocus();
	void signalSerRecallEdit(QString& txt);
protected:
    void    initializeContextActions();
	QString expressParseFrom(std::string srcText,bool issendmsg=false);
protected slots:
	void onCopyMsg();
	void onSerRecallEdit();
private:
	bool m_iscontainsemoji;
	int  m_emojicount;
	int  m_textspace;
    class RichTextMessageWidgetPrivate* d_ptr;
	QString mMsgText;
};

#endif // RICHTEXTMESSAGEWIDGET_H
