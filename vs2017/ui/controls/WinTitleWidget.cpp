#include "WinTitleWidget.h"
namespace ui{
WinTitleWidget::WinTitleWidget(QLabel *parent)
	: QLabel(parent)
{
	setStyleSheet("background-color:#2768c2; color:white");
	m_btnClose.setParent(this);
	m_btnClose.setPicName(QString(":/login/close"));
	m_hLayout.addStretch();
	m_hLayout.addWidget(&m_btnClose);
	m_hLayout.setMargin(1);

	setLayout(&m_hLayout);

	connect(&m_btnClose, SIGNAL(clicked()), this, SLOT(onBtnClose()));
}

WinTitleWidget::~WinTitleWidget()
{

}
void WinTitleWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint curPoint  = event->pos();
	emit mouseMoveTo(QPoint(curPoint.x()-m_pos.x(),curPoint.y()-m_pos.y()));
}
void WinTitleWidget::mousePressEvent(QMouseEvent *event)
{
	m_pos = event->pos();
}
void WinTitleWidget::onBtnClose()
{
	emit closeClicked();
}
}