#ifndef HEADIMAGE_H
#define HEADIMAGE_H

#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>
#include <QSize>
#include <QColor>
#include "qlabel.h"
namespace ui{
class HeadImage : public QWidget
{
	Q_OBJECT

    enum {
        MAX_ROUNDHEAD_WIDTH = 120,
        MAX_ROUNDHEAD_HEIGHT = 120,
    };

public:
    HeadImage(QWidget *parent = 0, 
		const QSize& avatarSize = QSize(MAX_ROUNDHEAD_WIDTH, MAX_ROUNDHEAD_HEIGHT), 
		bool hasHoverBorder = false);

    void setAvatarPath(const QString& fullPath);
	QString AvatarPath();
	void setHasHoverBorder(const bool hasHoverBorder);
	void setShowAsGray(bool isGray);
	void setAvaterSize(QSize size);
	void setMouseInStyle(bool isTrue);

	///QLabel *nameInfo;
signals:
    void clicked(QPoint pos);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    bool        mIsMouseOver;
    bool        mIsMousePressed;
    QString     mImgFullPath;
    QSize       mAvatarSize;
    QImage      mOriginalImage;
    QImage      mMask;
	bool		m_hasHoverBorder;
	bool        mIsShowGray;
	bool		m_isClicked;
public:
	////void SetInfo(QString info);
};
}
#endif // HEADIMAGE_H
