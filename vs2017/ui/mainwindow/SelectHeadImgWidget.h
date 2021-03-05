#pragma once

#include <QObject>
#include <QLabel>
//#include "../core/BaseDialog.h"
#include "../controls/TWindow.h"
#include "../controls/WinTitleWidget.h"
#include "../controls/PushButton.h"
#include "../controls/HeadImage.h"
#include "../controls/ClipImageWidget.h"
#include <QVBoxLayout>

#include "common/controlptr.h"

namespace ui{
class SelectHeadImgWidget : public TWindow
{
	Q_OBJECT

public:
	SelectHeadImgWidget(TWindow *parent=NULL);
	~SelectHeadImgWidget();
	void setHeadType(int type);
public slots:
	void onBtnClose();
	void onBtnOK();
	void onMouseMove(QPoint p);
	void onClipImgSucc(QString file400, QString file150);

	void onSerSetHead(int, const std::string&, const std::string&);
	void onSerSetUserInfoHead(int code);
signals:
	void signalSerSetHead(int, const std::string&, const std::string&);
	void signalSerSetUserInfoHead(int code);
	void signalSerModifyGroupHead(std::string&);
	void signalUserHeadSucc(QString file400);
private:
	QVBoxLayout m_mainLayout;
	QHBoxLayout m_SelLayout;
	QVBoxLayout m_contentLayout;

	WinTitleWidget m_lbTitle;
	QPushButton m_btnOK;
	QPushButton m_btnCancel;
	ClipImageWidget m_leftBgRect;
	HeadImage m_img150x150;
	QLabel m_lb150x150;
	HeadImage m_img40x40;
	QLabel m_lb40x40;

	int m_type;// 1:¸öÈË 2£ºÍ·Ïñ

	IUserControl_Ptr m_usercontrol;
	IAuthControl_Ptr m_authcontrol;
};
}
