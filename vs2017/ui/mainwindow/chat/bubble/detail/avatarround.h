#pragma once
#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>
#include <QSize>

class AvatarRound : public QWidget
{
    Q_OBJECT
    enum {
        MAX_ROUNDHEAD_WIDTH = 80,
        MAX_ROUNDHEAD_HEIGHT = 80,
    };

public:
    AvatarRound(QWidget *parent = 0, const QSize& avatarSize = QSize(MAX_ROUNDHEAD_WIDTH, MAX_ROUNDHEAD_HEIGHT));

    void setAvatarPath(const QString& fullPath);

    void setAvatar(const QPixmap& pixmap);
    QPixmap avatar() const;

    QSize sizeHint() const;

signals:
    void clicked();

protected:
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *event);

private:
    bool        mIsMouseOver;
    bool        mIsMousePressed;
    QString     mImgFullPath;
    QSize       mAvatarSize;
    QImage      mOriginalImage;
    QImage      mMask;
};

