#pragma once

#include <QLabel>
#include <QMouseEvent>
#include <interface/Defines.h>
namespace ui{
	const int HEAD_WIDTH = 320+20;
	const int HEAD_HEIGTH  = 460;
    class PushButton;
class UserHeadImg : public QLabel
{
	Q_OBJECT

public:
	UserHeadImg(QObject *parent=NULL);
	~UserHeadImg();

	void setHeadImg(QString path);
signals:
	void mouseLeftRelease(/*QMouseEvent *ev*/);
    void closeImageWin();
protected:
	void mouseReleaseEvent(QMouseEvent *ev);
	QPixmap getRoundHead(const QPixmap &src, int radius);
private:  
    CSharedPtr<PushButton>  m_closeBtn;
	QLabel*  m_head;
};
}
