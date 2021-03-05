#include "richtextmessagewidget.h"
#include "detail/mtextedit.h"
#include "detail/textutils.h"
#include "flexaction.h"
#include "data/ChatData.h"
#include "controls/ChatEdit.h"
#include "MsgBubbleConfig.h"
#include <regex>
#include <QMenu>
#include <QLabel>
#include <QDebug>
#include <QMimeData>
#include <QTextDocument>
#include <QScrollBar>
#include <QAbstractTextDocumentLayout>
#include "control/chatmgrcontrol/GlobalDef.h"
#include <QApplication>
#include <QClipboard>
class RichTextMessageWidgetPrivate
{
public:
    void init();
    RichTextMessageWidget* q_ptr;
    ui::ChatEdit * textEdit;
};

void RichTextMessageWidgetPrivate::init()
{
    textEdit = new ui::ChatEdit(q_ptr,true);
    textEdit->document()->setDocumentMargin(3);
	textEdit->setContentsMargins(0,0,0,0);
    textEdit->setStyleSheet("background-color:transparent;");
    textEdit->setFrameShape(QFrame::NoFrame);
	textEdit->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	textEdit->setAcceptDrops(false);
    q_ptr->setCentralWidget(textEdit);
	textEdit->setReadOnly(true);
}

RichTextMessageWidget::RichTextMessageWidget(QWidget* parent) : AbstractMessageWidget(parent),m_iscontainsemoji(false),
m_emojicount(0)
{
    d_ptr = new RichTextMessageWidgetPrivate;
    d_ptr->q_ptr = this;
    d_ptr->init();
	this->setAcceptDrops(false);
	CONNECT_SERVICE(RecallEdit());
	connect(d_ptr->textEdit,SIGNAL(noticeInputEditFocus()),this,SIGNAL(noticeInputEditFocus()));
}

RichTextMessageWidget::~RichTextMessageWidget()
{
    delete d_ptr;
}
void RichTextMessageWidget::setText(CSharedPtr<data::Msg>&msg)
{
	qint32 sat = 0;
	QString text("");
	AbstractMessageWidget::setMsg(msg);
	if (CNull == msg) return;

	text = QString::fromUtf8(msg->body.c_str());
	text = expressParseFrom(text.toUtf8().data());
	if (text == SHAKE_TEXT)
	{
		text = transfer("抖一抖");
	}
	else if (text.contains(SHAKE_TEXT)){
		text = text.remove(SHAKE_TEXT);
	}

	//文本消息发送
	if (!msg->isRecvMsg && !msg->isDeviceMsg && !msg->msgId)
	{
		QString sendtext = QString::fromUtf8(msg->body.c_str());
		sendtext = expressParseFrom(sendtext.toUtf8().data(),true);
		msg->body =sendtext.toUtf8().data();
		setMsg(msg);
	}
	if (m_iscontainsemoji)
	{
		d_ptr->textEdit->insertHtml(text);
	}
	else{
		if (d_ptr->textEdit->hasWebUrl(text)){
			
			if (borderColor() == MsgBubbleConfig::selfBubbleColor())
			{
				d_ptr->textEdit->setContentSrc(false);
			}
			else{
				d_ptr->textEdit->setContentSrc(true);
			}
			d_ptr->textEdit->setWebUrlContext(text);
		}
		else{
			d_ptr->textEdit->setText(text);
		}
	}
	mMsgText = text;
	mRightMenu.setMenuState(MENU_COPY,true);
	if (!msg->isRecvMsg&&msg->isBurn)
	{
		mRightMenu.setMenuState(MENU_RECALL,false);
		mRightMenu.setMenuState(MENU_TRANSPORT,false);
		mRightMenu.setMenuState(MENU_COPY,false);
	}
	if(!msg->isRecvMsg)
	{
		mRightMenu.setMenuState(MENU_RECALLEDIT,true);
	}
	connect(&mRightMenu,SIGNAL(signalCtrlCopyMenu(qint64,qint64)),this,SLOT(onCopyMsg()));
}

QString RichTextMessageWidget::text() const
{
    return d_ptr->textEdit->toPlainText();
}

void RichTextMessageWidget::setFont(const QFont &f)
{
    d_ptr->textEdit->setFont(f);
}

QFont RichTextMessageWidget::font() const
{
    return d_ptr->textEdit->font();
}

void RichTextMessageWidget::setTextColor(const QColor& clr)
{
    d_ptr->textEdit->setStyleSheet(TextUtils::textColorStyle(clr));
}

QColor RichTextMessageWidget::textColor() const
{
    return d_ptr->textEdit->textColor();
}

int getDivisionValue(int x,int y)
{
	return ceil(((float)x)/y);
}
QSize RichTextMessageWidget::suggestWidth(int width)
{
	QSize sz;
	int hei =0;
	int wid = 0;
	int textMaxWidth = 0;
    int textSpace =width - 50 -16; // 50px for the angle, 16px for left & right margins
	QTextEdit *editor=d_ptr->textEdit; 
	QTextDocument *document=editor->document();
	if(document){
		QSizeF size;
		document->adjustSize();
		QSizeF sizeContent = document->size();

		textMaxWidth = TextUtils::textWidth(textSpace,editor->toPlainText(),editor->fontMetrics());
		if(textMaxWidth<textSpace){
			document->setTextWidth(textMaxWidth);
			size = document->size();
		}
		else{
			document->setTextWidth(textSpace);
			size = document->size();
		}
		int newHeight = size.height()+5;
		int newWidth  = size.width();
		editor->setFixedSize(newWidth,newHeight);
		editor->updateGeometry();
	}
	sz = this->sizeHint()-QSize(30,0);
	this->setFixedSize(sz);
	return sz;
}

int RichTextMessageWidget::type() const
{
    return 4;
}

void RichTextMessageWidget::initializeContextActions()
{
    AbstractMessageWidget::initializeContextActions();
}
QString RichTextMessageWidget::expressParseFrom(std::string srcText,bool issendmsg)
{
	std::regex				regexpress(EMOJI_REG);					//匹配表情正则表达式变量
	std::smatch				find;
	std::string::const_iterator begin;
	std::string::const_iterator	end;
	std::string					strFind = "";
	std::string strPath("");
	std::string					strResult = "";
	std::string replace(srcText);
	QString tempReplace = QString::fromUtf8(replace.c_str());
	//查找表情路径
	begin = srcText.begin();
	end = srcText.end();

	while (std::regex_search(begin, end, find, regexpress))
	{
		QString fmt("");
		begin = find[0].second;
		//提取表情路径
		strFind = find[1];
		strPath = find[2];
		if (strPath.empty()){
			continue;
		}
		if (!issendmsg)
		{
			fmt = "<img src=\"%1\" width=\"24\" height=\"24\"/>";
			fmt = fmt.arg(QString::fromUtf8(strPath.c_str()));
		}
		else{
			fmt.append(QString::fromLocal8Bit(EMOJI_IMAGE));
			fmt.append(QString::fromStdString(strPath));
			fmt.append(QString::fromLocal8Bit(EMOJI_IMAGE));
		}
		m_iscontainsemoji = true;
		++m_emojicount;
		tempReplace.replace(QString::fromUtf8(strFind.c_str()),fmt);
	}
	return tempReplace;
}

void RichTextMessageWidget::onCopyMsg()
{
	QString selectedText = d_ptr->textEdit->textCursor().selectedText();
	if(selectedText.isEmpty()){
	   d_ptr->textEdit->selectAll();
	}
	d_ptr->textEdit->copy();
	d_ptr->textEdit->setCursorWidth(0);
}

void RichTextMessageWidget::onSerRecallEdit()
{
	QString text("");
	if(NULL == msg())
		return;
	text = QString::fromUtf8(msg()->body.c_str());
	text = expressParseFrom(text.toUtf8().data());
	emit signalSerRecallEdit(text);
}
