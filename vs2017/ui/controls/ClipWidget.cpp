#include "ClipWidget.h"
#include <QPainter>
#include <QLabel>
#include <QDesktopServices>
#include <utils/common.h>
#include <log.h>

ClipWidget::ClipWidget(QWidget* parent)
	: QWidget(parent), m_fileName("")
{
	horizontalSlider = new QSlider(this);
	horizontalSlider->setOrientation(Qt::Horizontal);
	horizontalSlider->setFixedSize(300, 20); //h:20(2020-8-25)
	horizontalSlider->setMinimum(0);
	horizontalSlider->setMaximum(99);
	horizontalSlider->setSingleStep(1);
	horizontalSlider->move(0, 310);
	connect(horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(onScaledChanged(int)));

	scrollArea = new DragScrollArea(this);
	scrollArea->setWidgetResizable(true);
	scrollArea->setFixedSize(300, 300);
	scrollArea->move(0, 0);

	scrollAreaWidgetContents = new QWidget();
	verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);

	label_header = new QLabel(scrollAreaWidgetContents);
	label_header->setAlignment(Qt::AlignCenter);
	verticalLayout->addWidget(label_header);

	scrollArea->setWidget(scrollAreaWidgetContents);

	m_pDivWidget = new QWidget(scrollArea);
	m_pDivWidget->setAttribute(Qt::WA_TranslucentBackground);
	m_pDivWidget->hide();
	m_pDivWidget->installEventFilter(this);
}

ClipWidget::~ClipWidget()
{
}

void ClipWidget::LoadHeader(const QPixmap& pixmap)
{
	if (pixmap.isNull())
	{
		AddLog(LOG_LEV_INFO, "error---ClipWidget::LoadHeader()-pixmap=NULL!");
		m_fileName = "";
		return;
	}
	if (pixmap.width() < 300 && pixmap.height() < 300)
	{
		m_sourceHeader = pixmap.scaled(300, 300, Qt::KeepAspectRatio);
	}
	else
	{
		m_sourceHeader = pixmap;
	}
	int nSliderMinmum = 0;
	QPixmap scaledPixmap;
	if (m_sourceHeader.width() > m_sourceHeader.height())
	{
		scaledPixmap = m_sourceHeader.scaledToHeight(scrollArea->height());
		nSliderMinmum = scaledPixmap.height() * horizontalSlider->maximum() / m_sourceHeader.height();
	}
	else
	{
		scaledPixmap = m_sourceHeader.scaledToWidth(scrollArea->width());
		nSliderMinmum = scaledPixmap.width() * horizontalSlider->maximum() / m_sourceHeader.width();
	}
	scrollAreaWidgetContents->resize(m_sourceHeader.size());
	horizontalSlider->setEnabled(true);
	horizontalSlider->setMinimum(nSliderMinmum);
	horizontalSlider->setValue(nSliderMinmum);
	label_header->setPixmap(scaledPixmap);
	m_pDivWidget->show();
}

bool ClipWidget::eventFilter(QObject* watched, QEvent* event)
{
	if (m_pDivWidget == watched && QEvent::Paint == event->type()) //»æÖÆÕÚÕÖ²ã
	{
		m_pDivWidget->resize(scrollArea->size());
		QPainterPath path;
		path.addRect(m_pDivWidget->geometry());
		path.addEllipse(m_pDivWidget->geometry().adjusted(2, 2, -2, -2));
		QPainter p(m_pDivWidget);
		p.setRenderHint(QPainter::Antialiasing);
		p.setBrush(QColor(100, 100, 100, 200));
		p.setClipPath(path);
		p.drawRect(m_pDivWidget->geometry());
	}
	return QWidget::eventFilter(watched, event);
}

void ClipWidget::onScaledChanged(int nValue)
{
	int a = horizontalSlider->maximum();
	int b = m_sourceHeader.size().width();
	int bb = m_sourceHeader.size().height();

	QPixmap pixmap = m_sourceHeader.scaled(
		m_sourceHeader.size() * (static_cast<double>(nValue) / horizontalSlider->maximum()));
	scrollAreaWidgetContents->resize(pixmap.size());
	label_header->setPixmap(pixmap);
}

void ClipWidget::setImgPath(QString filename)
{
	m_fileName = filename;

	//QString strFilePath = "C:/Users/Joven/Desktop/VA/ClipImageWidget/ClipImageWidget/bbb.jpg";
	LoadHeader(QPixmap(m_fileName));
}

void ClipWidget::saveImg()
{
	if (const QPixmap* pHeader = label_header->pixmap())
	{
		int x = scrollArea->horizontalScrollBar()->value();
		int y = scrollArea->verticalScrollBar()->value();
		QPixmap pix400 = pHeader->copy(x, y, 300, 300);
		QPixmap pix150 = pix400.scaled(130, 130);


		std::string userdatapath = QStandardPaths::writableLocation(QStandardPaths::DataLocation).toLocal8Bit().data();
		utils::string_replace(userdatapath, "Linkdood", "CPPCC");
		QString file400 = QString::fromStdString(userdatapath + "/public/head/tmpHead400x400.jpg");
		QString file150 = QString::fromStdString(userdatapath + "/public/head/tmpHead150x150.jpg");


		pix400.save(file400, "JPEG");
		pix150.save(file150, "JPEG");

		emit clipImgSucc(file400, file150);
	}
	else
	{
	}
}
