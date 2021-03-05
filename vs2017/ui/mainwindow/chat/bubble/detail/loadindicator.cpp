#include "loadindicator.h"
#include "QProgressIndicator.h"
#include "clicklabel.h"

#include <QStackedWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include "../../../../common/Common.h"

class LoadIndicatorPrivate
{
public:
    void init();

    LoadIndicator* q_ptr;
    QWidget* normalWidget;
    ClickLabel* clickLabel;
	QLabel* imageLabel;
    QProgressIndicator* loadingWidget;
};

void LoadIndicatorPrivate::init()
{
    // Create normal widget
    normalWidget = new QWidget(q_ptr);
    imageLabel = new QLabel(normalWidget);
    imageLabel->setPixmap(QPixmap(":/chat/clock"));

    clickLabel = new ClickLabel(normalWidget);
    clickLabel->setTextColor(QColor(19,52,83));
    clickLabel->setUnderlined(true);
    clickLabel->setText(transfer("查看更多消息"));
    QHBoxLayout* normalWidgetLayout = new QHBoxLayout;
    normalWidgetLayout->setSpacing(3);
    normalWidgetLayout->setContentsMargins(1, 1, 1, 1);
    normalWidgetLayout->addWidget(imageLabel);
    normalWidgetLayout->addWidget(clickLabel);
    normalWidget->setLayout(normalWidgetLayout);

    // Create loading widget
    loadingWidget = new QProgressIndicator(q_ptr);
    loadingWidget->startAnimation();
    loadingWidget->hide();

    q_ptr->connect(clickLabel, SIGNAL(clicked()), q_ptr, SLOT(onLabelClicked()));

    q_ptr->setFixedHeight(20);
    q_ptr->setAttribute(Qt::WA_TranslucentBackground);
}

LoadIndicator::LoadIndicator(QWidget *parent) : QWidget(parent)
{
    d_ptr = new LoadIndicatorPrivate;
    d_ptr->q_ptr = this;
    d_ptr->init();
}

void LoadIndicator::setNoMoreDataState(bool isClicked)
{
	if (isClicked)
	{
		d_ptr->clickLabel->setTextColor(QColor(19, 52, 83));
		d_ptr->clickLabel->setText(transfer("查看更多消息"));
	}
	else{
		d_ptr->clickLabel->setTextColor(Qt::gray);
		d_ptr->clickLabel->setText(transfer("没有更多消息了"));
	}
	d_ptr->clickLabel->setEnabled(isClicked);
}

LoadIndicator::~LoadIndicator()
{
    delete d_ptr;
}

void LoadIndicator::setLoading(bool loading)
{
    d_ptr->loadingWidget->setVisible(loading);
    d_ptr->normalWidget->setVisible(!loading);
    layoutWidgets();
}

bool LoadIndicator::loading() const
{
    return d_ptr->loadingWidget->isVisible();
}

void LoadIndicator::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event)
    layoutWidgets();
}

void LoadIndicator::onLabelClicked()
{
    d_ptr->loadingWidget->show();
    d_ptr->normalWidget->hide();
    layoutWidgets();
    emit startLoading();
}
void LoadIndicator::setNoMoreData(){
	d_ptr->loadingWidget->setVisible(false);
	d_ptr->imageLabel->setDisabled(true);
	d_ptr->clickLabel->setTextColor(Qt::gray);
	d_ptr->clickLabel->setText(transfer("没有更多消息了"));
	d_ptr->normalWidget->setVisible(true);
	layoutWidgets();
}
void LoadIndicator::layoutWidgets()
{
    if (d_ptr->loadingWidget->isVisible()) {
        QPoint pos(rect().center().x() - (qreal)d_ptr->loadingWidget->width() / 2, 0);
        d_ptr->loadingWidget->move(pos);
        d_ptr->loadingWidget->setFixedSize(QSize(height(), height()));
    }

    if (d_ptr->normalWidget->isVisible())
        d_ptr->normalWidget->setGeometry(rect());
}

bool LoadIndicator::hasMoreData()
{
	return !(d_ptr->clickLabel->text() == transfer("没有更多消息了"));
}

