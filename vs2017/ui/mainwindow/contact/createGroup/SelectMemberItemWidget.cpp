#include "SelectMemberItemWidget.h"
#include "../../controls/headimage.h"
#include "../../controls/PushButton.h"
#include "Json.h"
namespace ui{
	SelectMemberItemWidget::SelectMemberItemWidget( QWidget *parent /*=CNull*/ ,bool canDel):TWidget(parent)
	{
		mHead = new HeadImage(this,QSize(40,40));
		mName = new QLabel(this);
		mName->setObjectName("HighNamelbl");		
		mCheckBox = new QCheckBox(this);

		QHBoxLayout* layout = new QHBoxLayout(this);
		//加组别界别界面
		QVBoxLayout* TipLoayout = new QVBoxLayout(this);
		mJbZblbl = new QLabel(this);
		mJbZblbl->setObjectName("HighJblbl");
		TipLoayout->addWidget(mName,0,Qt::AlignLeft);
		TipLoayout->addWidget(mJbZblbl, 0, Qt::AlignLeft);
		TipLoayout->setSpacing(0);
		TipLoayout->setContentsMargins(0,5,0,3);

		layout->addWidget(mHead);
		layout->addLayout(TipLoayout);
		layout->addWidget(mCheckBox,0,Qt::AlignRight);
		layout->setContentsMargins(10,0,20,0);

		mBtnDel = new PushButton(this);
		mBtnDel->setPicName(":/chat/delete");
		mBtnDel->setVisible(false);
		layout->addWidget(mBtnDel,0,Qt::AlignRight);
		connect(mBtnDel,SIGNAL(clicked(bool)),this,SLOT(onDeleteClicked()));
		if(canDel){
			mCheckBox->setVisible(false);
		}
		mCanDel = canDel;

		setLayout(layout);

		connect(mHead, SIGNAL(clicked(QPoint)), this, SLOT(onSerShowUserInfo()));
	}

	SelectMemberItemWidget::~SelectMemberItemWidget()
	{
	}

	void SelectMemberItemWidget::setData( int64 id,QString name,QString JbZbTip, QString avatar,bool isChecked/*=false*/ )
	{
		mId = id;
		mStrName = name;
		mAvatar = avatar;
		mName->setText(name);
		if(JbZbTip.size() > 16)
		{
			mJbZblbl->setToolTip(JbZbTip);
			JbZbTip = JbZbTip.mid(0,16) + "...";
		}
		mJbZblbl->setText(JbZbTip);
		mCheckBox->setChecked(isChecked);
		mHead->setAvatarPath(avatar);
	}

	void SelectMemberItemWidget::setData( data::UserBasicData data )
	{
		mData = data;
		std::string Extents = data.extends.value();
		mJsUserInfo = Extents;
		QString tsector;
		QString tgroup;
		Json::Reader reader;
		Json::Value obj;
		
		if (reader.parse(Extents, obj))
		{
			if(obj.isArray())
			{
				for(int i=0; i<obj.size();i++)
				{
					if(obj[i]["sector"].isString())
					{
						tsector = QString::fromUtf8(obj[i]["sector"].asCString());
					}

					if(obj[i]["group"].isString())
					{
						tgroup = QString::fromUtf8(obj[i]["group"].asCString());
					}
				}
			}
		}
		QString tjbzb = tsector + "  " + tgroup;
			setData(data.id.value(),
			QString::fromStdString(data.name.value()),
			tjbzb,
			QString::fromStdString(data.thumbAvatar.value()));
	}

	bool SelectMemberItemWidget::isSelect()
	{
		return mCheckBox->isChecked()&&mCheckBox->isEnabled();
	}

	void SelectMemberItemWidget::enterEvent(QEvent *e)
	{
		if(mCanDel){
			mBtnDel->setVisible(true);
		}
		//e->accept();
	}

	void SelectMemberItemWidget::leaveEvent(QEvent *e)
	{   
		if(mCanDel){
			mBtnDel->setVisible(false);
		}
		//e->accept();
	}

	void SelectMemberItemWidget::onDeleteClicked()
	{
		mBtnDel->setEnabled(false);
		emit deleteClicked(QString::number(mId));
	}

	void SelectMemberItemWidget::showNameOnly()
	{
		mCheckBox->setVisible(false);
		mHead->setVisible(false);
	}

	void SelectMemberItemWidget::setCheckboxEnabled( bool enabled,bool isCheck )
	{
		mCheckBox->setChecked(isCheck);
		mCheckBox->setEnabled(enabled);
	}

	void SelectMemberItemWidget::SetChecked(bool isTrue)
	{
		mCheckBox->setChecked(isTrue);
	}

	void SelectMemberItemWidget::onSerShowUserInfo()
	{
		emit signalSerShowUserInfo(mId, mStrName, mAvatar, mJsUserInfo);
	}

}
