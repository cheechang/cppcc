#pragma  once
#include <memory>
#include <QString>
#include <interface/Defines.h>
namespace data{
	class Msg;
}
class QGraphicsTextItem;
class AbstractMessageWidget;
class IMsgFactory{
public:
	virtual AbstractMessageWidget* GetMessageWidget(CSharedPtr<data::Msg>&msg)=0;
	virtual QGraphicsTextItem* GetMessageTimeWidget(QString strtime) =0;  
};