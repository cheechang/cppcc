#include "SelectHeadImgWidget.h"
#include "Log.h"
#include <../../common/Connect.h>
#include <json.h>
#include "../common/Common.h"

namespace ui{
	SelectHeadImgWidget::SelectHeadImgWidget(TWindow *parent)
		: TWindow(parent)
	{
		m_lbTitle.setParent(this);
		m_lbTitle.setText(transfer("  修改头像"));
		//m_lbTitle.setAlignment(Qt::AlignLeft);
		m_lbTitle.resize(600, 30);//580，30（2020年8月31日）
		m_lbTitle.move(10,10);
		connect(&m_lbTitle, SIGNAL(mouseMoveTo(QPoint)), this, SLOT(onMouseMove(QPoint)));
		connect(&m_lbTitle, SIGNAL(closeClicked()), this, SLOT(onBtnClose()));

		AddLog(LOG_LEV_INFO,"-----------x:%d-y:%d-w:%d-h:%d-----------", this->x(), this->y(), this->width(), this->height());

		m_leftBgRect.setMinSize(330, 330);
		connect(&m_leftBgRect, SIGNAL(clipImgSucc(QString, QString)), this, SLOT(onClipImgSucc(QString, QString)));


		m_img150x150.setAvatarPath(":/base/app_default");
		m_img150x150.setFixedHeight(150);
		m_img150x150.setFixedWidth(150);
		m_lb150x150.setText(transfer("150x150像素"));
		m_lb150x150.setAlignment(Qt::AlignHCenter);
		m_img40x40.setAvatarPath(":/base/app_default");
		m_img40x40.setFixedHeight(40);
		m_img40x40.setFixedWidth(40);
		m_lb40x40.setText(transfer("40x40像素"));
		m_lb40x40.setAlignment(Qt::AlignHCenter);

		m_img150x150.setVisible(false);
		m_lb150x150.setVisible(false);
		m_img40x40.setVisible(false);
		m_lb40x40.setVisible(false);

		m_SelLayout.addWidget(&m_leftBgRect,1,Qt::AlignCenter);

		m_contentLayout.addWidget(&m_img150x150,0,Qt::AlignHCenter);
		m_contentLayout.addWidget(&m_lb150x150,0,Qt::AlignHCenter);
		m_contentLayout.addWidget(&m_img40x40,0,Qt::AlignHCenter);
		m_contentLayout.addWidget(&m_lb40x40,0,Qt::AlignHCenter);

		m_SelLayout.addLayout(&m_contentLayout);
		//m_SelLayout.setMargin(20);

		//m_mainLayout.addWidget(&m_lbTitle);
		m_mainLayout.addSpacing(50);
		m_mainLayout.addLayout(&m_SelLayout);
		m_mainLayout.addStretch();

		m_btnOK.setParent(this);
		m_btnOK.setText(transfer("确定"));
		m_btnOK.setFixedHeight(30);
		m_btnOK.setFixedWidth(70);
		m_btnOK.setObjectName("updateOk");
		m_btnOK.move(600-180, 450-50);
		connect(&m_btnOK, SIGNAL(clicked()), this, SLOT(onBtnOK()));

		m_btnCancel.setParent(this);
		m_btnCancel.setText(transfer("取消"));
		m_btnCancel.setFixedHeight(30);
		m_btnCancel.setFixedWidth(70);
		m_btnCancel.setObjectName("updateCancel");
		/*m_btnCancel.setStyleSheet("background-color: rgb(255, 255, 255);color:#AAAAAA;\
		border-color: #A6A6A6;\
		border-width: 1px;\
		border-style: solid;");*/
		m_btnCancel.move(600-100, 450-50);
		connect(&m_btnCancel, SIGNAL(clicked()), this, SLOT(onBtnClose()));

		setLayout(&m_mainLayout);

		m_usercontrol = USERCONTROL;
		m_authcontrol = AUTHCONTROL;
		CONNECT_SERVICE(SetHead(int, const std::string&, const std::string&));
		CONNECT_SERVICE(SetUserInfoHead(int));
	}

	SelectHeadImgWidget::~SelectHeadImgWidget()
	{

	}
	void SelectHeadImgWidget::onBtnClose()
	{
		m_leftBgRect.setBtnVisible(true);
		close();
	}
	void SelectHeadImgWidget::onBtnOK()
	{
        m_btnOK.setEnabled(false);
		m_leftBgRect.onBtnSaveImg();
	}
	void SelectHeadImgWidget::onMouseMove(QPoint p)
	{
		this->move(this->x()+p.x(),this->y()+p.y());
	}
	void SelectHeadImgWidget::onClipImgSucc(QString file400, QString file150)
	{
		file400 = file400.replace('\\','/');
		emit signalUserHeadSucc(file400);

		//应该传入本地下载下来的头像地址
		if (m_type == 1)
		{
			data::AuthInfo info;
			info.avatar = file400.toUtf8().data();
			m_authcontrol->setLoginInfo(info);
		}
		
		m_usercontrol->uploadUserHead(file400.toStdString(), file150.toStdString(),CBind(&SelectHeadImgWidget::signalSerSetHead, this, CPlaceholders  _1, CPlaceholders  _2, CPlaceholders  _3));
	}

	void SelectHeadImgWidget::setHeadType(int type)
	{
		m_type = type;
	}

	void SelectHeadImgWidget::onSerSetHead(int code, const std::string& src, const std::string& thumb)
	{
		//src json
		//thumb json
		Json::Reader reader;
		Json::Value root;
		bool ret = reader.parse(src.c_str(),root);
		if(ret){
			Json::Value obj = root["files"][0];
			Json::Value srcJson = obj["images"][0];
			std::string srcUrl = srcJson["url"].asCString();
			
			//Json::Value objThumb = root["files"][0];
			//Json::Value thumbJson = obj["images"][0];
			//std::string thumbUrl = srcJson["url"].asCString();
			
			if (m_type == 1)
			{
				data::AccountInfo userInfo;
				userInfo.id = m_usercontrol->GetAccountInfo()->id.value();
				userInfo.avatarUrl = srcUrl;
				userInfo.avatar = srcUrl;
				userInfo.thumbAvatarUrl = srcUrl;
				userInfo.thumbAvatar = srcUrl;
				m_usercontrol->updateAccountInfo(userInfo, CBind(&SelectHeadImgWidget::signalSerSetUserInfoHead, this, CPlaceholders  _1));
			}
			
			if (m_type == 2)
			{
				emit signalSerModifyGroupHead(srcUrl);
			}
		
		}
		else {
			m_btnOK.setEnabled(true);  // 2019-5-20 bxy change
		}
	}
	void SelectHeadImgWidget::onSerSetUserInfoHead(int code)
	{
		m_leftBgRect.setBtnVisible(true);
        m_btnOK.setEnabled(true);
		onBtnClose();
	}
}