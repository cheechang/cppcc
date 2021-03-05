#pragma once

#include <core/BaseDialog.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include "common/Controlptr.h"
#include <data/SearchData.h>
namespace ui{
	class PushButton;
	class HeadImage;
	class AddContactWindow : public BaseDialog
	{
		Q_OBJECT

	public:
		AddContactWindow(QWidget *parent=CNull);
		~AddContactWindow();
		void InitData(const data::SearchResultInfo& dataInfo);
		void InitDatas(std::vector<data::SearchResultInfo>& dataInfo);
	protected slots:
		void onOkBtnClicked();
		void onCancelBtnClicked();
		void onSerGetUserVerifyType(int err, data::ContactVerifyType& verifyType);
		void onSerAddContact(int err);
		void onSerGetGroupVerifyType(int err, int8 verifyType, int8 isInvite);
	signals:
		void signalSerGetUserVerifyType(int err, data::ContactVerifyType& verifyType);
		void signalSerAddContact(int err);
		void signalSerGetGroupVerifyType(int err, int8 verifyType, int8 isInvite);
		void signalSerAddFriden();
	private:
		void setAttribute();
		void layout();
		int64 m_id;
		std::vector<int64> mVectorId;
		int type; //0:单加好友 1：批量加好友
		QHBoxLayout*	m_pTitleBtnLayout;		//标题栏按钮布局
		QVBoxLayout* m_pMainLayout;  
		QLabel*			m_pBackground;			//背景图片
		PushButton*		m_pCloseButton;			//关闭

		QLabel* m_pLblName;
		HeadImage* m_pImgHead;
		QLabel*       m_verifyTipLbl;
		QTextEdit*     m_verifyInfoEdit;   //验证信息输入
		QLabel*        m_remarkTipLbl;
		QLineEdit*      m_pRemakLineEdit;   //备注
		QLabel*			m_pTitle;
		QPushButton*    m_pBtnOk;
		QPushButton*    m_pBtnCancel;
	
		IUserControl_Ptr m_usercontrol;
		IContactMgrControl_Ptr m_contactControl;
		IGroupMgrControl_Ptr m_groupControl;
	};
	
}
