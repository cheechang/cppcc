#pragma  once
#include <memory>
#include <vector>
#include <QString>
#include "IMsgFactory.h"
#include "common/Common.h"
namespace data{
	class Msg;
	class Member;
}
class QGraphicsTextItem;
class AbstractMessageWidget;
class FlexMessageWidget;
class MsgFactory:public IMsgFactory{
public:
	MsgFactory();
	virtual ~MsgFactory();

	AbstractMessageWidget* GetMessageWidget(CSharedPtr<data::Msg>&msg);
	FlexMessageWidget*     GetFlexMessageWidget(AbstractMessageWidget*&absmsg);
	QGraphicsTextItem*     GetMessageTimeWidget(QString strtime);
};