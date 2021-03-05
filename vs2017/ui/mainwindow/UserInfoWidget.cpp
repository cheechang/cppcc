#include "UserInfoWidget.h"
#include "SelectHeadImgWidget.h"
#include "UserBasicInfo.h"

#include "log.h"
#include <json.h>
#include <utils/common.h>
#include "../common/Common.h"
namespace ui{
UserInfoWidget::UserInfoWidget(BaseDialog *parent)
	: BaseDialog(parent),m_selImgWidget(NULL)
{
	//this->setMinimumHeight(600);
	
	setFocusPolicy (Qt::StrongFocus);
	onMoveWindow(false);
	m_usercontrol = USERCONTROL;
    
    m_userBasic = CMakePtr<UserBasicInfo>(this);

    connect(this,SIGNAL(signalOrgID(int64)),m_userExtend.get(),SLOT(setOrgId(int64)));
	connect(&m_headImage, SIGNAL(mouseLeftRelease()),this, SLOT(onHeadImgClicked()), Qt::QueuedConnection);
	connect(m_userBasic.get(),SIGNAL(signalSetUserInfoResult(int)),this,SLOT(onUpdateUserInfoResult(int)));

	m_headImage.setParent(this);
	AddLog(LOG_LEV_INFO,"----------------------");
	m_headImage.setHeadImg(":/base/default_head");
	connect(&m_headImage,SIGNAL(closeImageWin()),this,SIGNAL(signalWinClose()));
	this->setFixedWidth(340);
	m_mainLayout.addWidget(&m_headImage,0, Qt::AlignHCenter);

	m_mainLayout.addWidget(m_userBasic.get());
	m_mainLayout.addSpacing(10);
	setLayout(&m_mainLayout);
    setUserHead();
}

UserInfoWidget::~UserInfoWidget()
{
    if (m_selImgWidget != CNull)
    {
        delete m_selImgWidget;
        m_selImgWidget = CNull;
    }
}
void UserInfoWidget::focusOutEvent(QFocusEvent *event)
{
	//emit focusOut(event);
}
void UserInfoWidget::focusInEvent(QFocusEvent *event)
{
	//emit focusOut(event);
}

void UserInfoWidget::setUserHead()
{
    m_userInfo = m_usercontrol->GetAccountInfo();
    QString userImg = QString::fromLocal8Bit(m_userInfo.get()->avatar.value().data());
    if (userImg.isEmpty())
    {
        userImg = QString::fromLocal8Bit(m_userInfo.get()->thumbAvatar.value().data());
        if (userImg.isEmpty()){
            m_headImage.setHeadImg(":/base/default_head");
        }else{
            m_headImage.setHeadImg(userImg);
        }
    }
    else
    {
        m_headImage.setHeadImg(userImg);
    }

    emit signalOrgID(m_userInfo->id.value());
}


void UserInfoWidget::onHeadImgClicked(/*QMouseEvent *ev*/)
{
	if (m_selImgWidget == NULL)
	{
		m_selImgWidget = new SelectHeadImgWidget;
		connect(m_selImgWidget,SIGNAL(signalUserHeadSucc(QString)),this,SLOT(onUserHeadSucc(QString)),Qt::QueuedConnection);
	}
	AddLog(LOG_LEV_INFO,"====x:%d---y:%d",this->mapToGlobal(QPoint(this->x(),this->y())).x(),this->mapToGlobal(QPoint(this->x(),this->y())).y());
	int x = this->mapToGlobal(QPoint(this->x(),this->y())).x();
	int y = this->mapToGlobal(QPoint(this->x(),this->y())).y();
	m_selImgWidget->setHeadType(1);
	m_selImgWidget->setFixedSize(600,450);
	m_selImgWidget->setObjectName("widgetHead");
	m_selImgWidget->setFocus();
	m_selImgWidget->show();
}
void UserInfoWidget::onUserHeadSucc(QString headImg)
{
	m_headImage.setHeadImg(headImg);
	emit signalUserHeadSucc(headImg);
}

void UserInfoWidget::ShowInfo()
{
	m_headImage.setHeadImg(QString::fromLocal8Bit(utils::GetHeadPath(m_userInfo->gender.value(), m_userInfo->thumbAvatar.value()).c_str()));
    this->show();
}

void UserInfoWidget::onUpdateUserInfoResult( int code )
{
	ShowInfo();
}

}