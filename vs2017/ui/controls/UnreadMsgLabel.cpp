#include "UnreadMsgLabel.h"
#include <QPainter>
#include <QImage>

namespace ui
{
	UnreadMsgLabel::UnreadMsgLabel(QWidget* parent)
		: QLabel(parent)
	{
		this->setFont(QFont("Microsoft YaHei", 8)); ///<==== 2019-7-20  ������ʾ��Ϣ�����С,ԭ����Ϊ8 
		this->setAlignment(Qt::AlignCenter);
		this->setObjectName("whiteLabel1");
	}

	void UnreadMsgLabel::setText(const QString& text) //δ����ϢС��㱳����С
	{
		QLabel::setText(text);
		if (text.length() <= 1)
		{
			setFixedSize(QSize(FontW, FontW * 1.5)); //FontW
			this->setObjectName("whiteLabel1");
		}
		else if (text.length() == 2)
		{
			this->setFixedSize(QSize(Font2W, FontW * 1.5)); //FontW
			this->setObjectName("whiteLabel2");
		}
		else
		{
			setFixedSize(QSize(Font3W, FontW * 1.5)); //FontW
			this->setObjectName("whiteLabel3");
		}
		this->update();
	}

	UnreadMsgLabel::~UnreadMsgLabel()
	{
	}

	void UnreadMsgLabel::paintEvent(QPaintEvent* e)
	{
		QPainter painter(this);
		painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);

		painter.setBrush(Qt::red);
		painter.setPen(Qt::red);
		//QRectF rectangle(0.0, 0.0, 20.0, 20.0);

		QPainterPath path;
		path.addEllipse(rect());
		painter.setClipPath(path);

		painter.drawEllipse(rect());
		QLabel::paintEvent(e);
	}
}
