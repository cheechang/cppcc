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
	int availableTextSpace = width - 50;//width - 50 - 16;(2020��8��26��)
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
			hei += rowHeight + 30; // rowHeight + 12��2020��8��26�գ�line's top & bottom margin
		}
		++txtIter;
	}
	QSize sz((multiline ? rowMaxWidth : textWidth) + 50, hei+12);//+50��+6��2020��8��26�գ�
	return sz;
}
void TipMessageWidget::setTip(CSharedPtr<data::Msg>&msg){
	QString tipContent;
	if (CNull == msg) return;

	//�ı���Ϣ����
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
	
	//�ĺ��ִ��Ϣ
	if (4 == tipMsg->tipType)
	{
		int64 tipTime = QString::fromUtf8(tipMsg->tipTime.c_str()).toLongLong();
		QString relayMsgTime = DealMsgTime(tipTime, 2);
		if (!tipMsg->isRecvMsg)
		{
			result.append(AUTO_REPLY_TIP_MSG);   //�Զ��ظ�
			result.append(userinfoname);
			result.append(" ");
			result.append(relayMsgTime);
			result.append(AUTO_REPLY_REPIT_TIP_MSG);  //���ĺ��ִ��Ϣ
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
					userinfoname = transfer("��");
				}
				result.append(operUsername);
				result.append(READED_MSG_TIP_MSG);   //�ѿ���
				result.append(userinfoname);
				result.append(relayMsgTime);
				result.append(AUTO_REPLY_REPIT_TIP_MSG);  //���ĺ��ִ��Ϣ
			}
		}
	}
	//��Ƥ��
	else if (5 == tipMsg->tipType)
	{
		if (m_user.selfName == userinfoname) {
			userinfoname = transfer("��");
		}
		if (m_user.selfName == operUsername) {
			operUsername = transfer("��");
		}

		if (!tipMsg->isRecvMsg)
		{
			//1����ʾͬ��ɾ�� 2����ʾ�ܾ�ɾ��
			if (1 == tipMsg->operType)
			{
				result.append(ACCEPT_TIP_MSG); //��������
			}
			else if (2 == tipMsg->operType){
				result.append(REFUSE_MSG_TIP_MSG);  //���ܾ���
			}
			else{
				result.append(EARSER_MSG_TIP_MSG);  //��Ƥ������ʾ��Ϣ
			}
			result.append(userinfoname);
			result.append(DEL_REQUEST_MSG_TIP_MSG);  //��ɾ������
		}
		else
		{
			std::vector<int64>::iterator itr = std::find(tipMsg->limitRange.begin(), tipMsg->limitRange.end(), tipMsg->userId);
			if (itr != tipMsg->limitRange.end())
			{
				//1����ʾͬ��ɾ�� 2����ʾ�ܾ�ɾ��
				result.append(operUsername);
				if (1 == tipMsg->operType)
				{
					result.append(ACCEPT_DELREQUEST_MSG_TIP_MSG);  //����������ɾ������
				}
				else if (2 == tipMsg->operType){
					result.append(REFUSE_DELREQUEST_MSG_TIP_MSG);   //�ܾ�������ɾ������
				}
				else{
					result.append(EARSER_MSG_TIP_MSG);  //��Ƥ������ʾ��Ϣ
				}
			}
			else{
				result.append(operUsername);
				if (1 == tipMsg->operType)
				{
					result.append(ACCEPT_TIP_MSG.right(3));   //������
				}
				else if (2 == tipMsg->operType){
					result.append(REFUSE_MSG_TIP_MSG.right(3));   //�ܾ���
				}
				else{
					result.append(EARSER_MSG_TIP_MSG);   //��Ƥ������ʾ��Ϣ
				}
				result.append(userinfoname);
				result.append(DEL_REQUEST_MSG_TIP_MSG); //��ɾ������
			}
		}
	}
	//��һ��
	else if (6 == tipMsg->tipType||10 == tipMsg->tipType)
	{
		if (!tipMsg->isRecvMsg)
		{
			result.append(RESPONSE_TIP_MSG);   //����Ӧ��
			result.append(userinfoname);
			result.append(SHAKE_TIP_MSG); //�Ķ�һ��
		}
		else
		{
			std::vector<int64>::iterator itr = std::find(tipMsg->limitRange.begin(), tipMsg->limitRange.end(),tipMsg->userId);
			if (itr != tipMsg->limitRange.end() || tipMsg->isUser)
			{
				result.append(operUsername);
				result.append(RESPONSE_MYSHAKE_TIP_MSG);  //��Ӧ���ҵĶ�һ��
			}
			else{
				result.append(operUsername);
				result.append(RESPONSE_TIP_MSG.right(3));	 //��Ӧ��
				result.append(userinfoname);
				result.append(SHAKE_TIP_MSG.right(3));  //�Ķ�һ��
			}
		}
	}
	//���
	else if (7 == tipMsg->tipType)
	{
		if (!tipMsg->isRecvMsg)
		{
			result.append(IGET_TIP_MSG);  //����ȡ��
			result.append(userinfoname);
			result.append(REDPACKET_TIP_MSG);   //�ĺ��
		}
		else
		{
			std::vector<int64>::iterator itr = std::find(tipMsg->limitRange.begin(), tipMsg->limitRange.end(), tipMsg->userId);
			if (itr != tipMsg->limitRange.end())
			{
				result.append(operUsername);
				result.append(IGET_TIP_MSG.right(3));  //��ȡ��
				result.append(MYREDPACKET_TIP_MSG);  //�ҵĺ��
			}
			else{
				int64 tipTime = QString::fromUtf8(tipMsg->tipTime.c_str()).toLongLong();
				QString time = DealMsgTime(tipTime, 2);
				result.append(YOUREDPACKET_TIP_MSG);      //���ĺ��
				result.append(time);
				result.append(ROB_TIP_MSG);   //���ڱ�����
				result.append(operUsername);
				result.append(LUCK_TIP_MSG);   //�Ǻ��������
			}
		}
	}
	//�����ļ����͵�����ʾ
	else if (8 == tipMsg->tipType)
	{
		result.append(TAREGET_RECEIVE_FILE);
		result.append(QString::fromUtf8(tipMsg->fileInfo.data()));
	}
	//Ⱥ����ʾ
	else if (3 == tipMsg->tipType)
	{
		////operTypeȡֵ�� 0��usersInfo�����Ⱥ 1��operUser����usersInfo�����Ⱥ 2��operUserͬ��usersInfo�����Ⱥ
		//3��usersInfo�˳���Ⱥ  4��usersInfo��operUser�Ƴ���Ⱥ
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
				result.append(transfer("�޸�Ⱥ���ƣ�")+operUsername);
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
					  userName += transfer("����һ���ö���Ϣ");
				  }
				  else{
					  userName += transfer("����һ���ö���Ϣ");
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
