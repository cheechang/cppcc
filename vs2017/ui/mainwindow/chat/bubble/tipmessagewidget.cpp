#include "tipmessagewidget.h"
#include "common/ChineseInfos.hpp"
#include "detail/textutils.h"
#include "common/MsgTimeDeal.hpp"
#include <QLabel>
class TipMessageWidgetPrivate
{
public:
	void init();
	TipMessageWidget* q_ptr;
	QLabel* m_label;
};

void TipMessageWidgetPrivate::init()
{
	m_label = new QLabel(q_ptr);
	m_label->setStyleSheet("background-color:transparent;color:gray;");
	m_label->setFrameShape(QFrame::NoFrame);
	m_label->setScaledContents(false);
	m_label->setWordWrap(true);
	m_label->setAlignment(Qt::AlignCenter);
	q_ptr->setCentralWidget(m_label);
}
TipMessageWidget::TipMessageWidget(QWidget* parent):AbstractMessageWidget(parent)
{
	m_groupcontrol = GROUPMGRCONTROL;
	d_ptr = new TipMessageWidgetPrivate;
	d_ptr->q_ptr = this;
	d_ptr->init();
}
TipMessageWidget::~TipMessageWidget()
{
	delete d_ptr;
}
QSize TipMessageWidget::suggestWidth(int width)
{
	int availableTextSpace = width - 50;//width - 50 - 16;(2020年8月26日)
	const QFontMetrics& fm = d_ptr->m_label->fontMetrics();
	int textWidth = fm.width(d_ptr->m_label->text());//
	int rowHeight = fm.height();
	int len = 0;
	int hei = rowHeight;
	QString txt = d_ptr->m_label->text();
	QString::iterator txtIter = txt.begin();
	int rows = 1; // default to 1
	int rowMaxWidth = 0;
	int charWidth = 0;
	int rowWidth = 0;
	bool multiline = false;
	while (txtIter != txt.end()) {
		charWidth = fm.width(*txtIter);
		len += charWidth;
		rowWidth += charWidth;

		if (len > availableTextSpace || *txtIter == '\n') {
			rowMaxWidth = qMax<int>(rowWidth, rowMaxWidth);
			rowWidth = 0;
			multiline = true;
			len = 0;
			++rows;
			hei += rowHeight + 30; // rowHeight + 12（2020年8月26日）line's top & bottom margin
		}
		++txtIter;
	}
	QSize sz((multiline ? rowMaxWidth : textWidth) + 50, hei+12);//+50，+6（2020年8月26日）
	return sz;
}
void TipMessageWidget::setTip(CSharedPtr<data::Msg>&msg){
	QString tipContent;
	if (CNull == msg) return;

	//文本消息发送
	if (!msg->isRecvMsg && !msg->isDeviceMsg && !msg->msgId)
	{
		setMsg(msg);
	}
	tipContent = dealTipMsg(msg);
	d_ptr->m_label->setText(tipContent);
	d_ptr->m_label->adjustSize();
}
QString  TipMessageWidget::dealTipMsg(CSharedPtr<data::Msg>&msg)
{
	data::MsgTip* tipMsg = (data::MsgTip*)(msg.get());
	QString result("");
	QString username("");
	QString operUsername("");
	QString userinfoname("");

	operUsername = QString::fromUtf8(tipMsg->operUser.data());
	userinfoname = QString::fromUtf8(tipMsg->userInfo.data());
	
	//阅后回执消息
	if (4 == tipMsg->tipType)
	{
		int64 tipTime = QString::fromUtf8(tipMsg->tipTime.c_str()).toLongLong();
		QString relayMsgTime = DealMsgTime(tipTime, 2);
		if (!tipMsg->isRecvMsg)
		{
			result.append(AUTO_REPLY_TIP_MSG);   //自动回复
			result.append(userinfoname);
			result.append(" ");
			result.append(relayMsgTime);
			result.append(AUTO_REPLY_REPIT_TIP_MSG);  //的阅后回执消息
		}
		else
		{
			std::vector<int64>::iterator itr = std::find(tipMsg->limitRange.begin(), tipMsg->limitRange.end(),tipMsg->userId);
			if (itr != tipMsg->limitRange.end() || tipMsg->isUser)
			{
				result.append(operUsername);
				result.append(AUTO_REPLY_REPIT_TIP_MSG);
			}
			else{
				if (m_user.selfName == userinfoname) {
					userinfoname = transfer("我");
				}
				result.append(operUsername);
				result.append(READED_MSG_TIP_MSG);   //已看过
				result.append(userinfoname);
				result.append(relayMsgTime);
				result.append(AUTO_REPLY_REPIT_TIP_MSG);  //的阅后回执消息
			}
		}
	}
	//橡皮擦
	else if (5 == tipMsg->tipType)
	{
		if (m_user.selfName == userinfoname) {
			userinfoname = transfer("我");
		}
		if (m_user.selfName == operUsername) {
			operUsername = transfer("我");
		}

		if (!tipMsg->isRecvMsg)
		{
			//1、表示同意删除 2、表示拒绝删除
			if (1 == tipMsg->operType)
			{
				result.append(ACCEPT_TIP_MSG); //您接受了
			}
			else if (2 == tipMsg->operType){
				result.append(REFUSE_MSG_TIP_MSG);  //您拒绝了
			}
			else{
				result.append(EARSER_MSG_TIP_MSG);  //橡皮擦弱提示消息
			}
			result.append(userinfoname);
			result.append(DEL_REQUEST_MSG_TIP_MSG);  //的删除请求
		}
		else
		{
			std::vector<int64>::iterator itr = std::find(tipMsg->limitRange.begin(), tipMsg->limitRange.end(), tipMsg->userId);
			if (itr != tipMsg->limitRange.end())
			{
				//1、表示同意删除 2、表示拒绝删除
				result.append(operUsername);
				if (1 == tipMsg->operType)
				{
					result.append(ACCEPT_DELREQUEST_MSG_TIP_MSG);  //接受了您的删除请求
				}
				else if (2 == tipMsg->operType){
					result.append(REFUSE_DELREQUEST_MSG_TIP_MSG);   //拒绝了您的删除请求
				}
				else{
					result.append(EARSER_MSG_TIP_MSG);  //橡皮擦弱提示消息
				}
			}
			else{
				result.append(operUsername);
				if (1 == tipMsg->operType)
				{
					result.append(ACCEPT_TIP_MSG.right(3));   //接受了
				}
				else if (2 == tipMsg->operType){
					result.append(REFUSE_MSG_TIP_MSG.right(3));   //拒绝了
				}
				else{
					result.append(EARSER_MSG_TIP_MSG);   //橡皮擦弱提示消息
				}
				result.append(userinfoname);
				result.append(DEL_REQUEST_MSG_TIP_MSG); //的删除请求
			}
		}
	}
	//抖一抖
	else if (6 == tipMsg->tipType||10 == tipMsg->tipType)
	{
		if (!tipMsg->isRecvMsg)
		{
			result.append(RESPONSE_TIP_MSG);   //我响应了
			result.append(userinfoname);
			result.append(SHAKE_TIP_MSG); //的抖一抖
		}
		else
		{
			std::vector<int64>::iterator itr = std::find(tipMsg->limitRange.begin(), tipMsg->limitRange.end(),tipMsg->userId);
			if (itr != tipMsg->limitRange.end() || tipMsg->isUser)
			{
				result.append(operUsername);
				result.append(RESPONSE_MYSHAKE_TIP_MSG);  //响应了我的抖一抖
			}
			else{
				result.append(operUsername);
				result.append(RESPONSE_TIP_MSG.right(3));	 //响应了
				result.append(userinfoname);
				result.append(SHAKE_TIP_MSG.right(3));  //的抖一抖
			}
		}
	}
	//红包
	else if (7 == tipMsg->tipType)
	{
		if (!tipMsg->isRecvMsg)
		{
			result.append(IGET_TIP_MSG);  //我领取了
			result.append(userinfoname);
			result.append(REDPACKET_TIP_MSG);   //的红包
		}
		else
		{
			std::vector<int64>::iterator itr = std::find(tipMsg->limitRange.begin(), tipMsg->limitRange.end(), tipMsg->userId);
			if (itr != tipMsg->limitRange.end())
			{
				result.append(operUsername);
				result.append(IGET_TIP_MSG.right(3));  //领取了
				result.append(MYREDPACKET_TIP_MSG);  //我的红包
			}
			else{
				int64 tipTime = QString::fromUtf8(tipMsg->tipTime.c_str()).toLongLong();
				QString time = DealMsgTime(tipTime, 2);
				result.append(YOUREDPACKET_TIP_MSG);      //您的红包
				result.append(time);
				result.append(ROB_TIP_MSG);   //秒内被抢完
				result.append(operUsername);
				result.append(LUCK_TIP_MSG);   //是红包运气王
			}
		}
	}
	//下载文件后发送的弱提示
	else if (8 == tipMsg->tipType)
	{
		result.append(TAREGET_RECEIVE_FILE);
		result.append(QString::fromUtf8(tipMsg->fileInfo.data()));
	}
	//群弱提示
	else if (3 == tipMsg->tipType)
	{
		////operType取值： 0：usersInfo加入该群 1：operUser邀请usersInfo加入该群 2：operUser同意usersInfo加入该群
		//3：usersInfo退出该群  4：usersInfo被operUser移除该群
		switch (tipMsg->operType)
		{
		case 0:
			{
				result.append(userinfoname+ GROUP_TIP_JION);
				break;
			}
		case 1:
			{
				result.append(operUsername + GROUP_TIP_IINVITE + userinfoname + GROUP_TIP_IINVITEJION);
				break;
			}
		case 2:
			{
				result.append(operUsername + GROUP_TIP_AGREE + userinfoname+GROUP_TIP_JION);
				break;
			}
		case 3:
			{
				result.append(userinfoname + GROUP_TIP_QUIT);
				break;
			}
		case 4:
			{
				if (utils::Error::IsChinese())
				{
					result.append(userinfoname + GROUP_TIP_BY + operUsername + GROUP_TIP_DELETE );
				}
				else 
				{
					result.append(operUsername + GROUP_TIP_REMOVED + userinfoname);
				}
				break;
			}
		case 5:
			{
				result.append(transfer("修改群名称：")+operUsername);
				break;
			}
		case 6:
		case 7:
		{
				  data::Member mem;
				  m_groupcontrol->GetMemberInfo(msg->targetId, msg->fromId, mem);
				  QString userName = QString::fromUtf8(mem.remark.value().c_str());
				  if (userName.isEmpty())
				  {
					  userName = QString::fromUtf8(mem.name.value().c_str());
				  }
				  if (tipMsg->operType == 6)
				  {
					  userName += transfer("新增一条置顶消息");
				  }
				  else{
					  userName += transfer("撤销一条置顶消息");
				  }
				  result.append(userName);
				  break;
		}
		default:
			result.append(QString::fromUtf8(tipMsg->body.data()));
			break;
		}
	}
	else{
		if (!tipMsg->tipType)
		{
			result.append(INVALID_TIP_MSG);
		}
		else{
			result.append(QString::fromUtf8(tipMsg->body.data()));
		}
	}

	return result;
}

void TipMessageWidget::initializeContextActions()
{

}

void TipMessageWidget::mousePressEvent( QMouseEvent *e )
{

}
