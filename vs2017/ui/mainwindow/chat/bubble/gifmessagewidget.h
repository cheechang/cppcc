#ifndef GIFMESSAGEWIDGET_H
#define GIFMESSAGEWIDGET_H

#include "imagemessagewidget.h"

class QMovie;
class GifMessageWidget : public ImageMessageWidget
{
    Q_OBJECT
public:
    explicit GifMessageWidget(QWidget* parent = 0);

	void  setDnyMsg(CSharedPtr<data::Msg>&msg);
    void setImage(const QString& image);
    QSize suggestWidth(int width);

protected:
    void initializeContextActions();
	void mouseDoubleClickEvent(QMouseEvent* event);
protected:
    QMovie* m_movie;
    QSize m_movieSize;
};

#endif // GIFMESSAGEWIDGET_H
