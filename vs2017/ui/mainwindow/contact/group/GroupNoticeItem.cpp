#include "GroupNoticeItem.h"
#include "controls/headimage.h"
#include "common/Common.h"
#include "common/UIUtils.h"
#include <QDateTime>

namespace ui{
	GroupNoticeItem::GroupNoticeItem(QWidget *parent)
		: TWidget(parent)
	{
		m_pChatControl = CHATMGRCONTROL;
		
		m_MainLayout = new QVBoxLayout(this);
		m_pNomination = new QLabel(this);
		m_pNomination->setObjectName("NoticeNominationlbl");
		m_pNomination->setFixedHeight(30);
		m_pNomination->setAlignment(Qt::AlignRight);

	//	m_pLabelNoticeContent = new QLabel(this);
		m_pLabelNoticeContent = new QTextEdit(this);
		m_pLabelNoticeContent->setReadOnly(true);
		m_pLabelNoticeContent->setObjectName("chatedit");
		
		m_pLabelNoticeContent->setMaximumHeight(200);//150(2020年8月31日)
		m_pLabelNoticeContent->setFixedWidth(400);
		m_pLabelNoticeContent->adjustSize();//自动调整大小~无效（2020年8月31日）
		m_pLabelNoticeContent->setObjectName("NoticeShowLabel");//
		/*m_pLabelNoticeContent->setWordWrap(true);
		m_pLabelNoticeContent->setMargin(2);
		m_pLabelNoticeContent->setIndent(2);*/
		m_MainLayout->addWidget(m_pLabelNoticeContent);
		m_MainLayout->addWidget(m_pNomination);
		m_MainLayout->setSpacing(0);
		m_MainLayout->setContentsMargins(1,0,1,1);//居中靠上
		setLayout(m_MainLayout);
		this->setFixedWidth(400);
	}

	GroupNoticeItem::~GroupNoticeItem()
	{
		
	}

	void GroupNoticeItem::setData(const data::Group& pGroupInfo)
	{
		QString NoticeContent = "      " + QString::fromUtf8(pGroupInfo.bulletin.value().c_str());
		m_pLabelNoticeContent->setText(NoticeContent);
	}

	void GroupNoticeItem::setNominition(std::string name)
	{
		int AllTime = QDateTime::currentDateTime().toTime_t();
		QString datestr = QDateTime::fromTime_t(AllTime).toString("yyyy-MM-dd hh:mm");
		datestr = QString::fromUtf8(name.c_str()) + transfer(" 发表于") + "  " + datestr+ "  ";
		m_pNomination->setText(datestr);
	}

	int GroupNoticeItem::getContentHigh()
	{
		int fontH = m_pLabelNoticeContent->fontMetrics().height();
		int height = fontH;
		int width = m_pLabelNoticeContent->fontMetrics().width(m_pLabelNoticeContent->toPlainText());
		int maxWidth = 400;//395（2020年8月31日）
		if (width>maxWidth){
			int rowcount = width / maxWidth;
			int dx = width%maxWidth;
			if (dx != 0){
				rowcount += 1;
			}
			height = fontH*rowcount+5;
		}
		else{
			height = fontH + 6;
		}

		if (height > 150)
		{
			m_pLabelNoticeContent->resize(250, maxWidth);//150（2020年8月31日）
		}
		else{
			m_pLabelNoticeContent->resize(height+100, maxWidth);//height （2020年8月31日）
		}
		return height;
	}

	QSize GroupNoticeItem::GetSizeByContent(int pwidth)//根据内容调整大小
	{
		int availableTextSpace = pwidth;// - 50 - 16;
		const QFontMetrics& fm = m_pLabelNoticeContent->fontMetrics();
		//int textWidth = fm.width(m_pLabelNoticeContent->text());
		int textWidth = fm.width(m_pLabelNoticeContent->toPlainText());
		int rowHeight = fm.height();
		int len = 0;
		int hei = rowHeight;
		QString txt = m_pLabelNoticeContent->toPlainText();
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
				hei += rowHeight + 25; // 12 无效（2020年8月31日）line's top & bottom margin
			}
			++txtIter;
		}
		QSize sz((multiline ? rowMaxWidth : textWidth), hei+60);//40（2020年8月31日）
		//QSize sz((multiline ? rowMaxWidth : textWidth) + 50, hei+6);
		return sz;
	}


}
