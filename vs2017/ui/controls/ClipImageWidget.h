#pragma once

#include <QObject>
#include <QLabel>
#include "PushButton.h"
#include "ClipWidget.h"

namespace ui{
class ClipImageWidget : public QWidget
{
	Q_OBJECT

public:
	ClipImageWidget(QWidget *parent=NULL);
	~ClipImageWidget();

	void setMinSize(int w, int h);
	void setBtnVisible(bool b);
public slots:
	void onSelectBtnClicked();
	void onBtnSaveImg();
	void onClipImgSucc(QString file400, QString file150);
signals:
	void clipImgSucc(QString file400, QString file150);
private:
	QLabel m_bgLab;
	PushButton m_selBtn;
	ClipWidget m_clipImg;
	QString m_filename;
};
}

