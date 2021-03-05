#ifndef SELECTMEMBERITEMWIDGET_H
#define SELECTMEMBERITEMWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include "../../controls/TWidget.h"
#include "data/UserData.h"
namespace ui{
	class HeadImage;
	class ToolButton;
	class PushButton;
	/**
	** ÁÐ±íÏî
	**/
	class SelectMemberItemWidget:public TWidget{
		Q_OBJECT
	public:
		SelectMemberItemWidget(QWidget *parent =CNull,bool canDel=false);
		~SelectMemberItemWidget();

		void setData(int64 id,QString name,QString JbZbTip,QString avatar,bool isChecked=false);
		void setData(data::UserBasicData data);
		data::UserBasicData data(){return mData;}
		bool isSelect();
		QString id(){return QString::number(mId);}
		int64 GetId(){return mId;}
		void showNameOnly();
		void setCheckboxEnabled(bool enabled,bool isCheck);
		void SetChecked(bool isTrue);
	signals:
		void deleteClicked(QString id);
		void signalSerShowUserInfo(int64,QString,QString,std::string);
	protected slots:
		void onDeleteClicked();
		void onSerShowUserInfo();
	protected:
		void enterEvent(QEvent *e);
		void leaveEvent(QEvent *e);
	protected:
		bool mCanDel;
		int64 mId;
		data::UserBasicData mData;
		QLabel* mName;
		QCheckBox*mCheckBox;
		HeadImage* mHead;
		PushButton*mBtnDel;
		QLabel* mJbZblbl;

		QString mStrName;
		QString mAvatar;
		std::string mJsUserInfo;
	};
}

#endif // SELECTMEMBERITEMWIDGET_H
