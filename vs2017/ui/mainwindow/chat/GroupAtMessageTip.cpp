#include "GroupAtMessageTip.h"

namespace ui
{
	GroupAtMessageTip::GroupAtMessageTip(QWidget* parent)
		: TWidget(parent)
	{
		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		mainLayout->setContentsMargins(6, 0, 10, 0);

		mAvatar = new HeadImage(this, QSize(20, 20));
		mNameAndMsg = new ElidedLabel(this);
		mNameAndMsg->setMinimumWidth(600);//520£¨2020Äê8ÔÂ31ÈÕ£©
		mBtnDel = new PushButton(this);
		mBtnDel->setPicName(":/chat/delete");
		connect(mBtnDel,SIGNAL(clicked(bool)), this,SLOT(hide()));

		mainLayout->addWidget(mAvatar);
		mainLayout->addWidget(mNameAndMsg, 0, Qt::AlignVCenter);
		mainLayout->addStretch();
		mainLayout->addWidget(mBtnDel, 0, Qt::AlignHCenter | Qt::AlignRight);

		setLayout(mainLayout);
	}

	GroupAtMessageTip::~GroupAtMessageTip()
	{
	}

	void GroupAtMessageTip::setData(QString avatar, QString msgContent)
	{
		mAvatar->setAvatarPath(avatar);
		mNameAndMsg->setText(msgContent);
	}
}
