#include "ClipImageWidget.h"
#include "Log.h"
#include <QFileDialog>
#include <QPainter>
#include <QPaintEvent>
#include "../common/Common.h"

namespace ui{
ClipImageWidget::ClipImageWidget(QWidget *parent)
	: QWidget(parent),m_filename("")
{
	m_bgLab.setParent(this);
	m_bgLab.resize(330, 330);
	m_bgLab.setStyleSheet("background-color: rgb(200, 200, 200)");

	m_selBtn.setParent(&m_bgLab);
	m_selBtn.setMinimumSize(162, 52);
	m_selBtn.setPicName(QString(":/group/selectImg"));
	m_selBtn.setVisible(true);
	connect(&m_selBtn, SIGNAL(clicked()), this, SLOT(onSelectBtnClicked()));

	m_clipImg.setParent(this);
	m_clipImg.resize(330, 330);
	//m_clipImg.move(50, 50);
	m_clipImg.setVisible(false);
	connect(&m_clipImg, SIGNAL(clipImgSucc(QString, QString)), this, SLOT(onClipImgSucc(QString, QString)));
}

ClipImageWidget::~ClipImageWidget()
{

}
void ClipImageWidget::setMinSize(int w, int h)
{
	AddLog(LOG_LEV_INFO,"------this:w:%d-h:%d===btn:w:%d-h:%d-----", this->width(), this->height(), m_selBtn.width(), m_selBtn.height());

	this->setMinimumSize(w, h);
	m_selBtn.move((w - m_selBtn.width())/2, (h - m_selBtn.height())/2);
	m_bgLab.setVisible(true);
	m_clipImg.setVisible(false);
}
void ClipImageWidget::setBtnVisible(bool b)
{
	m_bgLab.setVisible(true);
	m_clipImg.setVisible(false);
	m_filename = "";
	
	//setAutoFillBackground(true);   // 这个属性一定要设置
	//QPalette pal(palette());
	//pal.setBrush(QPalette::Window, QBrush());
	//setPalette(pal);
}
void ClipImageWidget::onSelectBtnClicked()
{  
	m_filename = QFileDialog::getOpenFileName(this,  
		transfer("选择图像"),  
		"",  
		transfer("Images (*.bmp *.jpg *.tif)")); //选择路径  
	if(m_filename.isEmpty())  
	{
		m_bgLab.setVisible(true);
		return;  
	}  
	else  
	{
		m_bgLab.setVisible(false);
		m_clipImg.setImgPath(m_filename);
		m_clipImg.setVisible(true);
	}
}
void ClipImageWidget::onBtnSaveImg()
{
	if (m_filename == "")
		return;
	m_clipImg.saveImg();
}
void ClipImageWidget::onClipImgSucc(QString file400, QString file150)
{
	emit clipImgSucc(file400, file150);
}
}
