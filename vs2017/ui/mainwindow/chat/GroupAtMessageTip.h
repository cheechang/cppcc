#ifndef GROUPATMESSAGETIP_H
#define GROUPATMESSAGETIP_H
#include <QHBoxLayout>
#include <QLabel>

#include "../controls/TWidget.h"
#include "interface/Defines.h"
#include "../controls/headimage.h"
#include "../controls/PushButton.h"
#include "../controls/ElidedLabel.h"
namespace ui{
	class GroupAtMessageTip : public TWidget
	{
		Q_OBJECT

	public:
		GroupAtMessageTip(QWidget *parent=CNull);
		~GroupAtMessageTip();
		void setData(QString avatar,QString msgContent);
	private:
		ElidedLabel* mNameAndMsg;
		HeadImage* mAvatar;
		PushButton* mBtnDel;
	};
}

#endif // GROUPATMESSAGETIP_H
