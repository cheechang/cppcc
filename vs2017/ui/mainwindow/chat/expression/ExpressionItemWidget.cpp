#include "ExpressionItemWidget.h"
#include <QMovie>
#include <QDebug>
#include <QMouseEvent>
namespace ui{
	ExpressionItemWidget::ExpressionItemWidget(QString fileName , QSize emotionMoiveSize,QWidget*parent)
		: QLabel(parent)
	{
		//���ȹ��캯���н��г�ʼ��;
		QMovie* iconMovie = new QMovie(this);
		iconMovie->setFileName(fileName);
		this->setMovie(iconMovie);
		setContentsMargins(3, 3, 3, 3);
		iconMovie->setScaledSize(QSize(emotionMoiveSize.width(), emotionMoiveSize.height()));
		//Ϊ�˶�̬ͼƬ������ʾ����������startͼƬ����ʾ��������stopͼƬһ�ִ��ڶ�̬Ч����
		iconMovie->start();
		iconMovie->stop();
		setStyleSheet("QLabel:hover{border: 1px solid rgb(111, 156, 207);\
					  color: rgb(2, 65, 132);\
					  background: rgba(255, 255, 255, 200);}");
	}

	ExpressionItemWidget::~ExpressionItemWidget()
	{}

	// ������Label�¼�
	void ExpressionItemWidget::enterEvent(QEvent* event)
	{
		QMovie* movie = this->movie();
		movie->start();
		setContentsMargins(4, 2, 2, 4);
		return __super::enterEvent(event);
	}
	// ����뿪Label�¼�
	void ExpressionItemWidget::leaveEvent(QEvent* event)
	{
		QMovie* movie = this->movie();
		movie->jumpToFrame(0);
		movie->stop();
		setContentsMargins(3, 3, 3, 3);
		return __super::leaveEvent(event);
	}

	void ExpressionItemWidget::mousePressEvent( QMouseEvent *ev )
	{
		if (ev->button() == Qt::LeftButton)
		{
			emit clicked(this->movie()->fileName());
		}
		QLabel::mousePressEvent(ev);
	}

}