#pragma once

#include "../core/BaseDialog.h"
#include "../controls/ElidedLabel.h"

#include "common/controlptr.h"
#include "UserHeadImg.h"
#include "UserExtendInfo.h"
#include <QStackedWidget>
#include <QFocusEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMap>

namespace ui{
class PushButton;

class SelectHeadImgWidget;
class UserBasicInfo;
class UserExtendInfo;

class UserInfoWidget : public BaseDialog
{
	Q_OBJECT

public:
	UserInfoWidget(BaseDialog *parent=NULL);
	~UserInfoWidget();
    void ShowInfo();
signals:
	void signalWinClose();
    void signalOrgID(int64 id);
	void signalUserHeadSucc(QString headImg);
    void signalEditInfoClicked();
public slots:
	void onHeadImgClicked();
	void onUserHeadSucc(QString headImg);
	void onUpdateUserInfoResult(int code);
protected:
    void setUserHead();
	void focusOutEvent(QFocusEvent *event);
	void focusInEvent(QFocusEvent *event);

private:
	IUserControl_Ptr m_usercontrol;
	CSharedPtr<data::AccountInfo> m_userInfo;

    CSharedPtr<UserExtendInfo>    m_userExtend;
    CSharedPtr<UserBasicInfo>     m_userBasic;
    CSharedPtr<QStackedWidget>    m_userInfoStack;

	QVBoxLayout m_mainLayout;
	QHBoxLayout  m_bottunLayout;
	UserHeadImg m_headImage;

	CSharedPtr<QPushButton> m_btnSave;
    CSharedPtr<QPushButton> m_btnCancel;
    CSharedPtr<QPushButton> m_btnMoreInfo;
	CSharedPtr<PushButton>  m_btnEdit;

	SelectHeadImgWidget* m_selImgWidget;
};
}
